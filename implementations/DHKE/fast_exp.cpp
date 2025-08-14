#include "fast_exp.hpp"


fast_exp::fast_exp()
{
}

int fast_exp::exp(int x, int H, int n)
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

