#include "rsa.hpp"

int main()
{
    RSA alice;
    RSA bob(991, 997);  // problem with small ps and qs breaks with some large nums
    // biggest problem is when d is super big, doing exponents is tough, need to optimize
    // need an algorithm thatll choose the lowest e and d pair
    int message = 123;
    cout << message << endl;
    alice.set_plaintext(message);
    cout << bob.get_public_key().first << " " << bob.get_public_key().second << endl;
    alice.enc(bob.get_public_key());

    int ys = alice.get_ciphertext();
    cout << ys << endl;
    bob.set_ciphertext(ys);
    bob.dec();
    
    int xs = bob.get_plaintext();

    cout << xs << endl;
    return 0;
}