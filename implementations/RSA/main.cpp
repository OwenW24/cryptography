#include "rsa.hpp"

int main()
{
    RSA alice;
    RSA bob;

    string message = "TESTING TESTING";
    cout << message << endl;
    alice.set_plaintext(message);
    alice.enc();

    string ys = alice.get_ciphertext();
    cout << ys << endl;
    bob.set_ciphertext(ys);
    bob.dec();
    
    string xs = bob.get_plaintext();

    cout << xs << endl;
    return 0;
}