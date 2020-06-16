# Truck Stop Fun

## Points: 75

## Challenge
While driving from Hawaii to New Mexico Susan really had to go to the restroom. Upon entering her favorite truck stop bathroom she’s sees the following. What is this bizarre sticker? There has to be some sort of clue in this photo?

Credit: TLSHack

[ [truck_stop_fun][1] ]

## Solution
Dump all strings:
```
$ strings truck_stop_fun.jpg
...
N5VSA43PEBRGC43JMNQWY3DZEBUW2IDNN5XGW6I=
```

Plug into [CyberChef][2]:
```
input:  N5VSA43PEBRGC43JMNQWY3DZEBUW2IDNN5XGW6I=
output: ok so basically im monky
```

Format as flag and submit:
```
LHC{ok so basically im monky}
```

[1]:./truck_stop_fun.jpg
[2]:https://gchq.github.io/CyberChef/#recipe=Magic(3,false,false,'')&input=TjVWU0E0M1BFQlJHQzQzSk1OUVdZM0RaRUJVVzJJRE5ONVhHVzZJPQ