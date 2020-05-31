# Double Dutch

## Reverse Engineering: 60 points

## Challenge

This one seems tougher to crack than the other one I sent you. See if you can figure out what the heck is going on here.

Note: Be sure to encase it in LHC{}

Credit: Benwick#5127

[doubledutch](doubledutch)

## Solution
Run the program. Enter a password. Access denied:
```
$ ./doubledutch 
Insert a string of 5 characters: 12345
Access Denied!
```

Try gdb. 
```
$ chmod +x doubledutch
$ gdb doubledutch
```


```
$ ./doubledutch 
Insert a string of 5 characters: asfaj
Access Granted
```

Format as flag:
```
LHC{asfaj}
```