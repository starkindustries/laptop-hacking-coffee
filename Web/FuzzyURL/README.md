# Fuzzy URL

## Web: 25 points

## Challenge

I can't remember what directory I left my password in, can you find it?

## Solution

The challenge title hints at fuzzing the URL. Try **dirb** against the site:
```
$ dirb http://challenges.laptophackingcoffee.org:8888

-----------------                                                                
DIRB v2.22                                                                       
By The Dark Raver
-----------------

START_TIME: Sun May 31 20:20:16 2020
URL_BASE: http://challenges.laptophackingcoffee.org:8888/
WORDLIST_FILES: /usr/share/dirb/wordlists/common.txt

-----------------

GENERATED WORDS: 4612                                                          

---- Scanning URL: http://challenges.laptophackingcoffee.org:8888/ ----
+ http://challenges.laptophackingcoffee.org:8888/index.html (CODE:200|SIZE:370)                               
==> DIRECTORY: http://challenges.laptophackingcoffee.org:8888/recoverpassword/                                
                                          
...

-----------------
END_TIME: Sun May 31 20:30:04 2020
DOWNLOADED: 9029 - FOUND: 2
```

Success! Dirb found a webpage:
```
http://challenges.laptophackingcoffee.org:8888/recoverpassword/
```

Visit that page and grab the flag:
```
LHC{p455w0rd_r3c0v3ry}
```