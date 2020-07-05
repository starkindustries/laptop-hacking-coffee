# The Heist

## Web: 700 Points

## Challenge

Cluckin' Bell has some of the best chicken in town, hack into their server and get me that recipe!

[ [Start](http://challenges.laptophackingcoffee.org:2364/) ]

## Solution

Nmap:
```
$ nmap -sC -sV challenges.laptophackingcoffee.org -p 2364 -Pn
Starting Nmap 7.80 ( https://nmap.org ) at 2020-07-05 08:47 MDT
Nmap scan report for challenges.laptophackingcoffee.org (35.237.149.50)
Host is up (0.062s latency).
rDNS record for 35.237.149.50: 50.149.237.35.bc.googleusercontent.com

PORT     STATE SERVICE VERSION
2364/tcp open  http    Apache httpd 2.4.38 ((Ubuntu))
|_http-server-header: Apache/2.4.38 (Ubuntu)
|_http-title: Site doesn't have a title (text/html; charset=UTF-8).

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 13.65 seconds
```

Pages:
* http://challenges.laptophackingcoffee.org:2364/?page=home
* http://challenges.laptophackingcoffee.org:2364/?page=menu
* http://challenges.laptophackingcoffee.org:2364/?page=legal

Try browsing to http://challenges.laptophackingcoffee.org:2364/?page=admin:
```
Warning: include(admin.php): failed to open stream: No such file or directory in /var/www/app/index.php on line 25
Warning: include(): Failed opening 'admin.php' for inclusion (include_path='.:/usr/share/php') in /var/www/app/index.php on line 25
```

Dirb:

* http://challenges.laptophackingcoffee.org:2364/images/
* http://challenges.laptophackingcoffee.org:2364/uploads/