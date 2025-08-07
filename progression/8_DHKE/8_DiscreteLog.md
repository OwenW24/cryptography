# DHKE

### DHKE prerequisites

#### Groups
![Image](/images/group.png)  
The set $\mathbb{Z}_p^*$ consists of all integers $i =1, \dots, n-1$ for which $\gcd(i,n) = 1$, forms a abelian/commutative group under multiplication modulo $n$. The identity element is $e=1$.

- For this group, closure, associativity, identity, inverse, and commutativity hold. 
- This group is a abelian/commutative group.
- The inverse of each element can be computed with the extended Euclidean algorithm.

#### Diffie-Hellman Key exchange

DHKE is based on the fact that for a prime $p$ the exponentiation in $\mathbb{Z}_p^*$ is a one-way function and exponentiation is communicative  
$$k \equiv (\alpha ^x) ^y \equiv (\alpha ^y) ^x \mod p$$

1) Choose a large prime $p$
2) Choose an integer $\alpha \in \{2,3,\dots, p-2 \}$
3) Publish domain parameters $p$ and $\alpha$  

Source (Alice):

1) Choose $a = k_{pr,A} \in \{2,3,\dots, p-2\}$
2) Compute $A= k_{pub,A} \equiv \alpha^a \mod p$

Source (Alice) sends $K_{pub, A} = A$ to Destination (Bob)

Destination (Bob):

1) Choose $b = k_{pr,B} \in \{2,3,\dots, p-2\}$
2) Compute $B = k_{pub,B} \equiv \alpha^b \mod p$
3) Compute $k_{AB} = k^{k_{pr,B}}_{k_{pub,A}} = A^b \mod p$

Destination (Bob) sends $K_{pub, B} = B$ to Source (Alice)

Source (Alice):

1) Compute $k_{AB} = k^{k_{pr,A}}_{k_{pub,B}} = B^a \mod p$

**Proof of correctness**  
Source (Alice) computes
$$B^a = (\alpha^b)^a \mod p$$
Destination (Bob) computes
$$A^a = (\alpha^a)^b \mod p$$
![Image](/images/dhke.png)

````cpp
struct DHKE
{
    int p;
    int alpha;
    int k_priv;
    int k_pub;
    int k_shared;
    void public_key_gen(){ k_pub = (crypt::exp(alpha, k_priv, p)); }
    void shared_key_gen(int other_k_pub){ k_shared = crypt::exp(other_k_pub, k_priv, p);};
    DHKE(int p, int alpha):p(p), alpha(alpha){}
};
int main()
{
    DHKE Alice(29,2);
    DHKE Bob(29,2);
    Alice.k_priv = 5;
    Alice.public_key_gen();
    Bob.k_priv = 12;
    Bob.public_key_gen();
    Bob.shared_key_gen(Alice.k_pub);
    Alice.shared_key_gen(Bob.k_pub);
    cout << Alice.k_shared << " " << Bob.k_shared << endl;
    return 0;
}
````