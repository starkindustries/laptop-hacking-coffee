# Chemistry

## Points: 75

## Challenge
My GF got bored in chemistry class and sent me this:

`31392f337c31347c332f317c332f31327c32302f397c332f31327c31397c31342f317c3139`

Can you help me decode it?

Note: Be sure to encase in LHC{} 

Credit: Delta#6862

## Solution
Baking the cipher with [CyberChef][1] gives:
```
input:  31392f337c31347c332f317c332f31327c32302f397c332f31327c31397c31342f317c3139
output: 19/3|14|3/1|3/12|20/9|3/12|19|14/1|19
```

Convert via A1Z26 cipher:
```
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
A B C D E F G H I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z

input:   19/3|14|3/1|3/12|20/9|3/12|19|14/1|19
output:   S/C| N|C/A|C/L | T/I|C/L | S| N/A| S
elements: Sc   N  Ca  Cl   Ti   Cl   S  Na   S
```

These are elements. Convert to their atomic number:
```
 Sc N Ca Cl Ti Cl  S Na  S
 21 7 20 17 22 17 16 11 16
```

Convert numbers back to letters:
```
input:  21 7 20 17 22 17 16 11 16
output: ugtqvqpkp
```

ROT13 by `-2`:
```
input:  ugtqvqpkp
output: serotonin
```

Format as flag:
```
LHC{serotonin}
```

[1]:https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto')&input=MzEzOTJmMzM3YzMxMzQ3YzMzMmYzMTdjMzMyZjMxMzI3YzMyMzAyZjM5N2MzMzJmMzEzMjdjMzEzOTdjMzEzNDJmMzE3YzMxMzk