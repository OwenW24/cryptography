# RSA notes

### RSA encryption and decryption
**Definition** RSA Encryption: Given the public key $(n,e) = k_{pub}$ and the plaintext $x$, the encryption function is  
$$y = e_{k_{pub}}(x) \equiv x^e \mod n$$
**Definition** RSA Decryption: Given the private key $(d) = k_{pr}$ and the ciphertext $y$, the decryption function is  
$$x = d_{k_{pr}}(y) \equiv y^d \mod n$$
where $x,y \in \mathbb{Z}_n$  
Requirements for the RSA cryptosystem:
1) it must be computationally infeasible to determine the private key $d$ given the public key values $e$ and $n$.
2) we cannot encrypt more than $l$ bits ($l$ = bit length of $n$) with one RSA encryption
3) It should be relatively easy to calculate $x^e \mod n$ to encrypt and $y^d \mod n$ to decrypt.
4) For a given $n$ there should be many private/public key pairs

### Key generation
**Definition** RSA Key Generation:
Output: public key:$k_{pub} = (n,e)$ and private key: $k_{pr} = d$

1. Compute two large primes $p$ and $q$
2. Compute $n = p\cdot q$
3. Compute $\Phi(n) = (p-1)(q-1)$
4. Select the public exponent $e \in \{1,2,\dots,\Phi(n)-1 \}$ such that $\gcd(e, \Phi(n)) = 1$
5. Compute the private key $d$ such that $d \cdot e \equiv 1 \mod \Phi (n)$ 
Applying extended euclidean algorithm with input parameters $n$ and $e$ we obtain the relationship
$\gcd (\Phi(n), e) = s\cdot \Phi (n) + t \cdot n$ thus $d \equiv t \mod \phi(n)$  
In  psuedocode, a better way to understand the encryption and decryption functions are as follows
- `enc(x, (n,e)) = (x^e) % n`
- `dec(y, (n,e), d) = (y^d) % n`

C++ enc and dec (without fast exponentiation) 
```cpp
int enc(int x, pair<int, int> k_pub)
{
	int n = k_pub.first;
	int e = k_pub.second;
	int y = 1;
	for (int i = 0; i < e; i++) y = (y * x) % n;
	return y;
}
```

```cpp
int dec(int y, pair<int, int> k_pub, int k_priv)
{
	int n = k_pub.first;
	int e = k_pub.second;
	int x = 1;
	for (int i = 0; i < k_priv; i++) x = (x * y) % n;
	return (x);
}
```
### Fast Exponentiation

**Square and Multiply Algorithm**
We can achieve the desired result by performing two basic operations
1) squaring the current result
2) multiplying the current result by the base element $x$
Algorithm in words:
Scan the exponent bits left to right 
- in every iteration we square
- if current bit is equal to one: multiply by $x$

```cpp
int exp(int x, int H, int n)
{
	bitset<32> h(H);
	int t = h.size() - 1;
	while (h[t] != 1) {t--;}
	int r = x;
	for (int i = t - 1; i >= 0; i--)
	{
	r = (r*r) % n;
	if (h[i] == 1) r = (r * x) % n;
	}
	return r;
}
```


### Finding Large Primes
The probability for a random odd number $p$ to be prime is: 
$$P(p\text{ is prime}) \approx \frac 2 {\ln(p)}$$
Thus, for an RSA with a 2048 bit modulus $n$ 
$$P(p\text{ is prime}) \approx \frac 2 {\ln(2^{1024})} \approx \frac 1 {354}$$
Thus it is more than computationally feasible to pick large numbers at random until you find a prime number.
### Primality Tests
Based on Fermat's Little Theorem:
**Fermat Primality Test**

```

```
