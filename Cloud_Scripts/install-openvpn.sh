#!/bin/bash
# Complete UFW + OpenVPN install & config script for Ubuntu 24.04 LTS
# Usage: sudo ./install-openvpn.sh <VPN_SUBNET> <EXTERNAL_INTERFACE>
# Example: sudo ./install-openvpn.sh 10.8.0.0/16 eth0

set -e

VPN_SUBNET=$1
EXT_IF=$2

if [[ -z "$VPN_SUBNET" || -z "$EXT_IF" ]]; then
  echo "Usage: sudo $0 <VPN_SUBNET> <EXTERNAL_INTERFACE>"
  echo "Example: sudo $0 10.8.0.0/16 enp3s0"
  exit 1
fi

echo "Step 1: Update APT and install OpenVPN and UFW..."
apt update
apt install -y openvpn ufw

echo "Step 2: Enable IPv4 forwarding..."
sed -i 's/#net.ipv4.ip_forward=1/net.ipv4.ip_forward=1/' /etc/sysctl.conf
sysctl -p

echo "Step 3: Set UFW default forward policy to ACCEPT..."
sed -i 's/DEFAULT_FORWARD_POLICY="DROP"/DEFAULT_FORWARD_POLICY="ACCEPT"/' /etc/default/ufw

echo "Step 4: Enable IP forwarding in UFW sysctl config..."
sed -i 's/#net\/ipv4\/ip_forward=1/net\/ipv4\/ip_forward=1/' /etc/ufw/sysctl.conf

echo "Step 5: Configure NAT in UFW before.rules..."
# Backup the before.rules file
cp /etc/ufw/before.rules /etc/ufw/before.rules.bak

# Insert NAT rules if not already present
if ! grep -q "POSTROUTING -s $VPN_SUBNET -o $EXT_IF -j MASQUERADE" /etc/ufw/before.rules; then
  sed -i "/^*filter/i\\
# NAT table rules\n*nat\n:POSTROUTING ACCEPT [0:0]\n-A POSTROUTING -s $VPN_SUBNET -o $EXT_IF -j MASQUERADE\nCOMMIT\n" /etc/ufw/before.rules
fi

# Allow forwarding for VPN subnet in before.rules
#if ! grep -q "-A ufw-before-forward -s $VPN_SUBNET -j ACCEPT" /etc/ufw/before.rules; then
#  sed -i "/^COMMIT/i -A ufw-before-forward -s $VPN_SUBNET -j ACCEPT\n-A ufw-before-forward -d $VPN_SUBNET -j ACCEPT" /etc/ufw/before.rules
#fi

echo "Step 6: Allow OpenVPN-related traffic through UFW..."
ufw allow 1194/udp
ufw allow in on tun0
ufw allow out on tun0
ufw allow OpenSSH

echo "Step 7: Enable UFW if not enabled and reload rules..."
ufw --force enable
ufw reload

echo "Configuration complete. Remember to configure your OpenVPN server.conf separately, then restart:"
echo "  sudo systemctl restart openvpn-server@server"
