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

# To determine the value of φ(n), it is not enough to know n. Only with the 
# knowledge of p and q we can efficiently determine φ(n).
# The secret key also consists of n and a d with the property that e × d is a 
# multiple of φ(n) plus one.

# Expressed in formulas, the following must apply:
# e × d = 1 (mod φ(n))

# In this case, the mod expression means equality with regard to a residual class. 
# It is x = y (mod z) if and only if there is an integer a with x − y = z × a.

# This d can always be determined (if e was chosen with the restriction described 
# above)—for example with the extended Euclidean algorithm.

# https://stackoverflow.com/questions/4798654/modular-multiplicative-inverse-function-in-python
def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

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
    # https://stackoverflow.com/questions/16310871/how-to-find-d-given-p-q-and-e-in-rsa
    # e × d = 1 (mod φ(n))
    # d = e^-1 (mod φ(n))
    d = modinv(e, phi)    
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
    # Modular Exponentiation
    # pow(x, y[, z])
    # Return x to the power y; if z is present, return x to the power y, modulo z 
    return pow(message, e, n)

#***************************
# Decryption
#***************************
# Decrypting with the private key (n, d) is done analogously with
# m'' := m'^d (mod n).
#
# This is the same as: 
# m'' = m^(e × d) (mod n).
#
# RSA now exploits the property that:
# x^a = x^b (mod n)
# if
# a = b (mod φ(n))
# 
# As e and d were chosen appropriately, it is
# m'' = m.
# 
# The order does not matter. You could also first raise a message with the private key, 
# and then power up the result with the public key—this is what you use with RSA signatures.

def decrypt(cipher, d, n):
    # Modular Exponentiation
    # pow(x, y[, z])
    # Return x to the power y; if z is present, return x to the power y, modulo z 
    return pow(cipher, d, n)

