#!/bin/bash

# Make sure user entered location
if ! [[ -n $1 ]]; then
	echo Suppy drive location ie: /dev/sdf
	exit;
fi

read -p "Start Destructive test $1? (Y/n) :" inp

if [ "$inp" = "n" ]; then
	exit;
fi

disk=$1
part=${disk}1

echo "Checking for Bad Blocks"
sudo badblocks -w -s -o error.log $disk
sudo parted -s $disk mklabel gpt
sudo parted -s $disk mkpart primary fat32 1MiB 100%
sudo mkfs.vfat -F 32 $part
sudo mount $part /mnt/
sudo f3write /mnt/
sudo f3read /mnt/
sudo rm -rf /mnt/*
sudo umount /mnt/
