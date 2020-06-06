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