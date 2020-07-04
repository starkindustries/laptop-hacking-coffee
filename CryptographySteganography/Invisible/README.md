# Invisible

## Cryptography/Steganography: 175 Points

## Challenge

Help, I can’t find anything useful here! My friend gave me a hint, he says the filename is a keyboard cipher shifted two keys. What does that even mean?

Credits: Azotos#6989

[ [tvph.txt][1] ]

## Solution

The file will not open in a normal text editor. Check the file type:

```
$ file tvph.txt 
tvph.txt: JPEG image data [...]
```

The file is actually a JPG. Rename the extension to **.jpg**. It is in fact an image:

![watch_doge](./tvph.jpg)

The text **WATCH_DOGE** in the picture is **not** the flag. It is a red herring. Go back to the hint in the challenge text:
> he says the filename is a keyboard cipher shifted two keys

The filename is **tvph.txt**. Shift **tvph** two keys to the left:
```
t >> e
v >> x
p >> i
h >> f
```

The result is: **exif**, which hints that the image has exif data. Below are the interesting bits of data:
```
$ exiftool tvph.jpg 
ExifTool Version Number         : 10.80
File Name                       : tvph.jpg
...
Image Description               : 6210274434052f20fcb83e1d0f492204fcb11884..88ae6f8febf29f28782f7c5db164d0c8736fd110
Camera Model Name               : 9ae345e1b619cfd86b5f01360ee61745
Resolution Unit                 : None
Software                        : 5292c527e0e77b38813bc63bdac7ddd5
Artist                          : b3e37c058e373af3b1ca2c7c5bae8051595ee985
...
```

The image description, camera model, software, and artist are all hashes. Run them through [MD5decrypt][2] and [MD5Online][3] to unhash them:
```
Image Description:
6210274434052f20fcb83e1d0f492204fcb11884 (SHA1): passphrase
88ae6f8febf29f28782f7c5db164d0c8736fd110 (SHA1): isartist

Camera Model Name
9ae345e1b619cfd86b5f01360ee61745 (MD5): [no result found]

Software
5292c527e0e77b38813bc63bdac7ddd5 (MD5): steghide

Artist
b3e37c058e373af3b1ca2c7c5bae8051595ee985 (SHA1) : rickastley
```

The image description reveals that the **passphrase is artist**. The artist description decrypts to **rickastley**. And the software description reveals the tool used: **steghide**.

Install steghide. Run it. Enter **rickastley** as the passphrase. 
```
$ sudo apt install steghide
$ steghide extract -sf tvph.jpg
Enter passphrase: 
wrote extracted data to "hidden.jpg"
```

Open up the new [hidden.jpg][4] file:

![hidden][4]

Get the flag:
```
LHC{n1Tr0G3N}
```

[1]:./tvph.txt
[2]:https://md5decrypt.net
[3]:https://www.md5online.org/
[4]:./hidden.jpg