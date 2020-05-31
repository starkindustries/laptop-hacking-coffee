#!/bin/python3
import subprocess

with open('keys.txt', 'r') as handle:
    for line in handle:
        key = line.strip()
        args = ['./keygen.elf', key]
        try:
            result = subprocess.check_output(args).decode().strip()
            result = int(result)
            # print(f"{key}: {result}")
            if result == 2653470883089645351:
                print(f"Found valid key: {key}")
        except Exception as e:
            # print(f"Error in result: {e}")
            pass