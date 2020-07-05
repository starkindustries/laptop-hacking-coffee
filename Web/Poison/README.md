# Poison

## Web: 350 Points

## Challenge

Someone is trying to leak all of LHC's user passwords, stop them before its too late!

[ [Start](http://challenges.laptophackingcoffee.org:666/) ]

Note: The server resets to default every 30 minutes. All progress will be lost

## Solution

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