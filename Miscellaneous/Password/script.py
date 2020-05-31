#!/bin/python3

from pwn import *

conn = remote('challenges.laptophackingcoffee.org', 3345)
conn.recvline()