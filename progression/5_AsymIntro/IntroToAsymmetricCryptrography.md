## Basics

**Definition** One-way function
A function $f$ is a one-way function if  

1. $y=f(x)$ is computationally easy, and
2. $x=f^{-1}(y)$ is computationally infeasible

## Number Theory

### Euclidean Algorithm

Euclid's algorithm for finding the greatest common divisor between two positive integers $a, b$  

```cpp
// recursive implementation
int euclid(int a, int b){
	if (b == 0) return a;
	return euclid(b, a % b);
}
```

### Extended Euclidean Algorithm
Goal: $\gcd(r_0, r_1) = s r_0 + t r_1$, compute $s, t$ 
Idea: Compute regular Euclidean Algorithm $\gcd(r_0,r_1)$ whilst computing $s_i, t_i$ to eventually find $s_l, t_l = s, t$ 

| $i$      | $r_{i-2} = q_{i-1}r_{i-1}+r_i$ | $r_i = s_i r_0 + t_i r_1$                  |
| -------- | ------------------------------ | ------------------------------------------ |
| 2        | $r_0 = q_1r_1 + r_2$           | $r_2 = s_2 r_0 + t_2 r_1$                  |
| $\vdots$ | $\vdots$                       | $\vdots$                                   |
| $l$      | $r_{l-2} = q_{l-1}r_{l-1}+r_l$ | $r_l = s_l r_0 + t_l r_1 = \gcd(r_0, r_1)$ |

in general $r_{i-2} = s_{i-2} r_0 t_{i-2} r_1$, $r_{i-1} = s_{i-1} r_0 + t_{i-1} r_1$ 
and $r_i$ can be rewritten as $r_i = r_{i-2} - q_{i-1} r_{i-1}$ 
thus
$r_i = [s_{i-2} - q_{i-1} s_{i-1}]r_0 + [t_{i-2} - q_{i-1} t_{i-1}]r_1 = s_i r_0 + t_i r_1$
or 
$$s_i = s_{i-2} - q_{i-1} s_{i-1}$$
$$ t_i = t_{i-2} - q_{i-1} t_{i-1}$$
for $i \geq 2$, where $s_0 = 1, s_1 = 0, t_0 = 0, t_1 = 1$ 

```cpp
//iterative implementation
pair<int, pair<int, int>> extended_euclid(int r0, int r1)
{
	vector<int> s = {1, 0};
	vector<int> t = {0, 1};
	vector<int> r = {r0, r1};
	vector<int> q = {r0 / r1};
	int i = 1;
	while(r[i] != 0)
	{
		i += 1;
		r.push_back(r[i-2] % r[i-1]);
		q.push_back((r[i-2] - r[i]) / r[i-1]);
		s.push_back(s[i-2] - (q[i-1] * s[i-1]));
		t.push_back(t[i-2] - (q[i-1] * t[i-1]));
	}
	// return {gcd, {s, t}}
	return {r[i-1], {s[i-1], t[i-1]}};
}
```


Main application of the extended Euclidean algorithm is to computer the modular inverse of an integer e.g. $a^{-1} \equiv ? \mod n$. Note that $a\cdot a^{-1} \equiv 1 \mod n$. Thus we compute $\gcd(r_0,r_1) = 1 = sr_0 + tr_1$    
$$s r_0+ t r_1 \equiv 1\mod r_0$$
$$r_1 \cdot t \equiv 1 \mod r_0$$
$$t \equiv r_1 ^{-1} \mod r_0$$

### Euler's Phi Function

**Definition** Euler's Phi Function
The number of integers in $\mathbb{Z}_m$ relatively prime to $m$ is denoted by $\Phi (m)$.
For example, let $m = 6, \mathbb{Z}_6 = \{0,1,2,3,4,5\}$

- there are two numbers in the set that are relatively prime to $6$, namely $1$ and $5$: $\gcd(1,6) = \gcd(5,6) = 1$. Thus $\Phi(6) = 2$.
**Theorem** Let $m$ have the following canonical factorization
$$m = p_1^{e_1}\cdot p_2^{e_2}\cdot \dots \cdot p_n^{e_n}$$
where $p_i$ are distinct prime numbers and $e_i$ are positive integers, then
$$\Phi(m) = \prod_{i=1}^n p_i^{e_i}-p_i^{e_{i-1}}$$

**Theorem** Fermat's Little Theorem
Let $a$ be an integer and $p$ be prime then:
$$a^p \equiv a \mod p$$
**Theorem** Euler's Theorem
Let $a$ and $m$ be integers with $\gcd(a,m) = 1$, then:
$$a^{ \Phi (m) } \equiv 1 \mod m$$

