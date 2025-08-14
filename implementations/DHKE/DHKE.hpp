// implemented using Z*: multiplicative group of a prime field 
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <bitset>
#include <vector>
#include "primes.hpp"
#include "fast_exp.hpp"
using namespace std;

class DHKE
{
public:
    int p;  // refers to the index of the prime
    int alpha;  
    int k_pub;
private:
    int seed;
    int k_priv;
    int k_shared;

// helpers

    void choose_p();
    void choose_alpha();

    void choose_k_priv();
    void compute_k_pub();

protected:
    void compute_k_shared(int other_k_pub);

public:

    void gen_domain_parameters();
    std::pair<int, int> get_domain_parameters();

    void key_exchange(DHKE &other);

    int get_k_shared();
    
    DHKE();
    DHKE(int t);  // for random time/seed
};