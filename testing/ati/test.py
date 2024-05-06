#!/usr/bin/env python3
import subprocess
import platform
import sys

def test_device(device):
    result = subprocess.run(["sudo", "badblocks", "-b", "4096", "-svwt", "0xaa", device])

    if result.returncode != 0:
        print(f"Error: {result.returncode} on Device: {device}") 
    else:
        print(f"{device}: OK")

def format_device(device):
    print(f"Formatting {device} to FAT32...")
    subprocess.run(["sudo", "mkfs.vfat", "-F", "32", device])

def unmount_device(device):
    subprocess.run(["sudo", "umount", device])
    subprocess.run(["sudo", "umount", device + "1"])

def mount_device(device):
    folder = "mnt/"
    subprocess.run(["mkdir", folder])
    subprocess.run(["sudo", "mount", device, folder])

def copy_payload(device):
    folder = "mnt/"
    subprocess.run(["sudo", "cp", "hello.txt", folder])

def main():
    args = sys.argv[1:]
    test_answer = input(f"Do you want to test these devices: {args}? (y/n): ")
    if test_answer.lower() == "y":
        subprocess.run(["mkdir", "mnt"])
        for device in args:
            unmount_device(device)
            test_device(device)
            format_device(device)
            mount_device(device)
            copy_payload(device)
            unmount_device(device)

if __name__ == "__main__":
    main()
