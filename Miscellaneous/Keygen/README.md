# Keygen

## Miscellaneous: 70 Points

## Challenge

This file will give you a bunch of keys for fortnite vbucks but almost all of them are invalid. You're supposed to get a value of `2653470883089645351` when testing the key with the program, but there are way too many for me to test. I need you to test all the keys for me and give me the right one so I can buy the newest pewdiepie skin.

Note: Be sure to encase in LHC{}

Credit: ebeem#6523

[ [keygen.elf](keygen.elf) ]

## Solution
Add run permissions to the keygen file. Run it:
```
$ chmod +x keygen.elf
$ ./keygen.elf
[usage]
crack_me_01 [flag]
This program prints the value of the flag
```

The program expects a parameter `[flag]`. Try a random flag parameter. No luck:
```
$ ./keygen.elf is_this_the_flag
what's this?? skid!!
```

Run **strings** on the program:
```
$ strings keygen.elf | less
...
AUATL
[]A\A]A^A_
what's this?? skid!!
[usage]
crack_me_01 [flag]
This program prints the value of the flag
XYkzevAdssaKfYnjM4U7
KeAhYcIvDalZiIekU5vh
QauqhPStdLTpiBY4f5e6
27YQr1FRLqMqRl9lP414
...
```

The result shows a bunch of program symbols at the beginning. Then it shows the help string: `This program prints the value of the flag`. After this help string, it shows a bunch of random strings with all the same length. In the challenge prompt it says:

> This file will give you a bunch of keys for fortnite vbucks but almost all of them are invalid.

Maybe these random strings are keys. Try one of them to find out:
```
$ ./keygen.elf XYkzevAdssaKfYnjM4U7
-196612959275761727
```

This time the result is a number, which also follows the challenge prompt:

> You're supposed to get a value of 2653470883089645351

However, the result does not match the desired value `2653470883089645351`. The challenge suggests to "test all the keys." Export all keys to a file:
```
$ strings keygen.elf > keys.txt
```

Write up a python [script](./script.py) to test all the keys programmatically:
```python
#!/bin/python3
import subprocess

with open('keys.txt', 'r') as handle:
    for line in handle:
        key = line.strip()
        args = ['./keygen.elf', key]
        try:
            result = subprocess.check_output(args).decode().strip()
            result = abs(int(result))
            # print(f"{key}: {result}")
            if result == 2653470883089645351:
                print(f"Found valid key: {key}")
        except Exception as e:
            # print(f"Error in result: {e}")
            pass
```

Take a look at the line: `result = abs(int(result))`. Some keys return a negative number, which will not match with the desired positive value `2653470883089645351`. To fix this, the script gets the absolute value of the result and then compares it to the desired value. Run the script:

```
$ python3 script.py
Found valid key: kojhqSt5R2JztnmxQXL1
```

Valid key found. Format as flag and submit:
```
LHC{kojhqSt5R2JztnmxQXL1}
```

## GDB Commands
A few notes about basic gdb commands used while troubleshooting:
```
(gdb) start         - Start program with breakpoint at first instruction
(gdb) step          - Execute next program line (after stopping); step into any function calls in the line.
(gdb) print [expr]  - Print value of expression
(gdb) next          - Step over instruction
```