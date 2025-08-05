#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;  // need to adjust type casting
class RSA
{
private:
    struct key{
        long p, q, phi;
        pair<long, long> pub;
        long prv;
    };

    key k;
    long plaintext;
    long ciphertext;

    void key_gen();

    pair<long,pair<long,long>> extended_euclid(long r0, long r1);
    long exp(long x, long H, long n);
    long fermat(long p);

    
    long enc_char(long x, pair<long, long> pub);
    long dec_char(long y);


    // helpers


public:
    void enc(pair<long, long> pub);
    void dec();
    void set_plaintext(long x);
    void set_ciphertext(long y);

    long get_plaintext();
    long get_ciphertext();
    pair<long, long> get_public_key();

    RSA();
    RSA(long p, long q);
    
}; //need to for decrpt, need to accept others public key