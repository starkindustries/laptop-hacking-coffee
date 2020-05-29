# What Hash

## Points: 75

## Challenge

I wrote a script in python to hide a hash of a text file. It's pretty much unbreakable, don't even bother trying.

707c20104fe9aaa3dc183cf4b0ea0778a1819994ad6cf254ad6cf25cd02b402c4310334

Note: The contents of the file is LHC{secret_string}

Credit: Delta#6862

[what_hash_v3.png](what_hash_v3.png)

## Solution
The script's `fixer` function hashes the input using MD5. Then the constants `y` and `w` are pre-pended and appended to the hashed variable `x` respectively. 
```
y = '707c20104fe9aaa'
w = '4ad6cf25cd02b402c4310334'
x = fixer(password)
z = y+x+w
```

This gives the resulting hashed string:
```
707c20104fe9aaa3dc183cf4b0ea0778a1819994ad6cf254ad6cf25cd02b402c4310334
```

First separate the `y` and `w` components from the result:
```
707c20104fe9aaa 3dc183cf4b0ea0778a1819994ad6cf25 4ad6cf25cd02b402c4310334
```

The remaining hash is:
```
3dc183cf4b0ea0778a1819994ad6cf25
```

Reverse search for this hash on [gromweb](https://md5.gromweb.com/?md5=3dc183cf4b0ea0778a1819994ad6cf25). Verify the hash on [CyberChef](https://gchq.github.io/CyberChef/#recipe=MD5()&input=bnVjbGVhcg).