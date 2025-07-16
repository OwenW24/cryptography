# Modular Arithmetic and Historical Ciphers

**Topics Covered (Chapter 1.4)**  

- 1.4.1 Modular Arithmetic
- 1.4.2 rings
- 1.4.3 Shift cipher
- 1.4.4 Affine cipher

## Modular Arithmetic

**Definition** Congruence Modulo Operation  
Let $a, r, m \in \mathbb{Z}$ and $m > 0$.
$$
a \equiv r \mod m
$$
if $m | (a-r)$  
$m$ is called the modulus and $r$ is the remainder.  
Note: $r \equiv b \mod m$ if and only if $a \mod m = r \mod m$  

**Definition** Equivalence Classes $\mod m$  
If $a, m \in \mathbb{Z}$ then $[a]_m$ is the set of all integers that are congruent to $a, \mod m$. This set is referred to as the equivalence class of $a \mod m$.

## Rings

**Definition** Ring  
The integer ring $\mathbb Z _m$ consists of:  

1. The set $\mathbb Z_m = \{0,1,2,\dots, m-1\}$
2. Two operations "$+$" and "$\cdot$"for all $a, b \in \mathbb Z_m$ such that:  
    1. $a+b \equiv c \mod m \quad (c \in \mathbb Z_m)$
    2. $a\cdot b \equiv d \mod m \quad (d \in \mathbb Z_m)$  

Rings hold the following properties: closed, associative, distributive, communicative, there is a nuetral element with respect to addition (0),
the additive inverse always exists, there is a nuetral element with respect to multiplication (1), the
multiplicative inverse exists for some elements.  
Note: an element $a \in \mathbb Z$ has a multiplicative inverse
$a^{-1}$ if and only if $\text{gcd}(a,m) = 1$.  

## Shift/Caesar Cipher

**Definition** Shift Cipher  
Let $x,y,k \in \mathbb Z _{26}$.  
$e_k(x) \equiv x + k \mod 26$  
$d_k(y) \equiv y- k \mod 26$

## Affine Cipher

**Definition** Affine Cipher  
Let $x,y,a,b \in \mathbb Z_{26}$. Where key $k=(a,b)$ and $\gcd(a,26) = 1$  
$e_k(x) \equiv a \cdot x + b \mod 26$  
$d_k(y) \equiv a^{-1} \cdot (y - k) \mod 26$
