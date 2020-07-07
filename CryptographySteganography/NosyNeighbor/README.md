# Nosy Neighbor

## Cryptography/Steganography: 300 Points

## Challenge
I think my friend might be involved with the feds! I intercepted a message to him:
```
8d66f329e9df55a5f0cf6007196f39dc87eea9c1bdaff77a779784903a90e3b42a2cce315179f550ad606deadeb392f93dbc45f01af1497f218b8dec3786680f88734425eb8050b52b8c8f02698b91dea0f3d25fbcda569acbf85bd05069dc9e3625c73c0d5dfad341e9dbee80c7fc52b77bc9de17c7431d1944690a928803ab49ada9428041fb51f8936673685e5fbe422cc541741b91d424702f490b394bed313b23486a1b5d102ca81ae537221ed2babca8818a1ee51170f500e22e04d1e3df1279536f33bbab2cfa1f2f3e36fd96818903394b077875208933fd303c8b094ea32bba9319815728eaaa89df969aa41b3ae1f18060c1e223d840adaf4845e7ce3cc685a8fc562c2b51a6e9b258d6e55d8f6980d6ad11aa813c66fff0e41ebb5bc17879603d9fed335972af7995485ddbd6a3b5dc6b6438c5d304b85cda031fc88bbee0a54f6fc2e5c4f66bcb8d3f6eacd34e885a56f88292d9a62846def34d2cfbc0c0fd5f7d695dec1979c104a6b65959be5d69d0adcceb086b3b3dd0ef7f3c8d60d325425ad7292d9ecafb04a172007d723d40e1e350b8346b675d337b851dd558ef8ca02e3c3fea71ad33dcd4c8b1d47da07e115b5f9cc9346ed6ccaecb81ff1a9a4ddaeeb1f173f6baff0837c133d95d1b96a5b80f52d115074bd2ecdd8f96a681cc4ad579d4d4bde48dfc30ca840ccbf66cc4df5066ce8a6f2dffb0ab
```
I remember that I have his public key on file:
```
-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEA00GymhB9KGIrxEbMYkWy
KhXGBs4JOsfjREljNmRy6YckWQWpqaQZEFR1G24Osr5XAck4kfDXWF8dU6ca6CNu
0tswZxl4zhkgIYEprXloC55BUzQYZQZkBPSBiaG92KQAva3HI8Cj1gAVM/TCdIhL
hQGJTUs0jEmNaj+KRPANBXDXlAaxOVWWZjXrUH9/NhGq1DdBolNvZ6GnK+cY5dXD
ASHHRXUYGb4RAImOI87LU3gT8TpCdAbPsAoLbtUihw92QKDYP73gUwvynYwj8Uos
mGvjfEU1I4OPVuDNamX5sWTcmDZVHDiULnOxlxY+M9kz+JT0ubS9UTSSVsFesc+M
9VEbHeYJeg4cO/RTXkD3F/Js0U7fv7D+1iqk3QzqoQWCPgtQqblPEzTalOMCwiUJ
JC1qNxW3KgljJBnKQwx5VvyS6MkQE/Afl1VI+h0PtrQAmVwhwjbUCsZTbDsHTw7U
Qs8UQ95oth+lruDGRs4/cwf6oKSj6SJ+nuztYccrG8pdvFyQFk+lSn0AQg917brF
r4gQi24fNLghn2MCNBKb1EXeXZUxQDU2Zfw3clYsptHEfhNBHqzCXHwSJcg2P444
tTTDxZPcsbgistnCqYyeOcttGah4j28oAhodIxlYUUgcUwSa+qiStS1rCc/7Ovnn
1vqm6UmZTqe2aihE3s+SMwsCAwEAAQ==
-----END PUBLIC KEY-----
``` 
and not only that, but my key was also created with the same modulus:
```
 -----BEGIN RSA PRIVATE KEY-----
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
-----END RSA PRIVATE KEY-----
```
Can you crack his message?

Credits: IOException#6405

## Solution

### Understand the RSA Algorithm

The RSA explanations on [CrypTool][1] and [Wikipedia][2] are very insightful. The following is based on the explanation from CrypTool.

**Prime Factors**

Select two primes **p** and **q**:
```
p = 11
q = 13
```

Calculate **n = p * q**:
```
n = p * q
  = 11 * 13
  = 143
```

**Public Key**

Now select an exponent **e**, where **e** and **n** do not have a common divisor:
```
e = 23
```

The public key consists of module **n** and **e**.

**Secret Key**

RSA uses the Euler **φ** function of **n** to calculate the secret key. This is defined as:
```
φ(n) = (p - 1) * (q - 1)
```

