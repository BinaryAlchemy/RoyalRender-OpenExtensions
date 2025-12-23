#!/bin/bash

# Usage: sudo ./generalize-vm-gce.sh
echo "Generalizing VM..."

# 0. Require sudo
if [[ $EUID -ne 0 ]]; then
  echo "This script must be run with sudo." >&2
  exit 1
fi

# 1. Clean logs
echo "Cleaning logs..."
truncate -s 0 /var/log/*.log
find /var/log -type f -exec truncate -s 0 {} +

# 2. Remove SSH host keys (will regenerate on next boot)
echo "Removing SSH host keys..."
rm -f /etc/ssh/ssh_host_*key*

# 3. Clean cloud-init (forces first-boot behavior on new instances)
echo "Cleaning cloud-init..."
cloud-init clean --logs
rm -rf /var/lib/cloud/instance

# 4. Clean package caches and temp files
echo "Cleaning APT and temp files..."
apt-get clean
rm -rf /tmp/* /var/tmp/* /var/cache/apt/archives/*

# 5. Remove open-vpn configurations
echo "[*] Removing OpenVPN configurations..."
rm -fR /etc/openvpn/server/*

# 6. Remove machine-specific data (history, caches)
rm -rf /root/.cache /home/*/.cache

# 7. Remove client files
/etc/init.d/rrCloudService stop
rm /usr/local/rrService/configExecutedOnce.info
rm -rf /usr/local/rrService/lc64
rm -rf /usr/local/RR_Localdata
rm /usr/local/rrService/rrCloudService.log
rm /usr/local/rrService/rrCloudService_Errors.log

# 8. Remove all users
echo "Removing custom users..."
for user in $(getent passwd | awk -F: '$3 >= 1000 && $1 != "nobody" {print $1}'); do
    userdel --remove --force "$user"
done
rm -rf /home/* /root/.ssh

# 9. Clear history
history -c
export HISTSIZE=0

echo "Cleanup complete."
