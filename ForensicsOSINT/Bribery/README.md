# Bribery

## Points: 180

## Challenge
Can you figure out how n00b cheated?

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
\msg BananaHammock19 test
[08:02] *BananaHammock19* test
[08:02] == No such nick/channel: BananaHammock19
```

After asking the LHC Discord if BananaHammock19 still exists, they reply:
> It’s down with the web challenges

[1]:https://md5.gromweb.com/?md5=344aab9758bb0d018b93739e7893fb3a
[2]:https://gchq.github.io/CyberChef/#recipe=MD5()&input=bmV2ZXIgZ29ubmEgZ2l2ZSB5b3UgdXA