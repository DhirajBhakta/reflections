Every person has 2 large prime numbers M and N. these are kept secret.
They multiply this = MN  and the output MN  is made public.

Any outsider can garble(encrypt) his message using the publicly made available MN.. and noone(not even himself) can decrypt this without knowing what the prime factors of MN are (M and N are confidential)


## How to create a key pair?
https://www.onebigfluke.com/2013/11/public-key-crypto-math-explained.html
https://santandergto.com/en/math-details-of-public-key-cryptography/
- select two large prime numbers : `p` and `q` 
- `n = p * q`
- select a number  `e`  such `e` is co-prime with the totient of `n`   and `e < n` 
	- `totient(n) = (p-1) * (q-1)`
- **public key = `(n,e)`**
- Find a number `d` such that `ed` is coprime with `totient(n)` 
- **private key = (n, d, p , q)** 

Note: if you have the private key (n,e, p, q), you can derive the public key