# Lost Passwords

## Forensics & OSINT: 100 Points

## Challenge
My boss Susan and our other admin Larry just called and said they forgot the shared Twitter password for our company. She said she stored it in a spreadsheet somewhere. They’re both a bunch of dorks for forgetting it. Either way, maybe you can help me find it anyway?

Credit: TLSHack

## Solution

https://en.wikipedia.org/wiki/Google_hacking
https://exposingtheinvisible.org/guides/google-dorking/
https://kit.exposingtheinvisible.org/en/how/google-dorking.html

Things to try:
1. site: narrow down to LHC url and IP address. 
2. filetype: xlsx, xls, csv, ods, pdf, 

Attempts:
```
filetype:csv twitter
filetype:xls twitter
filetype:ods twitter
```