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
        int p, q, phi;
        pair<int, int> pub;
        int prv;
    };

    key k;
    string plaintext;
    string ciphertext;

    void key_gen();
    char enc_char(int x);
    char dec_char(int y);


    // helpers
    pair<int,pair<int,int>> extended_euclid(int r0, int r1);
    int exp(int x, int H, int n);
    int fermat(int p);

public:
    void enc();
    void dec();
    void set_plaintext(string xs);
    void set_ciphertext(string ys);

    string get_plaintext();
    string get_ciphertext();
    pair<int, int> get_public_key();

    RSA();
    
}; //need to for decrpt, need to accept others public key