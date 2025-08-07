#include "crypt.hpp"

int crypt::exp(int x, int H, int n)
{
    bool flip = false;
    if (H < 0 && H % 2 == 1)
    {
        flip = true;
        H *= -1;
    }
    else if (H < 0) H*=-1;

    bitset<32> h(H);
    int t = h.size() - 1;
    while (h[t] != 1) {t--;}
    int r = x;
    for (int i = t - 1; i >= 0; i--)
    {
        r = (r*r) % n;
        if (h[i] == 1) r = (r * x) % n;
    }

    if (flip) r*=-1;

    return r;
}

int crypt::fermat(int p)  // returns 1 (likely) prime, 0 if -> broken for numbers < 4
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

pair<int,pair<int,int>> crypt::extended_euclid(int r0, int r1)
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