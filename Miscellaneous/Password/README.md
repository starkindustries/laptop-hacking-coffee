# Password?

## Miscellaneous: 80 Points

## Challenge

I found another service that looks similar to the last, but this one asks for a password.

challenges.laptophackingcoffee.org:3345

## Solution
Connect via netcat. Enter a few passwords:
```
$ nc challenges.laptophackingcoffee.org 3345
Please enter your password: password
Please send your password as an MD5 for security.
Please enter your password: 5f4dcc3b5aa765d61d8327deb882cf99
Incorrect password.
Please enter your password: 
```

Is this a brute force challenge? Yes. 

Draft up a script that will automatically send password hashes to this challenge. Use the [rockyou](../../Tools/rockyou.txt) password list given in the rules. 

When using netcat, a newline character `\n` is sent at the end of the user's input string. The server receives this and truncates the last character of the input. When sending data with python, an extra byte needs to be tacked onto the end so that the server can truncate this extra byte. In the script, an extra `0` is added:
```
pwHash = hashlib.md5(password.encode('utf-8')).hexdigest() + "0"
```

This is the full script: [script.py](script.py). Run the script and wait for the flag:
```
$ python3 script.py challenges.laptophackingcoffee.org 3345
...
Trying: [isaiah]
Trying: [christmas]
Trying: [cesar]
Trying: [lolipop]
Password: lolipop
Response:  LHC{7cP8rU73d}
```