Calculate **φ** with the two primes already selected:
```
φ(n) = (11 - 1) * (13 - 1)
     = (10) * (12)
     = 120
```

It is important for RSA that the value of the **φ** function is coprime to **e** (the largest common divisor must be 1).
```
gcd(e, φ(n)) = 1
```

The secret key also consists of **n** and a **d** with the property that **e * d** is a multiple of **φ(n)** plus one. Expressed in formulas, the following must apply:
```
e * d = 1 (mod φ(n))
```
Divide both sides by **e** to get:
```
d = 1/e (mod φ(n))
  = e^-1(mod φ(n))
```

Therefore, **d** is the [modular multiplicative inverse][3] of **e** with respect to modulus **φ(n)**.

**Encryption and Decryption**

To encrypt a message **m**:
```
m' = m^e mod n
```

To decrypt:
```
m'' = m'^d mod n
```

Since **e** and **d** were chosen appropriately:
```
m'' = m
```

Values **e** and **d** can be arbitrarily large. In order to calculate such large exponents, RSA algorithms take advantage of [modular exponentiation][4]. This [YouTube video][5] by GVSUmath clearly explains the concept. The `pow` function in python implements it:
```
# Return x to the power y; if z is present, return x to the power y, modulo z 
pow(x, y[, z])
```

### Implement RSA in Python

Piece together all the equations above into a python [script](script.py). To implement the mod-inverse function, refer to this StackOverflow answer: [Modular multiplicative inverse function in Python
][6].

### Abstract Syntax Notation One (ASN.1)

The RSA public and private keys are encoded in [ASN.1][7] format. ASN.1 decoders are available online, such as the tools from [phpseclib][8] and [lapo.it][9]. Decode the public key with one of these tools. This is the result from [lapo.it][9]:
```
ASN.1 JavaScript decoder
SEQUENCE (2 elem)
  SEQUENCE (2 elem)
    OBJECT IDENTIFIER 1.2.840.113549.1.1.1 rsaEncryption (PKCS #1)
    NULL
  BIT STRING (1 elem)
    SEQUENCE (2 elem)
      INTEGER (4096 bit) 861851863518312589931294230347884084604096807236140236534310925215737...
      INTEGER 65537
```

