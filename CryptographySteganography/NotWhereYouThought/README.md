# Not Where You Thought

## Points: 75

## Challenge
I stumbled upon this file recently, its confusing the heck out of me. Can you help me out?

Credits: programme-zero#4997

[SecureBackup.exe](./SecureBackup.exe)

## Solution
This one is interesting. Start with **binwalk**:
```
$ binwalk SecureBackup.exe 
DECIMAL       HEXADECIMAL     DESCRIPTION
------------------------------------------------------------------
0             0x0             Microsoft executable, portable (PE)
10416         0x28B0          PNG image [...]
10457         0x28D9          Zlib compressed data, default compression
58936         0xE638          XML document, version: "1.0"
```

There is an executable, a PNG image, and an XML document. The XML document does not have anything interesting. Open up the .exe in Ghidra and examine the PNG image. The image shows the word "Princess."

Extract the PNG to its own file. A PNG contains zlib compressed data. Therefore the byte range of the PNG is from 10416 (at PNG image start) to 58935 (just before the XML document).

```
$ dd if=SecureBackup.exe of=princess.png bs=1 skip=10416 count=48520
```
The count value `48520` is the result of `58936` minus `10416`, which is the number of bytes from the PNG image header to the end of the zlib data. Now the image is extracted to [princess.png][1]

![princess][1]

Open up this image with [Stegsolve][3]. To download Stegsolve:
```
$ wget http://www.caesum.com/handbook/Stegsolve.jar -O stegsolve.jar
chmod +x stegsolve.jar
```

Run Stegsolve:
```
$ java -jar ../../Tools/stegsolve.jar
```

A tiny window will pop up. Click **File**, **Open**, and select the princess image. Click the right arrow **>** to scroll through the various planes. Take a close look at **red plane 0**:

![red-plane0][4]

There is short line of white noise at the top. This is also true for **green plane 0** and **blue plane 0**. The planes refer to the bit number of the color component. Each color is represented by three bytes: red, green, and blue. Plane 7 is the most significant bit (MSB). Plane 0 is the least significant bit (LSB).

```
               MSB           LSB
               v             v
red component: 0 0 0 0 0 0 0 0
               ^             ^
               plane7        plane0
```

Some sort of data is definitely hidden in the LSB of the image colors. Python's PIL library can extract the LSB data.
```
from PIL import Image
```

The full script is [here][5]. Run the script:
```
$ python3 script.py
```

Get the flag:
```
LHC{St3gn0F0rN00bs}
```



## Resources
* [Stegsolve Repository][3]
* [Stegsolve Jar File][2]
* [Ghidra][6]

[1]:./princess.png
[2]:../../Tools/stegsolve.jar
[3]:https://github.com/zardus/ctf-tools/blob/master/stegsolve/install
[4]:./princess-red-plane0.bmp
[5]:./script.py
[6]:https://ghidra-sre.org/