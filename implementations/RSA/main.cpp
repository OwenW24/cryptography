#include "rsa.hpp"

int main()
{
    RSA alice;
    RSA bob(11, 31);  // problem with small ps and qs breaks with some large nums
    // biggest problem is when d is super big, doing exponents is tough, need to optimize
    // need an algorithm thatll choose the lowest e and d pair
    string message = "Hello RSA World!";
    cout << message << endl;
    alice.set_plaintext(message);
    alice.enc(bob.get_public_key());

    string ys = alice.get_ciphertext();
    cout << ys << endl;
    bob.set_ciphertext(ys);
    bob.dec();
    
    string xs = bob.get_plaintext();

    cout << xs << endl;
    return 0;
}