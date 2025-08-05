#include "rsa.hpp"

// key generation
void RSA::key_gen()
{
    k.phi = (k.p-1) * (k.q-1); 
    
    // determine e in {1,2,phi-1} st gcd(e, phi) = 1

    // make a more efficient way to find e and d min
    // not totally necessary to find min here actually
    // should maybe figure out a way to exclude numbers that exceed a certain power

    // d & e efficient method -----------------
    int min = __INT_MAX__;
    int min_idx = 0;
    vector<pair<long, long>> e_and_d;
    for (long e = 2; e < k.phi; e++)
    {
        if (extended_euclid(e, k.phi).first == 1) 
            e_and_d.push_back({e, extended_euclid(k.phi, e).second.second});
    }
    for (long i = 0; i < e_and_d.size(); i++)
    {
        long e = e_and_d[i].first;
        long d = e_and_d[i].second;
        if (d < 0) d*=-1;
        if ((e + d) / 2 < min)
        {
            min = (e + d) / 2;
            min_idx = i;
        }
    }
    long e = e_and_d[min_idx].first;
    k.prv = e_and_d[min_idx].second;
    // d & e efficient method -----------------


    // // d & e random method  -----------------
    // long e = 1;
    // srand(time(0));
    // do
    // {
    //     e = (rand() % (k.phi-2)) + 2;
    // } while (extended_euclid(e, k.phi).first != 1);
    // // d & e random method  -----------------

    k.pub = {k.p * k.q, e};

    cout << e << "<-e" << endl;
    cout << k.prv << "<-d" << endl;
    cout << k.phi << "<-phi" << endl;
}


pair<long,pair<long,long>> RSA::extended_euclid(long r0, long r1)
{
    vector<long> s = {1,0};
    vector<long> t = {0,1};
    vector<long> r = {r0, r1};
    vector<long> q = {r0/r1};
    long i = 1;
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

long RSA::exp(long x, long H, long n)
{
    bool flip = false;
    if (H < 0 && H % 2 == 1)
    {
        flip = true;
        H *= -1;
    }
    else if (H < 0) H*=-1;
    bitset<32> h(H);
    long t = h.size() - 1;
    while (h[t] != 1) {t--;}
    long r = x;
    for (long i = t - 1; i >= 0; i--)
    {
        r = (r*r) % n;
        if (h[i] == 1) r = (r * x) % n;
    }

    if (flip) r*=-1;
    return r;
}

//prime testing
long RSA::fermat(long p)
{
    if (p == 1) return 0;
    if (p < 4) return 1;
    srand(time(0));
    long s = 20; // security parameter
    long a = 0;
    for (long i = 1; i <= s; i++)
    {
        a = (rand() % (p-3)) + 2; // random number generator {}
        if (exp(a, p-1, p) != 1) return 0;
    }
    return 1;
}


char RSA::enc_char(long x, pair<long, long> pub)
{
    long n = pub.first;
    long e = pub.second;
    long y = exp(x, e, n);
    return y;
}

char RSA::dec_char(long y)
{
    long n = k.pub.first;
    long d = k.prv; 
    long x = exp(y, d, n);
    return x;
}

void RSA::enc(pair<long, long> pub)
{
    if (plaintext.empty()) return;  // should throw error here
    ciphertext = "";
    for (char x: plaintext) ciphertext += enc_char(long(x), pub);
    // ciphertext = enc_char(plaintext, pub);

}

void RSA::dec()
{
    if (ciphertext.empty()) return;  // should throw error here
    plaintext = "";
    for (long y: ciphertext) plaintext += dec_char(long(y));

    // plaintext = dec_char(ciphertext);
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
    return ciphertext;
}

pair<long, long> RSA::get_public_key()
{
    return k.pub;
}

RSA::RSA()
{

}

RSA::RSA(long p, long q)
{
    k.p = p;
    k.q = q;
    key_gen();
}
