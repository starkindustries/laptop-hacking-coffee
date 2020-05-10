# Leaky

## Points: 75

## Challenge
I've lost access to my Snapchat account and I can't remember the password. I think the email is DarkBlade5@yahoo.com. Please find my password and submit it as LHC{password-here}. Thanks!

(NOTE: This is an OSINT challenge, NOT a hacking challenge. Do NOT hack Snapchat.)

## Solution
OSINT stands for [open-source intelligence](https://en.wikipedia.org/wiki/Open-source_intelligence). I did not know that. I decided to google the email address in question. That search led me to this website:

https://osintframework.com/

This website provides an interactive node mapping of a collection of OSINT tools. I clicked **Email Address** and then **Breach Data**. This opened up a collection of websites like [Have I been pwned?](https://haveibeenpwned.com/). It also listed DeHashed. I searched dehash for the email, which gave a few results. 

https://www.dehashed.com/search?query=DarkBlade5%40yahoo.com

But the results were hidden: 

```
Data available but hidden. You must be authenticated to view search results.
```

I created an account to view the full results and got this:

```
Result #4090647
Email
darkblade5@yahoo.com
Password
blade21
```

The password is `blade21` and therefore, the flag is:
```
LHC{blade21}
```