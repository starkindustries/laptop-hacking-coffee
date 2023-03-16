# Lost Passwords

## Forensics & OSINT: 100 Points

## Challenge
My boss Susan and our other admin Larry just called and said they forgot the shared Twitter password for our company. She said she stored it in a spreadsheet somewhere. They’re both a bunch of dorks for forgetting it. Either way, maybe you can help me find it anyway?

Credit: TLSHack

## Solution

* https://en.wikipedia.org/wiki/Google_hacking
* https://exposingtheinvisible.org/guides/google-dorking/
* https://kit.exposingtheinvisible.org/en/how/google-dorking.html
* https://www.exploit-db.com/google-hacking-database

Things to try:
1. site: narrow down to LHC url and IP address. 
2. filetype: xlsx, xls, csv, ods, pdf, 

Attempts:
```
filetype:csv twitter
filetype:csv passwords
filetype:xls twitter
filetype:xls passwords
filetype:ods twitter
filetype:ods passwords
filetype:xlsx twitter
filetype:xlsx passwords
allintext:susan larry
allintext:susan larry company
allintext:susan larry twitter
allintext:larry susan
allintext:larry susan company
allintext:larry susan twitter
intitle:"index of"
intitle:"index of" passwords
intitle:"index of" passwords susan
intitle:"index of" passwords larry
intitle:"index of" passwords twitter
```

https://cybersecurity.wtf/passwords/credentials.txt
https://wikileaks.org/sony/docs/bonus/1/Password/

```
admin:416e69eeac071fd732910d746a91423c
operator:2de5145528daf46ae3d872f40add0783
```
