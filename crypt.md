

# Ciphers
Ciphers are **algorithms** to perform encryption, decryption, digital signatures or hashing.
## Symmetric
_faster & older_

Blowfish, AES, DES, RC4, RC5 and RC6.

##### Most widely used
AES-128, AES-192, and AES-256.


## Asymmetric
_slower and newer_

RSA, DSA



# AES &mdash; Advanced Encryption Standard

- 128 bit block cipher = 16 bytes
    - which means it takes 128 bit long block of plaintext and converts it into 128 bit long ciphertext

- keys can be 
    - 128 bit = 16 bytes
    - 192 bit
    - 256 bit
    
    The Key size determines the number of rounds

- So AES128, AES192, AES256 describe the key size... the block size is ALWAYS 128 bits

- AES is based on a design principle known as a substitution-permutation network (SP-network)


AES operates on a 4x4 column major matrix called "state matrix"

matrix = 128 bit block of plaintext

one cell = 8 bits =  1 byte

```
b0 b4 b8  b12
b1 b5 b9  b13
b2 b6 b10 b14
b3 b7 b11 b15
```
`**Important note** : the plaintext should be a multiple of blocksize(128 bits, i.e 16 bytes) `
### Steps

1. Key expansion

2. First Round
    - Add Round Key
3. Subsequent Rounds
    - Byte substitution
    - Mix Rows 
    - Mix Columns
    - Add Round Key
4. Final Round
    - Byte substitution
    - Mix Rows
    - Add Round Key

In Kee Expansion, round keys are derived from the cipher key


![](https://qph.fs.quoracdn.net/main-qimg-9e836067540194ab84a87dfe63483b09.webp)


## Mode of operation

 In order to cope with data of arbitrary length, the cipher(AES) must be combined with a mode of operation.

 `

 #### ECB Mode
 - Weakest
 - Each 128bit block is encrypted independently of other blocks

#### CBC Mode
- Each 128bit plaintext block(prior to encryption) gets XORed with previous 128 bit ciphertext block
- Needs an IV (Initialization Vector)













