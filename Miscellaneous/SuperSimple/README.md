# Super Simple

## Miscellaneous: 350 points

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