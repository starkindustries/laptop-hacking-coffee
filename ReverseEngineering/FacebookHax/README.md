# Facebook Hax

## Points: 50

## Challenge

The CTO at MySpace recently heard that the Facebook app developers had nested their Firebase auth token in their app. Knowing that MySpace is about to make a big comeback he’s asked the best members of his team to reverse engineer the Facebook Lite app and get him that auth token! One of his engineers used to be a developer at Facebook. While he doesn’t remember the whole auth token he does remember that it started with “AIzaSyBWJZPw7wVi”.

Credit: TLSHack

[com.facebook.mlite.apk](./com.facebook.mlite.apk)

## Solution

Check the file type:
```
$ file com.facebook.mlite.apk 
com.facebook.mlite.apk: Zip archive data, at least v2.0 to extract
```

It's a zipfile. Unzip it:
```
$ unzip com.facebook.mlite.apk -d facebookdir
```

Find the string mentioned in the challenge text:
```
$ cd facebookdir
$ grep -nr AIzaSyBWJZPw7wVi .
Binary file ./resources.arsc matches
$ strings ./resources.arsc | grep AIzaSyBWJZPw7wVi
''AIzaSyBWJZPw7wVi-NQEViQV9ZnadO-xbX4S8o0
```

Found it. Enter this in flag format:
```
LHC{AIzaSyBWJZPw7wVi-NQEViQV9ZnadO-xbX4S8o0}
```