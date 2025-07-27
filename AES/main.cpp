#include <iostream>
#include "aes.hpp"

int main()
{

    int expandedKeySize = 176;
    unsigned char expandedKey[expandedKeySize];

    unsigned char key[16] = {'k', 'k', 'k', 'k', 'e', 'e', 'e', 'e', 'y', 'y', 'y', 'y', '.', '.', '.', '.'};

    AES::keySize size = AES::SIZE_16;

    unsigned char plaintext[16] = {'a', 'b', 'c', 'd', 'e', 'f', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};

    unsigned char ciphertext[16];

    unsigned char decryptedtext[16];

    AES test;
    test.set_plaintext(plaintext);
    test.set_ciphertext(ciphertext);
    test.set_decryptedtext(decryptedtext);
    test.set_key(key);
    test.set_keySize(size);

    test.encrypt();
    for (int i = 0; i < 16; i++) std::cout << ciphertext[i] << " ";
    std::cout << std::endl;
    
    test.decrypt();
    for (int i = 0; i < 16; i++) std::cout << decryptedtext[i] << " ";
    std::cout << std::endl;



    return 0;
}