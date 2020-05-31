# Password?

## Miscellaneous: 80 points

## Challenge

I found another service that looks similar to the last, but this one asks for a password.

challenges.laptophackingcoffee.org:3345

## Solution
Connect via netcat. Try entering a few passwords:
```
$ nc challenges.laptophackingcoffee.org 3345
Please enter your password: password
Please send your password as an MD5 for security.
Please enter your password: 5f4dcc3b5aa765d61d8327deb882cf99
Incorrect password.
Please enter your password: 
```

Is this a bruteforce?