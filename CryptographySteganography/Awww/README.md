# Awww

## Cryptography/Steganography: 125 Points

## Challenge
My 1337 GF sent me this and said she there's a lovely message in it for me, can you help me understand it?

Note: remember to encase in LHC{}

Credit: Delta#6862

[ [Love_You_Baby.png][1] ]

## Solution
The image contains shapes and alphanumeric characters. Why the shapes though? What if the shapes themselves also provided a clue to the message? What if the number of sides mean something?

![1]

Starting from left to right, top to bottom:

```
6 sides + c = 6c
3 sides + 0 = 30
7 sides + 6 = 76
3 sides + 3 = 33
2d (in the middle)
7 sides + 9 = 79
3 sides + 0 = 30
7 sides + 5 = 75
```

These looks like hex bytes, possible ASCII. Plug this into [CyberChef][2]:
```
input:  6c 30 76 33 2d 79 30 75
output: l0v3-y0u
```

Format as flag and submit:
```
LHC{l0v3-y0u}
```

[1]:./Love_You_Baby.png
[2]:https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto')&input=NmMgMzAgNzYgMzMgMmQgNzkgMzAgIDc1IA