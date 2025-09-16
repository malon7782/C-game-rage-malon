#!/bin/bash


set -e

if [ "$(id -u)" -ne 0 ]; then
  echo "Usage: Sudo bash install.sh"
  exit 1
fi

command -v make >/dev/null 2>&1 || { echo >&2 "error. please install build-essential"; exit 1; }
command -v gcc >/dev/null 2>&1 || { echo >&2 "error."; exit 1; }

make clean
make

install game /usr/local/bin/mtrage

echo ""
