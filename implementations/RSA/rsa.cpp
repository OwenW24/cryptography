#include "rsa.hpp"

void RSA::key_gen()
{
    k.p = 3;
    k.q = 11;
    k.pub = {k.p * k.q, 3};

    k.phi = (k.p-1) * (k.q-1);
    k.prv = extended_euclid(k.phi, k.pub.second).second.second;
}

char RSA::enc_char(int x)
{
    int n = k.pub.first;
    int e = k.pub.second;
    int y = exp(x, e, n);
    return char(y);
}

char RSA::dec_char(int y)
{
    int n = k.pub.first;
    int d = k.prv; 
    int x = exp(y, d, n);
    return char(x);
}



pair<int,pair<int,int>> RSA::extended_euclid(int r0, int r1)
{
    vector<int> s = {1,0};
    vector<int> t = {0,1};
    vector<int> r = {r0, r1};
    vector<int> q = {r0/r1};
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


int RSA::exp(int x, int H, int n)
{
    bitset<16> h(H);
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

//prime testing
int RSA::fermat(int p)
{
    if (p == 1) return 0;
    if (p < 4) return 1;
    srand(time(0));
    int s = 20; // security parameter
    int a = 0;
    for (int i = 1; i <= s; i++)
    {
        a = (rand() % (p-3)) + 2; // random number generator
        if (exp(a, p-1, p) != 1) return 0;
    }
    return 1;
}


void RSA::enc()
{
    if (plaintext.empty()) return;  // should throw error here
    for (char x: plaintext) ciphertext += enc_char(int(x));
}

void RSA::dec()
{
    if (ciphertext.empty()) return;  // should throw error here
    for (char y: ciphertext) plaintext += dec_char(int(y));
}

void RSA::set_plaintext(string xs)
{
    plaintext = xs;
}

void RSA::set_ciphertext(string ys)
{
    ciphertext = ys;
}

string RSA::get_plaintext()
{
    return plaintext;
}

string RSA::get_ciphertext()
{
    return plaintext;
}

pair<int, int> RSA::get_public_key()
{
    return k.pub;
}

RSA::RSA()
{
    key_gen();
}

