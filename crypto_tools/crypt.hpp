#ifndef CRYPT_HPP
#define CRYPT_HPP
#include <iostream>
#include <vector>
#include <bitset>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace crypt
{
    int exp(int x, int H, int n);
    int fermat(int p);
    pair<int,pair<int,int>> extended_euclid(int r0, int r1);
}

#endif