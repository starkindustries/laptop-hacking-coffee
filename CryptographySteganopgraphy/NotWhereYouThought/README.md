# Not Where You Thought

## Points: 75

## Challenge
I stumbled upon this file recently, its confusing the heck out of me. Can you help me out?

Credits: programme-zero#4997

## Solution
**IN PROGRESS**
```
2003  binwalk SecureBackup.exe 
2004  dd if=SecureBackup.exe skip=10416 bs=1 count=$((10457-10416)) of=picture.png
2005  file picture.png 
2006  sh
2007  dd if=SecureBackup.exe skip=10457 bs=1 count=$((58936-10457)) of=data.zlib
```