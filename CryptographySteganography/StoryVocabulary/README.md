# Story Vocabulary

## Points: 250

## Challenge

Can you find the hidden message in this image?

Credit: goeo_#0527

Hint 1: If you're stuck, just look a little closer.

Hint 2: [This should give you the right idea](https://www.imdb.com/title/tt2120120/)

[story_vocabulary.png][1]

## Solution

$ java -jar stegsolve.jar

[How to read the RGB value of a given pixel in Python?][1]

Exiftool. Nothing interesting.
```
$ exiftool story_vocabulary.png 
ExifTool Version Number         : 10.80
File Name                       : story_vocabulary.png
Directory                       : .
File Size                       : 1871 kB
File Modification Date/Time     : 2020:05:28 22:54:35-06:00
File Access Date/Time           : 2020:06:03 22:50:17-06:00
File Inode Change Date/Time     : 2020:05:28 22:55:01-06:00
File Permissions                : rw-rw-r--
File Type                       : PNG
File Type Extension             : png
MIME Type                       : image/png
Image Width                     : 1920
Image Height                    : 1080
Bit Depth                       : 8
Color Type                      : RGB
Compression                     : Deflate/Inflate
Filter                          : Adaptive
Interlace                       : Noninterlaced
Image Size                      : 1920x1080
Megapixels                      : 2.1
```

Placeholder
```
$ exif story_vocabulary.png 
Corrupt data
The data provided does not follow the specification.
ExifLoader: The data supplied does not seem to contain EXIF data.
```

Placeholder
```
$ sudo apt install stegosuite
```

```
You got 3 pictures all different
Same position
Same size
Everything same
You need to match it by color
not same color

then if I isolate each plane I get these: red plane1, green plane1, blue plane1

SarastroToday at 4:35 PM
Yeah but in colors



I'm still stuck on story vocab. I tried assigning them with colors like u hinted at. and then I recombined the 3 sections. I tried different "filters" where I would layer each differently. I tried isolating 2 colors/1 color, overlaying different color combinations. Wondering if this is the right direction. (tiny image attached)

SarastroToday at 3:25 AM
It's a good path. Honestly, at this point, your best attempt would just to look at it. Try seeing it, matching it, extracting it, analyzing it. So many ways you could do stuff with this without any crypto tools

delta06/04/2020
Try looking at LCD monitors and specificly color blending (not sure if thats the right term)


```

```
An 8-bit colormap is a typical place where things are hidden in a steganography challenge. After some lazy searching, we find a tool to change the palette (or colormap) of a PNG using Python on Stack Overflow.
https://github.com/ctfs/write-ups-2014/tree/master/plaid-ctf-2014/doge-stege
```

https://georgeom.net/StegOnline/checklist
https://georgeom.net/StegOnline/extract


https://stegosuite.org/
https://stackoverflow.com/questions/9542359/does-png-contain-exif-data-like-jpg#:~:text=Original%3A%20PNG%20does%20not%20embed,to%20define%20new%20chunk%20types.

https://www.blackmoreops.com/2017/01/11/steganography-in-kali-linux-hiding-data-in-image/
https://resources.infosecinstitute.com/steganalysis-x-ray-vision-hidden-data/
http://www.guillermito2.net/stegano/tools/

[1]:./story_vocabulary.png
[2]:https://stackoverflow.com/questions/138250/how-to-read-the-rgb-value-of-a-given-pixel-in-python

