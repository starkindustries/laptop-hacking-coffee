# Air Traffic

## Points: 150

## Challenge
One of our agents went dark and we believe is trying to communicate with us. We received a message from an unknown sender that just appears to be someone's flight plans. Can you help us figure out where he is?

Note: Be sure to encase the flag in LHC{}

Credit: Delta#6862

[flight_plan.txt](./flight_plan.txt)

## Solution
After searching for "flight plan" on LHC discord, this clue popped up:

> Pyro12/25/2019  
You can plan flight path

Open google maps, search all the airports and connect the dots. The result is this map:

[Air Traffic][1]

Take the flight plan given and simplify it to an airport to airport plan instead of a list of flights. The result is this:
```
MARCH: HPX-CYYC-XBF-ATL

APRIL: AMV-CYYC-ATL-AAH-ATL-ACA-AGA

MAY:   ADD-KBP-ABD-ABS-BZD

JUNE:  CYYC-HPX-BZD-HFE
```

Connect the airports for March to form a "P":

![march][2]

Connect the airports for April to form "E". The google map lines don't work well in this case. The letter "E" is easier to see if the airports are connected with straight lines:

![april][3]

Connect the airports for May to form "R":

![may][4]

Connect the airports for June to form "U":

![june][5]

String these letters together and format as flag:
```
LHC{peru}
```

[1]:https://www.google.com/maps/d/drive?state=%7B%22ids%22%3A%5B%2217BBxmM3MUlvhBW4IKso-Rg_ObqsOdU5o%22%5D%2C%22action%22%3A%22open%22%2C%22userId%22%3A%22100168907418177694346%22%7D&usp=sharing
[2]:screenshot1.png
[3]:screenshot2.png
[4]:screenshot3.png
[5]:screenshot4.png