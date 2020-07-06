# Poison

## Web: 350 Points

## Challenge

Someone is trying to leak all of LHC's user passwords, stop them before its too late!

[ [Start](http://challenges.laptophackingcoffee.org:666/) ]

Note: The server resets to default every 30 minutes. All progress will be lost

## Solution

```
Here I'm going to post the passwords for all of the LHC users. NOTE: I'm using this server as backup storage while reinstalling everything on my home machine. DO NOT DELETE FILES!
```

https://cyware.com/news/understanding-the-types-of-poisoning-attacks-ed39c024

```
$ nmap -sC -sV challenges.laptophackingcoffee.org -p 666
Starting Nmap 7.80 ( https://nmap.org ) at 2020-07-04 09:04 MDT
Note: Host seems down. If it is really up, but blocking our ping probes, try -Pn
Nmap done: 1 IP address (0 hosts up) scanned in 3.35 seconds
stark@kali:~/Desktop$ nmap -sC -sV challenges.laptophackingcoffee.org -p 666 -Pn
Starting Nmap 7.80 ( https://nmap.org ) at 2020-07-04 09:05 MDT
Nmap scan report for challenges.laptophackingcoffee.org (35.237.149.50)
Host is up (0.080s latency).
rDNS record for 35.237.149.50: 50.149.237.35.bc.googleusercontent.com

PORT    STATE SERVICE VERSION
666/tcp open  http    Apache httpd 2.4.25 ((Debian))
|_http-server-header: Apache/2.4.25 (Debian)
|_http-title: Site doesn't have a title (text/html; charset=UTF-8).

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 18.67 seconds
```

LHC channels suggested Nikto, which is readily available in Kali.

https://en.wikipedia.org/wiki/Nikto_(vulnerability_scanner)

```
$ nikto -host challenges.laptophackingcoffee.org -p 666
- Nikto v2.1.6
---------------------------------------------------------------------------
+ Target IP:          35.237.149.50
+ Target Hostname:    challenges.laptophackingcoffee.org
+ Target Port:        666
+ Start Time:         2020-07-05 20:10:32 (GMT-6)
---------------------------------------------------------------------------
+ Server: Apache/2.4.25 (Debian)
+ Retrieved x-powered-by header: PHP/7.2.11-2+0~20181015120801.9+stretch~1.gbp8105e0
+ The anti-clickjacking X-Frame-Options header is not present.
+ The X-XSS-Protection header is not defined. This header can hint to the user agent to protect against some forms of XSS
+ The X-Content-Type-Options header is not set. This could allow the user agent to render the content of the site in a different fashion to the MIME type
+ No CGI Directories found (use '-C all' to force check all possible dirs)
+ Apache/2.4.25 appears to be outdated (current is at least Apache/2.4.37). Apache 2.2.34 is the EOL for the 2.x branch.
+ Web Server returns a valid response with junk HTTP methods, this may cause false positives.
+ /test.php: PHP include error may indicate local or remote file inclusion is possible.
+ OSVDB-3233: /icons/README: Apache default file found.
+ OSVDB-3092: /test.php: This might be interesting...
+ 7865 requests: 0 error(s) and 9 item(s) reported on remote host
+ End Time:           2020-07-05 20:19:42 (GMT-6) (550 seconds)
---------------------------------------------------------------------------
+ 1 host(s) tested
```

No results from Gobuster 2.3-small.txt and 2.3-medium.txt

Visiting /index.php brings up the same page:

http://challenges.laptophackingcoffee.org:666/index.php


https://pentesterlab.com/exercises/php_include_and_post_exploitation/course