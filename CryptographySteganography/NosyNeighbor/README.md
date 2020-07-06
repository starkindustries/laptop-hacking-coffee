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

https://lapo.it/asn1js/
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

Convert public key to hex with cyber chef. Then setup the bytes in the same fashion as the stack exchange answer

https://crypto.stackexchange.com/a/35105/55622
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
|  |  |  01 00 01       ; 0x01001 is hex for 65537
```

```
$ openssl rsa -pubin -in public.key -text -noout
```

* https://www.cryptool.org/en/cto-highlights/rsa-step-by-step
* https://www.geeksforgeeks.org/how-to-solve-rsa-algorithm-problems/
* https://crypto.stackexchange.com/questions/18031/how-to-find-modulus-from-a-rsa-public-key
* https://lapo.it/asn1js/