This decoded text contains some vague information. However, this [StackOverflow answer][10] clearly explains each component of the decoded data. Convert the public key base64 string into hex using [CyberChef](https://gchq.github.io/CyberChef/). Then breakdown each component as explained in the StackOverflow answer. This is the result:
```
30 82 02 22             ; 30=SEQUENCE
|  30 0d                ; 30=SEQUENCE
|  |  06 09             ; 06=OBJECT_IDENTIFIER (0x09 = 9 bytes)
|  |  2a 86 48 86       ; Hex encoding of 1.2.840.113549.1.1
|  |  f7 0d 01 01 01      
|  |  05 00             ; 05=NULL (0 bytes)
|  03 82 02 0f 00       ; 03=BIT STRING
|  |  30 82 02 0a       ; 30=SEQUENCE 
|  |  |  02 82 02 01    ; 02=INTEGER (0x82 = 130 bytes) the modulus
|  |  |  00             ; leading zero of INTEGER
|  |  |  d3 41 b2 9a 10 7d 28 62 2b c4 46 cc 62 45 b2 2a 15 c6 06 ce 09 3a c7 e3 44 49 63 36 64 72 e9 87 24 59 05 a9 a9 a4 19 10 54 75 1b 6e 0e 
|  |  |  b2 be 57 01 c9 38 91 f0 d7 58 5f 1d 53 a7 1a e8 23 6e d2 db 30 67 19 78 ce 19 20 21 81 29 ad 79 68 0b 9e 41 53 34 18 65 06 64 04 f4 81 
|  |  |  89 a1 bd d8 a4 00 bd ad c7 23 c0 a3 d6 00 15 33 f4 c2 74 88 4b 85 01 89 4d 4b 34 8c 49 8d 6a 3f 8a 44 f0 0d 05 70 d7 94 06 b1 39 55 96 
|  |  |  66 35 eb 50 7f 7f 36 11 aa d4 37 41 a2 53 6f 67 a1 a7 2b e7 18 e5 d5 c3 01 21 c7 45 75 18 19 be 11 00 89 8e 23 ce cb 53 78 13 f1 3a 42 
|  |  |  74 06 cf b0 0a 0b 6e d5 22 87 0f 76 40 a0 d8 3f bd e0 53 0b f2 9d 8c 23 f1 4a 2c 98 6b e3 7c 45 35 23 83 8f 56 e0 cd 6a 65 f9 b1 64 dc 
|  |  |  98 36 55 1c 38 94 2e 73 b1 97 16 3e 33 d9 33 f8 94 f4 b9 b4 bd 51 34 92 56 c1 5e b1 cf 8c f5 51 1b 1d e6 09 7a 0e 1c 3b f4 53 5e 40 f7 
|  |  |  17 f2 6c d1 4e df bf b0 fe d6 2a a4 dd 0c ea a1 05 82 3e 0b 50 a9 b9 4f 13 34 da 94 e3 02 c2 25 09 24 2d 6a 37 15 b7 2a 09 63 24 19 ca 
|  |  |  43 0c 79 56 fc 92 e8 c9 10 13 f0 1f 97 55 48 fa 1d 0f b6 b4 00 99 5c 21 c2 36 d4 0a c6 53 6c 3b 07 4f 0e d4 42 cf 14 43 de 68 b6 1f a5 
|  |  |  ae e0 c6 46 ce 3f 73 07 fa a0 a4 a3 e9 22 7e 9e ec ed 61 c7 2b 1b ca 5d bc 5c 90 16 4f a5 4a 7d 00 42 0f 75 ed ba c5 af 88 10 8b 6e 1f 
|  |  |  34 b8 21 9f 63 02 34 12 9b d4 45 de 5d 95 31 40 35 36 65 fc 37 72 56 2c a6 d1 c4 7e 13 41 1e ac c2 5c 7c 12 25 c8 36 3f 8e 38 b5 34 c3 
|  |  |  c5 93 dc b1 b8 22 b2 d9 c2 a9 8c 9e 39 cb 6d 19 a8 78 8f 6f 28 02 1a 1d 23 19 58 51 48 1c 53 04 9a fa a8 92 b5 2d 6b 09 cf fb 3a f9 e7 
|  |  |  d6 fa a6 e9 49 99 4e a7 b6 6a 28 44 de cf 92 33 0b 
|  |  02 03             ; 02=INTEGER (0x03 = 3 bytes) - the exponent
|  |  |  01 00 01       ; 0x010001 is hex for 65537
```

From this breakdown, components **n** (modulus) and **e** are found:
```
n = d3 41 b2 9a 10 7d ... 92 33 0b (a really large number)
e = 01 00 01 (65537 in decimal)
```

Do the same for the private key and refer to this [StackOverflow answer][11] for a similar breakdown. These results are from [phpseclib][8]. The variables in parenthesis were added for reference.

```
    0:d=0  hl=4 l=2344 cons: SEQUENCE
    4:d=1  hl=2 l=   1 prim:  INTEGER            :00
    7:d=1  hl=4 l= 513 prim:  INTEGER (n)        :00D341B29A107D28622BC446CC6245B22A15C606CE093AC7E3444963366472E987245905A9A9A4191054751B6E0EB2BE5701C93891F0D7585F1D53A71AE8236ED2DB30671978CE1920218129AD79680B9E4153341865066404F48189A1BDD8A400BDADC723C0A3D6001533F4C274884B8501894D4B348C498D6A3F8A44F00D0570D79406B13955966635EB507F7F3611AAD43741A2536F67A1A72BE718E5D5C30121C745751819BE1100898E23CECB537813F13A427406CFB00A0B6ED522870F7640A0D83FBDE0530BF29D8C23F14A2C986BE37C453523838F56E0CD6A65F9B164DC9836551C38942E73B197163E33D933F894F4B9B4BD51349256C15EB1CF8CF5511B1DE6097A0E1C3BF4535E40F717F26CD14EDFBFB0FED62AA4DD0CEAA105823E0B50A9B94F1334DA94E302C22509242D6A3715B72A09632419CA430C7956FC92E8C91013F01F975548FA1D0FB6B400995C21C236D40AC6536C3B074F0ED442CF1443DE68B61FA5AEE0C646CE3F7307FAA0A4A3E9227E9EECED61C72B1BCA5DBC5C90164FA54A7D00420F75EDBAC5AF88108B6E1F34B8219F630234129BD445DE5D953140353665FC3772562CA6D1C47E13411EACC25C7C1225C8363F8E38B534C3C593DCB1B822B2D9C2A98C9E39CB6D19A8788F6F28021A1D23195851481C53049AFAA892B52D6B09CFFB3AF9E7D6FAA6E949994EA7B66A2844DECF92330B
  524:d=1  hl=2 l=   3 prim:  INTEGER (e)        :011861
  529:d=1  hl=4 l= 512 prim:  INTEGER (d)        :0D02548182B18700FFA378977BCF60B3A340FBD25A2ECC073445AC8260A7F1BBCDDA1E83D9071011F7E5BE0F28A7A6F1720D5E4CC9BFD81E14DBD50C4BCC27B1BC8AF7D09ED938C87EE4EEEEAE5B8369E03C4368270FF6359541D2D73B71A316B0A2BD0099A8125406F0DEE416D38676CE182B60FED2F192A588E2EB44AB8727FAA4AEF62C70867A50CEEE1EBDDDA8BA9C1FE486F83EA0AE0F9F73BD6CE48EBEE3DA654BBE2CD91CA9C65A5982210759041B359BF45B23B81114FCBFD70E4FFB1CD98617A6040C677431433098D43716F155529ACB3576C6D1D66597E502A5942FCF2A8DAD87C5DF83F581FE7EBA775A716918AE9D6915D12F037DC57B8CFB7E761B0871D76D5262CEFE28FC939CCFC943F0A34C7AE5D53BEA92FAC4058244D840FFFF8369CBA5AD3853B055457E86E66C5726F5917660F07E7D2D8496B781BD87B3461B15E753BC83A0BD53AD440C7CE8B096107D67D66D135E6F35148A80FA27DECEDE2BA73106C5A398B01931BB87D054B8E1EA1263381E1C7DDDC0FFBFB669D4497663631382F3B3ADA3699A82AC874012B294EFDEACA056EB79CAC4F8D196BE860D839AF21431D313E1C2398D908FED5EAD79872F9B5C5BEF155A58EAA39EB30AD9A353ED8D1D19490C1399772A69FFDE9364DF76261C21C73DBE1FB9FDCD42068C757C8781AB2FC98B30D872B9F79D3EC5A52C719B4DBD498AA7F06641
 1045:d=1  hl=4 l= 257 prim:  INTEGER (p)        :00D81AAEEAA380503C60B59283E40AABDF60624704250B1FC82FD2110F6BE9788A7186648B91C9E7B95B2C317159724C9818742F74AB4A01BF7932E7931730C446A73A40D3885B8094259F26AAEF712133E251840AA79239A7EEE43D64B10EF61AFAFB04AA4EDF6812623D6756FAD768842A47E9DA8059A6AEB1A93CD014493099EB1E643D60464ECD99995DD8C862E6281066A7A15D10BBC754E25544189CD8B1CE0AF8BD69CD4F840673B8E6C529BA05CE61E023FCED37B8D4010F3D1967127AFFE9EB07CD5CDA83AD7E8CC14842FBAD922502A76E1107A9B3F809DC390C4916686332607A9E8DACFEBF6DDEE8253A8DE994A7AD014A91659FEE90EE14110CDD
 1306:d=1  hl=4 l= 257 prim:  INTEGER (q)        :00FA41E961682A3F21C6F30BCFDEECC9BC8B0C0F6A2D2F5A1CCA991CA58EAB6853F2039EFF14A61A9D4EE15CD41CD7500EC1E25BD28015525E147F240FDDC7728A10069757A36CC267D35C0ADBDF74CF303A8E7E814421ADEE2CB827AC418BB595BC308C6304E818206785D53CD7592898FE4C8C62AF1BEDA8CE76466DB3186A8D61ACCEDE94170E200AFB57FBC2A64486D01618F206704C09BD31113A2CA8C139765896741F9868DCDACA0DAE21AA5908856736E51A774C705E32D5E0B675345E06583FB8D32C2BBB9D95AE44C31FBB6BC15ABC41F202F7F33402A740ECC7939487FEEFC723F334685D92582BE4E311E5B82D6803996509855455347D49B82D07
 1567:d=1  hl=4 l= 256 prim:  (d mod (p-1))      :6EED07ABA35EF599E4B1DF32D53494EB15C6835A45C0B8A1DD63FAF4490722B223A8EF1B1E6DCA394317BB9B1458E92912F09D40232DF0EB38FF2C3FFA461FD935E9B6102B2CBB4F5F06CB150E575E7029A5093113EBD8C08D62F0C05919B8318CF8DD0445482D97573AE8050F95A7B194B685EDB1901C291252E8259261DD7CF45F480926153AFC31599287F9104B22000D25629B332CAC9C560BB22C91A9E730324AEF4FD0F9545C31091535E2A2242DA0C3C7EE3AE6012358839BA8800B5BC3BDA3CDC0D63B8A971C109A687D66E92351C7BE6CD29350779BD4418030255BD7D82EE3FEC8C43814E55C84DC4D301FCE59D8C238A22D002B7BF9948993F215
 1827:d=1  hl=4 l= 257 prim:  (d mod (q-1))      :0089803C7B0000A47622687A62FE4EFF7EF4387BDED43E7FEFED30EF0E24749C991B476F53827F908ED1AB1746D9DA015CBBA73BC355B13E9A90F3BFCF444890F23D2263F92A609C37E5B42CBE0C69F9FA5884B5FD7752BFFCAD08ACBC836D531D13ECFE47A1AE44D10B9F6AAAFB4A619D5B8A4F7ADC287A8ECAAAD3CA594488911C4CF9A6390E6B2895CF89314FB868F3F0FF954A53338653F3A7224F6C8C7BF47DB02960BF4F5C1D8355D8A6B98735EC153D16F6C58878132EB94A16D3AD512C4F5CA70BFFE22388CB6BDB086E55342E3BAC9BD7EFA5BBE535BFE1DE242C3AA7E19793E39924AA0AFBD1B5F40F08B506DD20CE1F66E9AB4378A0C2BBA7DE1BAF
 2088:d=1  hl=4 l= 256 prim:  ((inv of q) mod p) :2926C152D608B4E7B0EF12C08E941F1EB0EBBCF0B0E6D8E2D59253B81F22CC42608A8FD2A80E0A1E215EDAF31E0847A9305F96E9F089B4C2273351E2F1DBDF7AE870DB8F5FA58A1552800A4580DFBF84C5FB7DAD3526CB14BD46FC638712224CC8525F348DC300A0DFD7ABF93A09F18753064F7E9C429A48949DD85EA8A08AA7F9D3E454321D1D40AF76E1301FE6EB4C3004AF556BFF99F05D6D7CBDFA5DDAB81E272A46E2F9942520CAD515574E3911F04761E396D5DFF711EA3A03B05D2682390EDC4E6E497A4DF07BBDDE483F13626AD7D1FAF80F755639BF6297D1B41CDA2549EE07BBFCC6CA2064347DA65007E755CEE15538861BCFCCE501C8138A8585
```

This result provides the final pieces, **p** and **q**, to unlock the neighbor's message:
```
p = 00D81AAEEAA38 ...
q = 00FA41E961682 ...
```

Recall that the attacker's key was created with the same modulus as the neighbor's. Verify that the two are the same:
```
neighbor's public key modulus:   d341b29a107d28622bc446cc6245b22a15c606 ...
attacker's private key modulus:  D341B29A107D28622BC446CC6245B22A15C606 ...
```

In order to create RSA keys, the algorithm requires: **p**, **q**, and **e**. Since the two keys were created with the same modulus, the **p** and **q** variables can be used to recreate the neighbor's private key. The exponent **e** was pulled from the neighbor's public key earlier. Plug these variables into the python script:

```python
p = "00D81AAEEAA38 ..."
q = "00FA41E961682 ..."
e = 65537
_, d, _ = createKeys(int(p, 16), int(q, 16), e)
```

This will produce the neighbor's private key. Last step is to decrypt the neighbor's message:
```python
cipher = "8d66f329e9df55a5f0cf6007196f39dc87eea9c1bd ..."
decrypted = decrypt(int(cipher, 16), d, int(n1, 16))
print(f"\nDecrypted message: {decrypted}\n")
```

Grab the flag:
```
LHC{conspiracy_debunked}
```

## Resources

* [CrypTool: RSA Step-By-Step][1]
* [Wikipedia: RSA][2]
* [Wikipedia: Modular Multiplicative Inverse][3]
* [Wikipedia: Modular Exponentiation][4]
* [YouTube: Modular Exponentiation][5]
* [StackOverflow: Modular multiplicative inverse function in Python][6]
* [Wikipedia: ASN.1][7]
* [PHPSecLib: ASN.1 Parser][8]
* [LapoIt: ASN.1 JavaScript decoder][9]
* [StackExchange: How to find modulus from a RSA public key?][10]
* [StackExchange: What is the SSL private key file format?][11]

[1]:https://www.cryptool.org/en/cto-highlights/rsa-step-by-step
[2]:https://en.wikipedia.org/wiki/RSA_(cryptosystem)
[3]:https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
[4]:https://en.wikipedia.org/wiki/Modular_exponentiation
[5]:https://www.youtube.com/watch?v=EHUgNLN8F1Y
[6]:https://stackoverflow.com/questions/4798654/modular-multiplicative-inverse-function-in-python
[7]:https://en.wikipedia.org/wiki/ASN.1
[8]:http://phpseclib.sourceforge.net/x509/asn1parse.php
[9]:https://lapo.it/asn1js/
[10]:https://crypto.stackexchange.com/a/35105/55622
[11]:https://crypto.stackexchange.com/a/21104/55622