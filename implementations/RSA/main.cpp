#include "rsa.hpp"

int main()
{
    RSA alice;
    RSA bob(991, 997);
    
    string message = "This_is_a_DSA_Key";
    cout << message << endl;
    vector<long> ys;
    for (long x : message)
    {
        alice.set_plaintext(x);
        alice.enc(bob.get_public_key());
        ys.push_back(alice.get_ciphertext());
    }

    for (long y:ys) cout << y << " ";
    cout << endl; 

    string xs;
    for (long y: ys)
    {
        bob.set_ciphertext(y);
        bob.dec();
        xs.push_back(bob.get_plaintext());
    }
    cout << xs << endl;

    return 0;
}