if __name__ == "__main__":
    modulus = "d3 41 b2 9a 10 7d 28 62 2b c4 46 cc 62 45 b2 2a 15 c6 06 ce 09 3a c7 e3 44 49 63 36 64 72 e9 87 24 59 05 a9 a9 a4 19 10 54 75 1b 6e 0e b2 be 57 01 c9 38 91 f0 d7 58 5f 1d 53 a7 1a e8 23 6e d2 db 30 67 19 78 ce 19 20 21 81 29 ad 79 68 0b 9e 41 53 34 18 65 06 64 04 f4 81 89 a1 bd d8 a4 00 bd ad c7 23 c0 a3 d6 00 15 33 f4 c2 74 88 4b 85 01 89 4d 4b 34 8c 49 8d 6a 3f 8a 44 f0 0d 05 70 d7 94 06 b1 39 55 96 66 35 eb 50 7f 7f 36 11 aa d4 37 41 a2 53 6f 67 a1 a7 2b e7 18 e5 d5 c3 01 21 c7 45 75 18 19 be 11 00 89 8e 23 ce cb 53 78 13 f1 3a 42 74 06 cf b0 0a 0b 6e d5 22 87 0f 76 40 a0 d8 3f bd e0 53 0b f2 9d 8c 23 f1 4a 2c 98 6b e3 7c 45 35 23 83 8f 56 e0 cd 6a 65 f9 b1 64 dc 98 36 55 1c 38 94 2e 73 b1 97 16 3e 33 d9 33 f8 94 f4 b9 b4 bd 51 34 92 56 c1 5e b1 cf 8c f5 51 1b 1d e6 09 7a 0e 1c 3b f4 53 5e 40 f7 17 f2 6c d1 4e df bf b0 fe d6 2a a4 dd 0c ea a1 05 82 3e 0b 50 a9 b9 4f 13 34 da 94 e3 02 c2 25 09 24 2d 6a 37 15 b7 2a 09 63 24 19 ca 43 0c 79 56 fc 92 e8 c9 10 13 f0 1f 97 55 48 fa 1d 0f b6 b4 00 99 5c 21 c2 36 d4 0a c6 53 6c 3b 07 4f 0e d4 42 cf 14 43 de 68 b6 1f a5 ae e0 c6 46 ce 3f 73 07 fa a0 a4 a3 e9 22 7e 9e ec ed 61 c7 2b 1b ca 5d bc 5c 90 16 4f a5 4a 7d 00 42 0f 75 ed ba c5 af 88 10 8b 6e 1f 34 b8 21 9f 63 02 34 12 9b d4 45 de 5d 95 31 40 35 36 65 fc 37 72 56 2c a6 d1 c4 7e 13 41 1e ac c2 5c 7c 12 25 c8 36 3f 8e 38 b5 34 c3 c5 93 dc b1 b8 22 b2 d9 c2 a9 8c 9e 39 cb 6d 19 a8 78 8f 6f 28 02 1a 1d 23 19 58 51 48 1c 53 04 9a fa a8 92 b5 2d 6b 09 cf fb 3a f9 e7 d6 fa a6 e9 49 99 4e a7 b6 6a 28 44 de cf 92 33 0b"
    modulus = modulus.replace(" ", "")
    n = int(modulus, 16)
    e = 65537
    print(f"modulus1: {n}")
    n2 = "00D341B29A107D28622BC446CC6245B22A15C606CE093AC7E3444963366472E987245905A9A9A4191054751B6E0EB2BE5701C93891F0D7585F1D53A71AE8236ED2DB30671978CE1920218129AD79680B9E4153341865066404F48189A1BDD8A400BDADC723C0A3D6001533F4C274884B8501894D4B348C498D6A3F8A44F00D0570D79406B13955966635EB507F7F3611AAD43741A2536F67A1A72BE718E5D5C30121C745751819BE1100898E23CECB537813F13A427406CFB00A0B6ED522870F7640A0D83FBDE0530BF29D8C23F14A2C986BE37C453523838F56E0CD6A65F9B164DC9836551C38942E73B197163E33D933F894F4B9B4BD51349256C15EB1CF8CF5511B1DE6097A0E1C3BF4535E40F717F26CD14EDFBFB0FED62AA4DD0CEAA105823E0B50A9B94F1334DA94E302C22509242D6A3715B72A09632419CA430C7956FC92E8C91013F01F975548FA1D0FB6B400995C21C236D40AC6536C3B074F0ED442CF1443DE68B61FA5AEE0C646CE3F7307FAA0A4A3E9227E9EECED61C72B1BCA5DBC5C90164FA54A7D00420F75EDBAC5AF88108B6E1F34B8219F630234129BD445DE5D953140353665FC3772562CA6D1C47E13411EACC25C7C1225C8363F8E38B534C3C593DCB1B822B2D9C2A98C9E39CB6D19A8788F6F28021A1D23195851481C53049AFAA892B52D6B09CFFB3AF9E7D6FAA6E949994EA7B66A2844DECF92330B"
    n2 = int(n2, 16)
    print(f"modulus2: {n2}")
    e2 = int("011861", 16)
    print(f"e2: {e2}")

    d = "0D02548182B18700FFA378977BCF60B3A340FBD25A2ECC073445AC8260A7F1BBCDDA1E83D9071011F7E5BE0F28A7A6F1720D5E4CC9BFD81E14DBD50C4BCC27B1BC8AF7D09ED938C87EE4EEEEAE5B8369E03C4368270FF6359541D2D73B71A316B0A2BD0099A8125406F0DEE416D38676CE182B60FED2F192A588E2EB44AB8727FAA4AEF62C70867A50CEEE1EBDDDA8BA9C1FE486F83EA0AE0F9F73BD6CE48EBEE3DA654BBE2CD91CA9C65A5982210759041B359BF45B23B81114FCBFD70E4FFB1CD98617A6040C677431433098D43716F155529ACB3576C6D1D66597E502A5942FCF2A8DAD87C5DF83F581FE7EBA775A716918AE9D6915D12F037DC57B8CFB7E761B0871D76D5262CEFE28FC939CCFC943F0A34C7AE5D53BEA92FAC4058244D840FFFF8369CBA5AD3853B055457E86E66C5726F5917660F07E7D2D8496B781BD87B3461B15E753BC83A0BD53AD440C7CE8B096107D67D66D135E6F35148A80FA27DECEDE2BA73106C5A398B01931BB87D054B8E1EA1263381E1C7DDDC0FFBFB669D4497663631382F3B3ADA3699A82AC874012B294EFDEACA056EB79CAC4F8D196BE860D839AF21431D313E1C2398D908FED5EAD79872F9B5C5BEF155A58EAA39EB30AD9A353ED8D1D19490C1399772A69FFDE9364DF76261C21C73DBE1FB9FDCD42068C757C8781AB2FC98B30D872B9F79D3EC5A52C719B4DBD498AA7F06641"

    p = "00D81AAEEAA380503C60B59283E40AABDF60624704250B1FC82FD2110F6BE9788A7186648B91C9E7B95B2C317159724C9818742F74AB4A01BF7932E7931730C446A73A40D3885B8094259F26AAEF712133E251840AA79239A7EEE43D64B10EF61AFAFB04AA4EDF6812623D6756FAD768842A47E9DA8059A6AEB1A93CD014493099EB1E643D60464ECD99995DD8C862E6281066A7A15D10BBC754E25544189CD8B1CE0AF8BD69CD4F840673B8E6C529BA05CE61E023FCED37B8D4010F3D1967127AFFE9EB07CD5CDA83AD7E8CC14842FBAD922502A76E1107A9B3F809DC390C4916686332607A9E8DACFEBF6DDEE8253A8DE994A7AD014A91659FEE90EE14110CDD"
    q = "00FA41E961682A3F21C6F30BCFDEECC9BC8B0C0F6A2D2F5A1CCA991CA58EAB6853F2039EFF14A61A9D4EE15CD41CD7500EC1E25BD28015525E147F240FDDC7728A10069757A36CC267D35C0ADBDF74CF303A8E7E814421ADEE2CB827AC418BB595BC308C6304E818206785D53CD7592898FE4C8C62AF1BEDA8CE76466DB3186A8D61ACCEDE94170E200AFB57FBC2A64486D01618F206704C09BD31113A2CA8C139765896741F9868DCDACA0DAE21AA5908856736E51A774C705E32D5E0B675345E06583FB8D32C2BBB9D95AE44C31FBB6BC15ABC41F202F7F33402A740ECC7939487FEEFC723F334685D92582BE4E311E5B82D6803996509855455347D49B82D07"

    d = int(d, 16)
    p = int(p, 16)
    q = int(q, 16)

    _, d, _ = createKeys(p, q, e)
    print(f"d: {hex(d)}")

    if n == n2:
        print("MODULUS EQUALS!")
    if p * q == n:
        print("EQUALS!")
    else:
        print("NOT EQUAL")

    cipher = "8d66f329e9df55a5f0cf6007196f39dc87eea9c1bdaff77a779784903a90e3b42a2cce315179f550ad606deadeb392f93dbc45f01af1497f218b8dec3786680f88734425eb8050b52b8c8f02698b91dea0f3d25fbcda569acbf85bd05069dc9e3625c73c0d5dfad341e9dbee80c7fc52b77bc9de17c7431d1944690a928803ab49ada9428041fb51f8936673685e5fbe422cc541741b91d424702f490b394bed313b23486a1b5d102ca81ae537221ed2babca8818a1ee51170f500e22e04d1e3df1279536f33bbab2cfa1f2f3e36fd96818903394b077875208933fd303c8b094ea32bba9319815728eaaa89df969aa41b3ae1f18060c1e223d840adaf4845e7ce3cc685a8fc562c2b51a6e9b258d6e55d8f6980d6ad11aa813c66fff0e41ebb5bc17879603d9fed335972af7995485ddbd6a3b5dc6b6438c5d304b85cda031fc88bbee0a54f6fc2e5c4f66bcb8d3f6eacd34e885a56f88292d9a62846def34d2cfbc0c0fd5f7d695dec1979c104a6b65959be5d69d0adcceb086b3b3dd0ef7f3c8d60d325425ad7292d9ecafb04a172007d723d40e1e350b8346b675d337b851dd558ef8ca02e3c3fea71ad33dcd4c8b1d47da07e115b5f9cc9346ed6ccaecb81ff1a9a4ddaeeb1f173f6baff0837c133d95d1b96a5b80f52d115074bd2ecdd8f96a681cc4ad579d4d4bde48dfc30ca840ccbf66cc4df5066ce8a6f2dffb0ab"
    cipher = int(cipher, 16)
    decrypted = decrypt(cipher, d, n)
    print(f"Decrypted: {hex(decrypted)}")
    decoded = bytes.fromhex(hex(decrypted)[2:]).decode('utf-8')
    print(f"Decoded: {decoded}")

    n, d, e = createKeys(11, 13, 23)
    message = 100
    cipher = encrypt(message, e, n)
    print(f"cipher: {cipher}")
    decrypted = decrypt(cipher, e, n)
    if message == decrypted == 100 and cipher == 133:
        print("IT WORKED!")
    print(f"decrypted: {decrypted}")
    print