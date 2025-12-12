#!/bin/bash
echo "=== Generalizing AlmaLinux instance for AMI capture ==="

# 1. Require sudo
if [[ $EUID -ne 0 ]]; then
  echo "This script must be run with sudo." >&2
  exit 1
fi

# 2. Stop services that might recreate state while cleaning
echo "[*] Stopping rsyslog (if present)..."
systemctl stop rsyslog

# 3. Remove SSH host keys so each clone gets fresh keys
echo "[*] Removing SSH host keys..."
rm -f /etc/ssh/ssh_host_*

# 4. Clear user bash history and authorized_keys for all local users
echo "[*] Clearing bash history and authorized keys..."
history -c 2>/dev/null || true
for home in /root /home/*; do
  if [[ -d "$home" ]]; then
    rm -f "$home"/.bash_history
    cat /dev/null > /home/$SUDO_USER/.ssh/authorized_keys
  fi
done

# 5. Clear temporary directories
echo "[*] Cleaning /tmp and /var/tmp..."
rm -rf /tmp/* /tmp/.[!.]* /tmp/..?*
rm -rf /var/tmp/* /var/tmp/.[!.]* /var/tmp/..?*

# 6. Truncate common log files (keep files, drop contents)
echo "[*] Truncating common logs..."
LOG_DIRS=(/var/log)
for d in "${LOG_DIRS[@]}"; do
  if [[ -d "$d" ]]; then
    find "$d" -type f -name "*.log" -exec sh -c '> "$1"' _ {} \;
    find "$d" -type f -name "messages"  -exec sh -c '> "$1"' _ {} \; 2>/dev/null || true
    find "$d" -type f -name "secure"    -exec sh -c '> "$1"' _ {} \; 2>/dev/null || true
    find "$d" -type f -name "wtmp"      -exec sh -c '> "$1"' _ {} \; 2>/dev/null || true
    find "$d" -type f -name "btmp"      -exec sh -c '> "$1"' _ {} \; 2>/dev/null || true
  fi
done

# 7. Remove cloud-init instance data so new instances re-run init
if command -v cloud-init >/dev/null 2>&1; then
  echo "[*] Cleaning cloud-init state..."
  cloud-init clean --logs || true
fi

# 8. Remove machine-id so clones get unique IDs
echo "[*] Resetting machine-id..."
truncate -s 0 /etc/machine-id
rm -f /var/lib/dbus/machine-id
ln -sf /etc/machine-id /var/lib/dbus/machine-id

# 9. Remove open-vpn configurations
echo "[*] Removing OpenVPN configurations..."
rm -fR /home/$SUDO_USER/Server
rm -fR /etc/openvpn/server/*

# 10. Remove temp stuff home folder
echo "[*] Removing temp stuff home folder..."
rm -R /home/$SUDO_USER/.local
rm -R /home/$SUDO_USER/.cache
rm  /home/$SUDO_USER/.wget-hsts
rm  /home/$SUDO_USER/.sudo_as_admin_successful
rm -R /home/$SUDO_USER/scripts

echo "=== Generalization complete. Shut down this instance and create the AMI ==="
