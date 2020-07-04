# Double Dutch

## Reverse Engineering: 60 Points

## Challenge

This one seems tougher to crack than the other one I sent you. See if you can figure out what the heck is going on here.

Note: Be sure to encase it in LHC{}

Credit: Benwick#5127

[ [doubledutch](doubledutch) ]

## Solution
Run the program. Enter a password. Access denied:
```
$ ./doubledutch 
Insert a string of 5 characters: 12345
Access Denied!
```

Open in gdb to get a feel of what is happening. Then open with Ghidra to understand. In Ghidra, browse to the main function and examine the decompiled C code. After understanding the code, renaming functions, and adding comments, this is the result: [main.c](main.c).

The main function begins by initializing the `randLetters` array with nine hex values. The hex values convert to ASCII as `ajshfjahjf`:
```c
randLetters[0] = 0x61; // a
randLetters[1] = 0x6a; // j
randLetters[2] = 0x73; // s
randLetters[3] = 0x68; // h
randLetters[4] = 0x66; // f
randLetters[5] = 0x6a; // j
randLetters[6] = 0x61; // a
randLetters[7] = 0x68; // h
randLetters[8] = 0x6a; // j
randLetters[9] = 0x66; // f
```

The prompt `Insert a string of 5 characters:` is printed and five letters (`%5s`) of user input are scanned into `userInputString`:
```c
printf("Insert a string of 5 characters: ");
scanf("%5s", userInputString);
```

Then the `do while` loop begins. First it checks if `randLetterIndex` is greater than 9. If it is then `Access Granted`. The goal is to make it into this `if` block:
```c
if (9 < (int)randLetterIndex)
{
    puts("Access Granted");
    returnValue = 0;
LAB_0010082a:
    // ... 
    return returnValue;
}
```

This is followed by another `if` block containing a [bitwise AND operator][1]. Code explanation in the comments:
```c
// The '&' operator is a bitwise AND.
// For example: 5 & 1 = b101 & b001 = 1
// The only cases where a number & 1 equal 0 are for even numbers
// E.g. 
// 0 & 1 == 0
// 2 & 1 == 0
// 4 & 1 == 0
// etc.
// Therefore this if block is entered only when randLetterIndex is even.
// When randLetterIndex is odd, the if block is skipped.
if ((randLetterIndex & 1) == 0)
{    
    // This checks if userInput matches the randLetters. 
    // The indices are important. 
    // Since randLetterIndex is even, only even indices of 
    // randLetters are checked: 0, 2, 4, 6, 8    
    // Therefore, only "asfaj" are checked
    if ((int)userInputString[userInputIndex] != randLetters[(int)randLetterIndex])
    {
        puts("Access Denied!");
        returnValue = 1;
        goto LAB_0010082a;
    }
    // userInputIndex only increments when randLetterIndex is even  
    userInputIndex = userInputIndex + 1;
}
// randLetterIndex increments for every loop
randLetterIndex = randLetterIndex + 1;
```

From this analysis, the code reveals that `userInput` is compared against `asfaj`. Run the program again and verify this:
```
$ ./doubledutch 
Insert a string of 5 characters: asfaj
Access Granted
```

Access Granted. Format the input as flag and submit:
```
LHC{asfaj}
```

[1]:https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/