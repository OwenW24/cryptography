#include "rsa.hpp"

int main()
{
    RSA alice;
    RSA bob(3001, 2999);

    string message = "This_is_a_AES_Key";
    alice.set_plaintext(message);
    alice.enc(bob.get_public_key());

    vector<long> ys = alice.get_ciphertext();
    for (long y: ys) cout << y << " ";
    cout << endl;

    bob.set_ciphertext(ys);
    bob.dec();
    cout << bob.get_plaintext();

    return 0;
}