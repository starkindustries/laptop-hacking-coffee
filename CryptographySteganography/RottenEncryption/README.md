# Rotten Encryption

## Points: 75

## Challenge

I've gotten access to a leaked database but it looks like it's encrypted with something custom.

My password "smartfridge" appears to be

25 23 3 26 26 16 20 17 10 17 7

I urgently need to get access to another account who's password shows up as

19 25 16 19 11 35 4 29 25 19 16 13 25 29

Please find it for me.

Note: Be sure to encase it in LHC{}

Credit: Delta#6862

## Solution

Compare the plaintext password length to the cipher length. They are the same length. Convert the password `smartfridge` to a A1Z26 cipher using [CyberChef](https://gchq.github.io/CyberChef/#recipe=A1Z26_Cipher_Encode('Space')&input=c21hcnRmcmlkZ2U):
```
input:  smartfridge
output: 19 13 1 18 20 6 18 9 4 7 5
```

Compare CyberChef's cipher with the given cipher:
```
plaintext:   s   m  a  r  t   f  r  i  d   g  e
Challenge:  25  23  3 26 26  16 20 17 10  17  7
CyberChef:  19  13  1 18 20   6 18  9  4   7  5
Difference: +6 +10 +2 +8 +6 +10 +2 +8 +6 +10 +2
```

The pattern `+6 +10 +2 +8` emerges. The encryption scheme adds these offsets and repeats process for each character.

```
Cipher:     19 25 16 19 11 35 4 29 25 19 16 13 25 29
Offsets:     6 10  2  8  6 10 2  8  6 10  2  8  6 10
Difference: 13 15 14 11  5 25 2 21 19  9 14  5 19 19
```

Plug this into CyberChef:
```
input:  13 15 14 11 5 25 2 21 19 9 14 5 19 19
output: monkeybusiness
```

Format as flag:
```
LHC{monkeybusiness}
```