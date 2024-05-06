#!/usr/bin/env python3
import subprocess
import platform
import sys

def test_devices(devices):
    if not devices:
        return

    for device in devices:
        result = subprocess.run(["badblocks", "-v", "-s", "-w", "-t", "0xaa", device])
        if result.returncode != 0:
            print(f"Error: {result.returncode} on Device: {device}") 
        else:
            print(f"{device}: OK")

def format_devices(devices):
    if not devices:
        return

    print("Formatting MSD devices to FAT32...")
    for device in devices:
        subprocess.run(["sudo", "mkfs.vfat", "-F", "32", "-n", "MSD_TEST", device])

    print("All MSD devices formatted to FAT32.")

def main():
    args = sys.argv[1:]
    test_answer = input(f"Do you want to test these devices: {args}? (y/n): ")
    if test_answer.lower() == "y":
        test_devices(args)
        format_devices(args)

if __name__ == "__main__":
    main()
