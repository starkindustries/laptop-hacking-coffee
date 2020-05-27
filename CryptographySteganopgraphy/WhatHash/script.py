#!/bin/python3
import hashlib

file = open('flag.txt', 'r')
password = file.read()
def fixer(my_string):
    my_string = my_string.encode('utf-8')
    m = hashlib.md5(my_string)
    return m.hexdigest()

y = '707c20104fe9aaa'
w = '4ad6cf25cd02b402c4310334'
x = fixer(password)
z = y+x+w
print(z)