#!/usr/bin/python3

import sys

p1 =  "helloworld".encode()
p2 =  "\x68\x65\x6c\x6c\x6f\x77\x6f\x72\x6c\x64".encode()
p3 =  "\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc".encode()
p4 = b'\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc\xcc'
sys.stdout.buffer.write(p1)
sys.stdout.buffer.write(p2)
sys.stdout.buffer.write(p3)
sys.stdout.buffer.write(p4)


