# Scam

## Forensics & OSINT: 75 Points

## Challenge
This guy tricked me into giving him my friend's Snapchat password. Help!

Credit: ObjectiveAct#0281

[ [scam.pcap](./scam.pcap) ]

## Solution
Open the given **scam.pcap** file in any text editor.

```
$ cat scam.pcap
```

The chat log mentions:
> a 7-zip file with the same password as his snapchat

It also provides a link a git repo:
> https://github.com/LHCScamCTF/CTF

The repo contains a 7z zipped file. The README gives a hint about the flag location:
> What does the file include?  
[...] I've stored some LHC flags there

The README also has a weird Bitcoin address:
> Feel free to send me something on my Bitcoin  "WW91V2lsbE5ldmVyR3Vlc3NUaGlzUGFzc3dvcmQ="

Convert the address from base64 using [CyberChef](https://gchq.github.io/CyberChef/#recipe=From_Base64('A-Za-z0-9%2B/%3D',true)&input=V1c5MVYybHNiRTVsZG1WeVIzVmxjM05VYUdselVHRnpjM2R2Y21RPQ):
```
input:  WW91V2lsbE5ldmVyR3Vlc3NUaGlzUGFzc3dvcmQ=
output: YouWillNeverGuessThisPassword
```

Make sure 7zip is installed:
```
$ sudo apt install p7zip
```

Extract the 7z file using the decoded Bitcoin address as the password:
```
$ 7z x CTF.7z 

7-Zip [64] 16.02 : Copyright (c) 1999-2016 Igor Pavlov : 2016-05-21
p7zip Version 16.02 (locale=en_US.UTF-8,Utf16=on,HugeFiles=on,64 bits,4 CPUs Intel(R) Core(TM) i5-6600 CPU @ 3.30GHz (506E3),ASM,AES-NI)

Scanning the drive for archives:
1 file, 823 bytes (1 KiB)

Extracting archive: CTF.7z

Enter password (will not be echoed):
--
Path = CTF.7z
Type = 7z
Physical Size = 823
Headers Size = 295
Method = LZMA2:12 7zAES
Solid = +
Blocks = 1

Everything is Ok

Folders: 1
Files: 4
Size:       714
Compressed: 823
```

Extract successful. Find root.txt in the extracted folder. It contains:
```
4C48437B546865466C61674973456173797D
```

It looks like a hex string. Plug this string into [CyberChef](https://gchq.github.io/CyberChef/#recipe=From_Hex('None')):

```
input:  4C48437B546865466C61674973456173797D
output: LHC{TheFlagIsEasy}
```