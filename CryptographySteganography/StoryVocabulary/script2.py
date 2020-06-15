#!/bin/python3

# Story Vocabulary

ciphertext = "1234156 756 81960 abc cde66"
plaintext = [" "]*len(ciphertext)

cipher = "0123456789abcde"
key    = "abcdefghijklmno"

# cipher = "1234567890abcde"
# key    = "t____r_soy_____"

for i in range(len(cipher)):
    for j in range(len(ciphertext)):
        if cipher[i] == ciphertext[j]:
            plaintext[j] = key[i]

print(f"ciphertext: {ciphertext}")
print(f"plaintext:  {''.join(plaintext)}")