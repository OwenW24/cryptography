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
    string plaintext;
    string ciphertext;

    void key_gen();

    pair<long,pair<long,long>> extended_euclid(long r0, long r1);
    long exp(long x, long H, long n);
    long fermat(long p);

    
    char enc_char(long x, pair<long, long> pub);
    char dec_char(long y);


    // helpers


public:
    void enc(pair<long, long> pub);
    void dec();
    void set_plaintext(string xs);
    void set_ciphertext(string ys);

    string get_plaintext();
    string get_ciphertext();
    pair<long, long> get_public_key();

    RSA();
    RSA(long p, long q);
    
}; //need to for decrpt, need to accept others public key