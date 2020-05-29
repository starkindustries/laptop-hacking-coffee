# Date Night

## Points: 100

## Challenge

My girlfriend asked me to pick up a movie on my way home and sent me this when I asked what movie to watch. Can you help me figure out what movie to get?

Note: Encase the flag in LHC{}

Credit: Delta#6862

[1394.png][1]

## Solution
Turns out the is a red herring.
![image][1]

Similar to the challenge [Awww](../Awww), the shapes and characters give the following hex values:
```
6e 6f 74 2d
74 68 65 2d
66 6c 61 67 3a 29
```

Plug this into [CyberChef][2]. This is clearly not the flag.
```
input:  6e 6f 74 2d 74 68 65 2d 66 6c 61 67 3a 29
output: not-the-flag:)
```

Dump all string values:
```
$ strings 1394.png
...
A New Hope
```
Place the movie in flag format:
```
LHC{A New Hope}
```

[1]:./1394.png
[2]:https://gchq.github.io/CyberChef/#recipe=From_Hex('Auto')&input=NmUgNmYgNzQgMmQKNzQgNjggNjUgMmQKNjYgNmMgNjEgNjcgM2EgMjk