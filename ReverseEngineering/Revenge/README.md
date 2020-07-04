# Revenge

## Reverse Engineering: 130 Points

## Challenge

I'm going to get those cryptolocker hackers back, here's the decryption module of my own malware that I'm sure is impenetrable. There's a little trick in there that should make it so nobody can decrypt it without knowing my secret.

Note: Be sure to encase it in LHC{}

Credit: ebeem#6523

[ [revenge_decoder](revenge_decoder) ]

## Solution

```
$ chmod +x 
```

```
$ file revenge_decoder 
revenge_decoder: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=3e3e7f8d6c7cada1c9d281142a8e752616c653f8, not stripped
```

Run file:
```
$ ./revenge_decoder 
invalid bypass key
[usage]
crack_me_03 [key]
$ ./revenge_decoder test
heh, won't be this easy
```

Decompile with Ghidra: [main.c](main.c)

Set breakpoint at `*main+136`:
```
   0x555555555100 <main+126>       lea    rsi,[rip+0x352]     # 0x555555555459
   0x555555555107 <main+133>       mov    rdi,rax
B+>0x55555555510a <main+136>       call   0x555555554e40 <strcmp@plt>
```

```
(gdb) set args hello world
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/z/Documents/playgrounds/LaptopHackingCoffee/ReverseEngineering/Revenge/revenge_decoder hello world

Breakpoint 2, 0x000055555555510a in main ()
(gdb) x/s $rdi
0x7fffffffe345: "hello"
(gdb) x/s $rsi
0x555555555459: "pXUsB"
(gdb) 
```

Set first argument to `pXUsB`:
```
(gdb) set args pXUsB world
```

It works.

```
 0x55555555510f <main+141>       test   eax,eax
 0x555555555111 <main+143>       jne    0x5555555551fe <main+380>
>0x555555555117 <main+149>       cmp    DWORD PTR [rbp-0xb4],0xfffe7961
 0x555555555121 <main+159>       jne    0x5555555551fe <main+380>
 0x555555555127 <main+165>       lea    rsi,[rip+0x332]        # 0x555555555460
(gdb) set $rip = main+165
(gdb) c
Continuing.
wow, the flag is LHC{[BYPASS_KEY_HERE]bH6yjQsKAsqOBjx}
```

Add in the bypass key `pXUsB`:
```
LHC{pXUsBbH6yjQsKAsqOBjx}
```