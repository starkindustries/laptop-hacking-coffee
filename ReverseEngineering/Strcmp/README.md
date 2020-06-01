# Strcmp

## Points: 30

## Challenge
A kid I go to school with bet me I couldn't hack his program. I'm a skid who just asks others to do stuff for me since I'm incapable of learning myself, so can you hack it for me plz.

Note: Be sure to encase it in LHC{}

[password.elf](./password.elf)

## Solution
Download the file `password.elf` and open it up with GDB. Also set the `disassembly-flavor` and use `layout asm` mode.

```
$ gdb password.elf
(gdb) set disassembly-flavor intel
(gdb) layout asm
```

Quick note: when using `layout asm`, the assembly code moves up/down when pressing the up/down arrow keys. To fix this, change the focus to the command window using command `focus cmd`. To switch focus back, use command `focus asm`. To exit `layout asm` mode, enter `Ctrl + x + a`.

Source: https://sourceware.org/gdb/onlinedocs/gdb/TUI-Commands.html

In the `asm` view, take a look at the `main` function. It will look very similar to this:

```
0x000000000000080a <+0>:	push   rbp
0x000000000000080b <+1>:	mov    rbp,rsp
0x000000000000080e <+4>:	sub    rsp,0x30
0x0000000000000812 <+8>:	mov    rax,QWORD PTR fs:0x28
0x000000000000081b <+17>:	mov    QWORD PTR [rbp-0x8],rax
0x000000000000081f <+21>:	xor    eax,eax
0x0000000000000821 <+23>:	mov    QWORD PTR [rbp-0x20],0x0
0x0000000000000829 <+31>:	mov    QWORD PTR [rbp-0x18],0x0
0x0000000000000831 <+39>:	mov    DWORD PTR [rbp-0x10],0x0
0x0000000000000838 <+46>:	mov    BYTE PTR [rbp-0x21],0x0
0x000000000000083c <+50>:	lea    rdi,[rip+0x111]        # 0x954
0x0000000000000843 <+57>:	mov    eax,0x0
0x0000000000000848 <+62>:	call   0x6c0 <printf@plt>
0x000000000000084d <+67>:	mov    rdx,QWORD PTR [rip+0x2007bc] # 0x201010 <stdin@@GLIBC_2.2.5>
0x0000000000000854 <+74>:	lea    rax,[rbp-0x20]
0x0000000000000858 <+78>:	mov    esi,0x14
0x000000000000085d <+83>:	mov    rdi,rax
0x0000000000000860 <+86>:	call   0x6d0 <fgets@plt>
0x0000000000000865 <+91>:	lea    rax,[rbp-0x20]
0x0000000000000869 <+95>:	mov    rdi,rax
0x000000000000086c <+98>:	call   0x6a0 <strlen@plt>
0x0000000000000871 <+103>:	mov    BYTE PTR [rbp-0x21],al
0x0000000000000874 <+106>:	movsx  eax,BYTE PTR [rbp-0x21]
0x0000000000000878 <+110>:	sub    eax,0x1
0x000000000000087b <+113>:	cdqe   
0x000000000000087d <+115>:	mov    BYTE PTR [rbp+rax*1-0x20],0x0
0x0000000000000882 <+120>:	lea    rax,[rbp-0x20]
0x0000000000000886 <+124>:	lea    rsi,[rip+0xd7]        # 0x964
0x000000000000088d <+131>:	mov    rdi,rax
0x0000000000000890 <+134>:	call   0x6e0 <strcmp@plt>
0x0000000000000895 <+139>:	test   eax,eax
0x0000000000000897 <+141>:	jne    0x8a7 <main+157>
0x0000000000000899 <+143>:	lea    rdi,[rip+0xcb]        # 0x96b
0x00000000000008a0 <+150>:	call   0x690 <puts@plt>
0x00000000000008a5 <+155>:	jmp    0x8b3 <main+169>
0x00000000000008a7 <+157>:	lea    rdi,[rip+0xc8]        # 0x976
0x00000000000008ae <+164>:	call   0x690 <puts@plt>
0x00000000000008b3 <+169>:	mov    eax,0x0
0x00000000000008b8 <+174>:	mov    rcx,QWORD PTR [rbp-0x8]
0x00000000000008bc <+178>:	xor    rcx,QWORD PTR fs:0x28
0x00000000000008c5 <+187>:	je     0x8cc <main+194>
0x00000000000008c7 <+189>:	call   0x6b0 <__stack_chk_fail@plt>
0x00000000000008cc <+194>:	leave  
0x00000000000008cd <+195>:	ret          
```

Note that line `0x890 <main+134>` contains the `strcmp` function mentioned in the challenge title. Set a breakpoint at that line. Run the program.

```
(gdb) break *main+134
Breakpoint 1 at 0x890
(gdb) run
Starting program: ~/password.elf
```

The program will ask for a password. Enter anything (e.g. password). At this point, the breakpoint triggers.

```
Enter password: password
Breakpoint 1, 0x0000000000000890 in main ()
(gdb) 
```

The program is currently at the `strcmp` call at `main+134`. Take a look at lines `main+124` and `main+131`. 
```
0x0000000000000886 <+124>:	lea    rsi,[rip+0xd7]        # 0x964
0x000000000000088d <+131>:	mov    rdi,rax
```
The first line contains `lea`, an instruction to load effective address. This loads the contents at `rip+0xd7` into the `rsi` register. The second line has a `mov` instruction, which moves the contents at `rax` into the `rdi` register. Quick list of what those instructions and registers stand for:

* lea: load effective address instruction
* mov: mov instruction
* rip: register instruction pointer
* rsi: register source index
* rax: register a extended
* rdi: register destination index

Examine the `rdi` and `rsi` registers. Evidently, `rdi` contains the password that was entered and `rsi` contains the actual password that is checked. This password is the flag.
```
(gdb) x /s $rdi
0x7fffffffde40:	"password"
(gdb) x /s $rsi
0x555555554964:	"n00bRE"
```

Format as flag and submit:
```
LHC{n00bRE}
```