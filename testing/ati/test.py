#!/usr/bin/env python3
import subprocess
import platform
import sys
import multiprocessing
import os

def test_device(device):
    print(f"Testing: {device}")
    result = subprocess.run(["sudo", "badblocks", "-b", "4096", "-svwt", "0xaa", device], stdout=subprocess.PIPE)

    if result.returncode != 0:
        print(f"Error: {result.returncode} on Device: {device}") 
    else:
        print(f"{device}: OK")

def format_device(device):
    print(f"Formatting {device} to FAT32...")
    subprocess.run(["sudo", "mkfs.vfat", "-F", "32", device])

def unmount_device(device):
    subprocess.run(["sudo", "umount", device], stderr=subprocess.DEVNULL)
    subprocess.run(["sudo", "umount", device + "1"], stderr=subprocess.DEVNULL)
    subprocess.run(["sudo", "umount", device + "2"], stderr=subprocess.DEVNULL)
    subprocess.run(["sudo", "umount", device + "3"], stderr=subprocess.DEVNULL)

def mount_device(device):
    folder = "mnt/" + device.split("/")[2] 
    subprocess.run(["mkdir", folder])
    subprocess.run(["sudo", "mount", device, folder])

def copy_payload(device):
    folder = "mnt/" + device.split("/")[2]
    subprocess.run(["sudo", "cp", "hello.txt", folder])

def batch(device):
    unmount_device(device)
    test_device(device)
    format_device(device)
    mount_device(device)
    copy_payload(device)
    unmount_device(device)

def main():
    args = sys.argv[1:]
    test_answer = input(f"Do you want to test these devices: {args}? (y/n): ")
    if test_answer.lower() == "y":
        subprocess.run(["mkdir", "mnt"])
        processes = []
        for device in args:
            process = multiprocessing.Process(target=batch, args=(device,))
            processes.append(process)
            process.start()

        for process in processes:
            process.join()

if __name__ == "__main__":
    main()
