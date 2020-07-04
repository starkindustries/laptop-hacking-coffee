# Not Binary

## Cryptography/Steganography: 30 Points

## Challenge
11 11111 010 000 0 101 11111 100 00011 00 000 101 11111 11111 0100

Don't forget to submit the flag with the LHC{} syntax

## Solution
The title provides a big hint that the code is not binary. So what else can it be? Note the spacing that separates the characters. Also the zeros `000`, `0`, and `00` must mean something different. So what other non-binary codes use just two different symbols to convey a message? Morse code comes to mind.

Load up [CyberChef](https://gchq.github.io/CyberChef), place the non-binary string into the input. Pull a **Find/Replace** function into the recipe zone. Find a one and replace with a dash.

```
Find
1
Replace
-
```

Add another **Find/Replace** function and this time find zero and replace with a dot.

```
Find
0
Replace
.
```

Then add the **From Morse Code** function. Letter delimiter should be set to space. This recipe gives the following output:
```
M0RSEK0D3ISK00L
```

Format as flag:
```
LHC{M0RSEK0D3ISK00L}
```