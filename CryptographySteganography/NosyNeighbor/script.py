#!/usr/bin/python3
import math

# https://www.geeksforgeeks.org/how-to-solve-rsa-algorithm-problems/
# https://www.cryptool.org/en/cto-highlights/rsa-step-by-step

#***************************
# Prime factors
#***************************
# As a starting point for RSA choose two primes p and q.
# 1st prime
# p = 11 
# 2nd prime
# q = 13

# For the algorithm to work, the two primes must be different.
# Calculate n
# n = p * q

#***************************
# Public key
#***************************
# The product 'n' is also called module in the RSA method. 
# The public key consists of the module 'n' and an exponent 'e'.
# e = 23

#***************************
# Secret key
#***************************
# RSA uses the Euler φ function of n to calculate the secret key. 
# This is defined as: φ(n) = (p − 1) × (q − 1)
# phi = (p - 1) * (q - 1)

# It is important for RSA that the value of the φ function is coprime to e 
# (the largest common divisor must be 1).
# https://www.geeksforgeeks.org/gcd-in-python/
# if math.gcd(e, phi) == 1:
#     # this is good
#     print(f"Success: math.gcd(e, phi) == 1")
# else:
#     # this is bad
#     print(f"Error: math.gcd(e, phi) != 1. Exiting..")
#     exit()

# To determine the value of φ(n), it is not enough to know n. Only with the 
# knowledge of p and q we can efficiently determine φ(n).
# The secret key also consists of n and a d with the property that e × d is a 
# multiple of φ(n) plus one.

# Expressed in formulas, the following must apply:
# (e × d) mod φ(n) = 1

# In this case, the mod expression means equality with regard to a residual class. 
# It is x = y (mod z) if and only if there is an integer a with x − y = z × a.

# This d can always be determined (if e was chosen with the restriction described 
# above)—for example with the extended Euclidean algorithm.

def createKeys(p, q, e):
    n = p * q
    phi = (p - 1) * (q - 1)
    if math.gcd(e, phi) == 1:
        # this is good
        print(f"Success: math.gcd(e, phi) == 1")
    else:
        # this is bad
        print(f"Error: math.gcd(e, phi) != 1. Exiting..")
        exit()
    d = 2
    while (e * d) % phi != 1:
        d += 1
    return n, d, e

#***************************
# Encryption 
#***************************
# Internally, this method works only with numbers, which are between 0 and n.
# Encrypting a message m (number) with the public key (n, e) is calculated:
# m' := m^e (mod n)

def encrypt(message, e, n):
    if message > n:
        print(f"Error: message{{{message}}} > n{{{n}}}. Exiting..")
    return (message**e) % n 

#***************************
# Decryption
#***************************
# Decrypting with the private key (n, d) is done analogously with
# m'' := m'^d (mod n).
#
# This is: 
# m'' = m^(e × d) (mod n).
#
# RSA now exploits the property that:
# xa = xb (mod n)
# if
# a = b (mod φ(n))
# 
# As e and d were chosen appropriately, it is
# m'' = m.
# 
# The order does not matter. You could also first raise a message with the private key, 
# and then power up the result with the public key—this is what you use with RSA signatures.

def decrypt(cipher, d, n):
    return (cipher**d) % n

if __name__ == "__main__":
    modulus = "d3 41 b2 9a 10 7d 28 62 2b c4 46 cc 62 45 b2 2a 15 c6 06 ce 09 3a c7 e3 44 49 63 36 64 72 e9 87 24 59 05 a9 a9 a4 19 10 54 75 1b 6e 0e b2 be 57 01 c9 38 91 f0 d7 58 5f 1d 53 a7 1a e8 23 6e d2 db 30 67 19 78 ce 19 20 21 81 29 ad 79 68 0b 9e 41 53 34 18 65 06 64 04 f4 81 89 a1 bd d8 a4 00 bd ad c7 23 c0 a3 d6 00 15 33 f4 c2 74 88 4b 85 01 89 4d 4b 34 8c 49 8d 6a 3f 8a 44 f0 0d 05 70 d7 94 06 b1 39 55 96 66 35 eb 50 7f 7f 36 11 aa d4 37 41 a2 53 6f 67 a1 a7 2b e7 18 e5 d5 c3 01 21 c7 45 75 18 19 be 11 00 89 8e 23 ce cb 53 78 13 f1 3a 42 74 06 cf b0 0a 0b 6e d5 22 87 0f 76 40 a0 d8 3f bd e0 53 0b f2 9d 8c 23 f1 4a 2c 98 6b e3 7c 45 35 23 83 8f 56 e0 cd 6a 65 f9 b1 64 dc 98 36 55 1c 38 94 2e 73 b1 97 16 3e 33 d9 33 f8 94 f4 b9 b4 bd 51 34 92 56 c1 5e b1 cf 8c f5 51 1b 1d e6 09 7a 0e 1c 3b f4 53 5e 40 f7 17 f2 6c d1 4e df bf b0 fe d6 2a a4 dd 0c ea a1 05 82 3e 0b 50 a9 b9 4f 13 34 da 94 e3 02 c2 25 09 24 2d 6a 37 15 b7 2a 09 63 24 19 ca 43 0c 79 56 fc 92 e8 c9 10 13 f0 1f 97 55 48 fa 1d 0f b6 b4 00 99 5c 21 c2 36 d4 0a c6 53 6c 3b 07 4f 0e d4 42 cf 14 43 de 68 b6 1f a5 ae e0 c6 46 ce 3f 73 07 fa a0 a4 a3 e9 22 7e 9e ec ed 61 c7 2b 1b ca 5d bc 5c 90 16 4f a5 4a 7d 00 42 0f 75 ed ba c5 af 88 10 8b 6e 1f 34 b8 21 9f 63 02 34 12 9b d4 45 de 5d 95 31 40 35 36 65 fc 37 72 56 2c a6 d1 c4 7e 13 41 1e ac c2 5c 7c 12 25 c8 36 3f 8e 38 b5 34 c3 c5 93 dc b1 b8 22 b2 d9 c2 a9 8c 9e 39 cb 6d 19 a8 78 8f 6f 28 02 1a 1d 23 19 58 51 48 1c 53 04 9a fa a8 92 b5 2d 6b 09 cf fb 3a f9 e7 d6 fa a6 e9 49 99 4e a7 b6 6a 28 44 de cf 92 33 0b"
    modulus = modulus.replace(" ", "")
    n = int(modulus, 16)
    e = 65537

    n, d, e = createKeys(11, 13, 23)
    message = 100
    cipher = encrypt(message, e, n)
    print(f"cipher: {cipher}")
    decrypted = decrypt(cipher, d, n)
    print