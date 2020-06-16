# Bribery

## Points: 180

## Challenge
Can you figure out how n00b cheated?

[ [n00b.pcap](n00b.pcap) ]

## Solution
Open up the pcap file in Wireshark. Filter for **irc** packets. Follow the conversation between n00b and RedWedge.

```
PRIVMSG #elite_haxorz :Can you tell me the flag for the that new forensics challenge on LHC?

:RedWedge!webchat@ip10-176-102-17.pa.pa.cox.net 
PRIVMSG #elite_haxorz :No. That's cheating.

PRIVMSG #elite_haxorz :I'll pay you.

PRIVMSG #elite_haxorz :0.02 BTC?

:RedWedge!webchat@ip10-176-102-17.pa.pa.cox.net 
PRIVMSG #elite_haxorz :Really?

PRIVMSG #elite_haxorz :Yeah. I need to proove to my friends that I'm l33t, and this is my task.

:RedWedge!webchat@ip10-176-102-17.pa.pa.cox.net 
PRIVMSG #elite_haxorz :I mean, I guess so, sure.

:RedWedge!webchat@ip10-176-102-17.pa.pa.cox.net 
PRIVMSG #elite_haxorz :Send it to 344aab9758bb0d018b93739e7893fb3a

PRIVMSG #elite_haxorz :Sent.

:RedWedge!webchat@ip10-176-102-17.pa.pa.cox.net 
PRIVMSG #elite_haxorz :Ok, fine. Just message BananaHammock19 on dalnet He'll give you the password. Just tell him Joey sent you. He'll know what it means.

PRIVMSG #elite_haxorz :Ok....
```

The Bitcoin address that RedWedge gives looks like a hash. Indeed both [gromweb][1] and [CyberChef][2] confirm this. Seems like RedWedge just wanted to RickRoll n00b.

```
input:  never gonna give you up
output: 344aab9758bb0d018b93739e7893fb3a        
```

Try to make contact with BananaHammock19 on dal.net:
```
/msg BananaHammock19 joey
```

In the chat:
```
[19:56] <n00b42> joey
[19:56] <BananaHammock19> Joey sent you? Well n00b42, I can't just GIVE you the answer, but I will say this: 'eajWg6oOn9d4Q' Good luck!!

[19:58] == BananaHammock19 [~BananaHam@50.149.237.35.bc.googleusercontent.com]
[19:58] ==  realname : BananaHammock19
[19:58] ==  channels : @#LHCBotmon
[19:58] ==  server   : halcyon.il.us.dal.net [valar dohaeris]
[19:58] ==  idle     : 0 days 0 hours 1 minutes 41 seconds [connected: Sat May 30 19:31:42 2020]
[19:58] == End of WHOIS
```

Identify this hash with `hash-identifier`:
```
$ hash-identifier
   #########################################################################
   #     __  __                     __           ______    _____           #
   #    /\ \/\ \                   /\ \         /\__  _\  /\  _ `\         #
   #    \ \ \_\ \     __      ____ \ \ \___     \/_/\ \/  \ \ \/\ \        #
   #     \ \  _  \  /'__`\   / ,__\ \ \  _ `\      \ \ \   \ \ \ \ \       #
   #      \ \ \ \ \/\ \_\ \_/\__, `\ \ \ \ \ \      \_\ \__ \ \ \_\ \      #
   #       \ \_\ \_\ \___ \_\/\____/  \ \_\ \_\     /\_____\ \ \____/      #
   #        \/_/\/_/\/__/\/_/\/___/    \/_/\/_/     \/_____/  \/___/  v1.2 #
   #                                                             By Zion3R #
   #                                                    www.Blackploit.com #
   #                                                   Root@Blackploit.com #
   #########################################################################
--------------------------------------------------
 HASH: eajWg6oOn9d4Q

Possible Hashs:
[+] DES(Unix)
--------------------------------------------------
```

The hash is potentially a DES ([Data Encryption Standard](https://en.wikipedia.org/wiki/Data_Encryption_Standard)) hash. 

Try cracking it using John the Ripper. Place the hash in a text file (bribery-hash.txt) and run John with the [rockyou](http://downloads.skullsecurity.org/passwords/rockyou.txt.bz2) wordlist from the [LHC rules](https://ctf.laptophackingcoffee.org/rules).
```
$ sudo john bribery-hash.txt --wordlist=rockyou.txt
Using default input encoding: UTF-8
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 256/256 AVX2])
Press 'q' or Ctrl-C to abort, almost any other key for status
18@Fart          (?)
1g 0:00:00:01 DONE (2020-06-02 13:41) 0.6896g/s 7998Kp/s 7998Kc/s 7998KC/s 18JoyMi1..1899901
Use the "--show" option to display all of the cracked passwords reliably
Session completed
```

Hash successfully cracked. Format as flag and submit:
```
LHC{18@Fart}
```

[1]:https://md5.gromweb.com/?md5=344aab9758bb0d018b93739e7893fb3a
[2]:https://gchq.github.io/CyberChef/#recipe=MD5()&input=bmV2ZXIgZ29ubmEgZ2l2ZSB5b3UgdXA