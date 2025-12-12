#!/bin/bash

# Require sudo
if [[ $EUID -ne 0 ]]; then
  echo "This script must be run with sudo." >&2
  exit 1
fi

RR_INSTALLER_NAME=$1
if [[ -z "$RR_INSTALLER_NAME" ]]; then
  echo "Usage: sudo $0 <installer_name>"
  echo "Example: sudo $0 RoyalRender__9.1.21__installer"
  exit 1
fi

RR_SERVICE_PATH="/usr/local/rrService"
RR_SERVICE_LIB_PATH="/usr/local/rrService/lib"
RR_INSTALLER_ARCHIVE="$RR_INSTALLER_NAME.zip"
RR_INSTALLER_BIN_PATH="$RR_INSTALLER_NAME/files/bin/lx64"
RR_SERVICE_FILES=(
"rrCloudService"
"rrLazyPeasant"
"rrKillWait"
"lib/libQt5Core.so.5"
"lib/libQt5Network.so.5"
"lib/librrShared.so.1"
"lib/libcrypto.so.1.1"
"lib/libssl.so.1.1"
"lib/7z.so"
)


dnf install unzip wget cifs-utils
wget "https://www.royalrender.de/download/$RR_INSTALLER_ARCHIVE"
unzip $RR_INSTALLER_ARCHIVE

mkdir -p $RR_SERVICE_PATH

if [ ! -d "$RR_SERVICE_PATH" ]; then
  mkdir -p $RR_SERVICE_PATH
fi

if [ ! -d "$RR_SERVICE_LIB_PATH" ]; then
  mkdir -p $RR_SERVICE_LIB_PATH
fi

for file in ${RR_SERVICE_FILES[@]}; do
  if [ -f "$RR_INSTALLER_BIN_PATH/$file" ]; then
    cp "$RR_INSTALLER_BIN_PATH/$file" "$RR_SERVICE_PATH/$file"
    echo "Copied: $file"
  else
    echo "Could not copy from: $RR_INSTALLER_BIN_PATH/$file to: $RR_SERVICE_PATH/$file"
  fi
done

chown -R root:wheel "$RR_SERVICE_PATH"
chmod -R +x "$RR_SERVICE_PATH"

"$RR_SERVICE_PATH/rrCloudService" /install


