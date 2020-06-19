# Not True Encryption

## Reverse Engineering: 75 points

## Challenge

I got infected with a piece of ransomware, I was able to find a copy of the module that checks for the right password before decrypting. Can you figure out what the password is and send it to me please?

Note: Be sure to encase in LHC{}

[ [RansomwareDecrypter.exe](RansomwareDecrypter.exe) ]

## Solution


https://schlafwandler.github.io/posts/mrmcdctf2019-slicer/
Note the name here: the ‘DAT_’ reflects that the variable is located in the data segment, not on the stack. DAT_00403568 therefore is a global variable, not a local one.

