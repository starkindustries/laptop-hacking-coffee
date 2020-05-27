# Leaky

## Points: 75

## Challenge
I've lost access to my Snapchat account and I can't remember the password. I think the email is DarkBlade5@yahoo.com. Please find my password and submit it as LHC{password-here}. Thanks!

(NOTE: This is an OSINT challenge, NOT a hacking challenge. Do NOT hack Snapchat.)

## Solution
OSINT stands for [open-source intelligence](https://en.wikipedia.org/wiki/Open-source_intelligence). A quick google gives the following link:

https://osintframework.com/

This website provides an interactive node-map of a collection of OSINT tools. Click **Email Address** and then **Breach Data**. This opens up a collection of websites like [Have I been pwned?](https://haveibeenpwned.com/). It also lists DeHashed. Search DeHashed for the email: 

https://www.dehashed.com/search?query=DarkBlade5%40yahoo.com

A few results pop up. However, they are hidden: 

```
Data available but hidden. You must be authenticated to view search results.
```

Create an account and sign in to view the full results:

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