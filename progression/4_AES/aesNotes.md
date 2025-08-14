# AES notes

##  Extension Fields

### Extension Field $\text{BF}(2^m)$ Arithmetic

a) Element Representation

The elements of $\text{BF}(2^m)$ are polynomials ( $a_{m-1}x^{m-1} + \dots + a_1 x + a_0 = A(x) \in \text{BF}(2^m)$ )
$$a_i \in \text{GF}(2) = \{0,1\}$$

Ex: $\text{GF}(2^3)$, any element must have the form $A(x) = a_2 x^2 + a_1 + a_0$.
Thus $\text{GF}(2^3) = \{0, 1, x, x+1, x^2, x^2+1, x^2+x, x^2 +x + 1\}$

How to compute with these elements??

b) Addition and Subtraction in $\text{GF}(2^m)$

---

**Definition** Extension field addition and subtraction
Let $A(x), B(x) \in \text{GF}(2^m)$ . *The sum of the two elements is then computed according to*
$$C(x) = A(x) + B(x) = \sum_{i=0}^{m-1} c_i x^i, \quad c_i \equiv a_i + b_i \mod 2$$
and their difference is computed according to:
$$C(x) = A(x) - B(x) = \sum_{i=0}^{m-1} c_i x^i, \quad c_i \equiv a_i - b_i \equiv a_i + b_i \mod 2$$

---
=> use regular polynomial addition or subtraction, *where the coefficients are computed in* $\text{GF}(2)$ 
Ex: $\text{GF}(2^3)$, $A(x) =x^2+x+1$, $B(x) = x^2 + 1$  
$A(x) + B(X) = (1+1) x^2 + x + (1+1)$ = $(0) x^2 + x + (0) = x$  
*Note, addition and subtraction in $\text{GF}(2^m)$ are the same operations.  
  
c) Multiplication in $\text{GF}(2^m)$  

---
**Definition** Extension field multiplication  
Let $A(x), B(x) \in \text{GF}(2^m)$ *and let*
$$P(x) = \sum_{i=0}^m p_ix^i, \quad p_i \in \text{GF} (2)$$  
*be an irreducible polynomial of degree* $m$ . *Multiplication of the two elements* $A(x), B(x)$ *is performed as*
$$C(x) \equiv A(x) \cdot B(x) \mod P(x)$$

---
Irreducible polynomial for $\text{GF}(2^3)$: $P(x) = x^3 +x + 1$.

For every field $\text{GF}(2^m)$ there exists several irreducible polynomials

d) Inversion in $\text{GF}(2^m)$  

---
**Definition** Extension field inversion  
The inverse $A^{-1}$ of a nonzero element $A \in \text{GF}(2^m)$ is defined by:
$$A^{-1}(x) \cdot A(x) \equiv 1 \mod P(x)$$

---

## Intro to ADS

**high level view of ADS**  

![alt text](/images/aesHighLevel.png)

number of rounds depend on the key length

| k   | # rounds |
| --- | -------- |
| 128 | 10       |
| 192 | 12       |
| 256 | 14       |

Remarks

- AES is the most important symmetric algorithm in the world
- NSA allows AES for classified data up to *top secret* with 192 or 256 bit key length.

## Structure of AES

- Unlike DES, AES is not a Fiestel cipher
- AES encrypts all 128 bits of the data path in one round  

**AES functions**  
![image](/images/aesBlock.png)  
each round consists of four layers

1) ByteSub: confusion
    - each element is nonlinearly trnsformed using lookup tables with special mathematical properies
2) ShiftRow: diffusion
    - premutes data
3) MixColumn: diffusion
    - matrix operation that combines blocks of four bytes
4) Key Addition
    - a 128 bit roundkey (subkey) derived from the main key is XORed to the state.

- last round does not have the MixCol layer  
- at the beginning of AES and at the very end, a subkey is added "key whitening"

**AES round function**  
![alt text](/images/image.png)  

- the 128 bit data path is split into 16 bytes

### Byte Substitution Layer

Each byte $A_i$ is replaced by another byte $B_i$:  
$$S(A_i) = B_i$$  
The S-box is the only non linear function of AES:
$$\text{ByteSub}(A)+\text{ByteSub}(b) \neq \text{ByteSub}(A+B)$$  
Each $S$ box is identical to each other.  
Example: $A_i = C2 = 1100 0010 \rightarrow S(C2) = 25 = 0010 0101$  
AES S-box table construction  
![alt text](/images/image-3.png)  

- consider $A_i \in \text{GF}(2^8)$ and compute its inverse
ex: $A_i = 1100 0010 \rightarrow A_i(x) = x^7 +x^6+x$, now computing the inverse, $B_i '(x) = x^5 + x^3 +x^2 + x + 1 \rightarrow B_i' = 0010 1111$. This can be verified by the fact that $A_i(x) \cdot B_i'(x) = (x^7 +x^6 + x) \cdot (x^5 + x^3 +x^2 + x + 1) \equiv 1 \mod x^8 + x^4 + x^3 + x + 1$  
- Next each byte $B_i'$ is multiplied by a consant bit matrix followed by the additoin of a consant 8-bit vector, resuliting in the final mapping from $A_i \rightarrow B_i$

### ShiftRows Sublayer

Cyclically shifts the second row of the state martix by three bytes to the right, third row two bytes to the right and fourth by one byte.

![alt text](/images/image-1.png)

![alt text](/images/image-2.png)

### MixColumn Sublayer

Linear transformation that mixes each column of the state matrix. Every input byte influences four output bytes, providing massive diffusion.
$$\text{MixColumn(B) = C}$$  
where $B$ is the state after the ShiftRows sublayer.  
![alt text](/images/image-4.png)  
The resulting $C$ vectors will be calculated using Galois field multiplication and addition (modulo reduction).  

## Decryption  

All layers must be inverted for decryption

- Byte Substitution -> Inv Byte  Substitution
- Shift Rows -> Inv Shift Rows 
- Mix Column -> Inv Mix Column
- Key schedule -> reversed key schedule

(insert decryption block here)

