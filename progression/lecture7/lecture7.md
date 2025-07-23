# Introduction to Galois Fields for the AES

**Topics Covered (Chapter 4)**  

1. Motivation
2. Intro to Finite Fields (Galois Fields)
3. Prime Fields
4. Extension Fields

## 4) Extension Fields

### Extension Field $\text{BF}(2^m)$ Arithmetic

a) Element Representation

The elements of $\text{BF}(2^m)$ are polynomials ( $a_{m-1}x^{m-1} + \dots + a_1 x + a_0 = A(x) \in \text{BF}(2^m)$ )
$$a_i \in \text{GF}(2) = \{0,1\}$$

Ex: $\text{GF}(2^3)$, any element must have the form $A(x) = a_2 x^2 + a_1 + a_0 $.
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
