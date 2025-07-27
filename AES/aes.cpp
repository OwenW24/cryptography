#include "aes.hpp"

unsigned char AES::getSBoxValue(unsigned char num){return sbox[num];}
unsigned char AES::getSBoxInvert(unsigned char num){return rsbox[num];}
unsigned char AES::getRconValue(unsigned char num){return rcon[num];}

// AES Encryption

// Byte Substitution
void AES::byteSub(unsigned char* state)
{
    for (int i = 0; i < 16; i++) state[i] = getSBoxValue(state[i]);
}

// Diffusion Layer

// Shift Rows
void AES::shiftRow(unsigned char* state, unsigned char num)
{
    unsigned char tmp;
    for (int i = 0; i < num; i++)
    {
        tmp = state[0];
        for (int j = 0; j < 3; j++) state[j] = state[j+1];
        state[3] = tmp;
    }
}

void AES::shiftRows(unsigned char* state)
{
    for (int i = 0; i < 4; i++) shiftRow(state + i * 4, i);
}

// Mix Column
unsigned char AES::galois_multiplication(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char hi_bit_set;
    for (unsigned char counter = 0; counter < 8; counter++)
    {
        if ((b & 1) == 1) p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80) a^= 0x1B;
        b >>= 1;
    }
    return p;
}

void AES::mixColumn(unsigned char* column)
{
    unsigned char cpy[4];
    for (int i = 0; i < 4; i++) cpy[i] = column[i];
    column[0] = galois_multiplication(cpy[0], 2) ^ galois_multiplication(cpy[3], 1) ^ galois_multiplication(cpy[2], 1) ^ galois_multiplication(cpy[1], 3);
    column[1] = galois_multiplication(cpy[1], 2) ^ galois_multiplication(cpy[0], 1) ^ galois_multiplication(cpy[3], 1) ^ galois_multiplication(cpy[2], 3);
    column[2] = galois_multiplication(cpy[2], 2) ^ galois_multiplication(cpy[1], 1) ^ galois_multiplication(cpy[0], 1) ^ galois_multiplication(cpy[3], 3);
    column[3] = galois_multiplication(cpy[3], 2) ^ galois_multiplication(cpy[2], 1) ^ galois_multiplication(cpy[1], 1) ^ galois_multiplication(cpy[0], 3);
}
void AES::mixColumns(unsigned char* state)
{
    unsigned char column[4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++) column[j] = state[(j * 4) + i];
        mixColumn(column);
        for (int j = 0; j < 4; j++) state[((j * 4) + i)] = column[j];
    }
}

// Key Addition
void AES::keyAddition(unsigned char* state, unsigned char* roundKey)
{
    for (int i = 0; i < 16; i++) state[i] = state[i] ^ roundKey[i];
}

// Key Schedule 
void AES::rotate(unsigned char* word)
{
    unsigned char c;
    c = word[0];
    for (int i = 0; i < 3; i++) word[i] = word[i + 1];
    word[3] = c;
}
void AES::core(unsigned char* word, int it)
{
    rotate(word);
    for (int i = 0; i < 4; i++) word[i] = getSBoxValue(word[i]);
    word[0] = word[0] ^ getRconValue(it);

}
void AES::expandKey(unsigned char* expandedKey, unsigned char* key, enum keySize size, size_t expandedKeySize)
{
    int currentSize = 0;
    int rconIt = 1;
    unsigned char tmp[4] = {0};
    for (int i = 0; i < size; i++) expandedKey[i] = key[i];
    currentSize += size;
    while (currentSize < expandedKeySize){
        for (int i = 0; i < 4; i++) tmp[i] = expandedKey[(currentSize - 4) + i];
        
        if (currentSize % size == 0) core(tmp, rconIt++);
        
        if (size == SIZE_32 && ((currentSize % size) == 16)) for (int i = 0; i < 4; i++) tmp[i] = getSBoxValue(tmp[i]);

        for (int i = 0; i < 4; i++)
        {
            expandedKey[currentSize] = expandedKey[currentSize - size] ^ tmp[i];
            currentSize++;
        }
    }
    
}

// AES rounds & body
void AES::createRoundKey(unsigned char* expandedKey, unsigned char* roundKey)
{
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) roundKey[(i + (j * 4))] = expandedKey[(i * 4) + j];
}
void AES::aes_round(unsigned char* state, unsigned char* roundKey)
{
    byteSub(state);
    shiftRows(state);
    mixColumns(state);
    keyAddition(state, roundKey);
}
void AES::aes_main(unsigned char* state, unsigned char* expandedKey, int numRounds)
{
    unsigned char roundKey[16];
    createRoundKey(expandedKey, roundKey);
    keyAddition(state, roundKey);
    for (int i = 1; i < numRounds; i++)
    {
        createRoundKey(expandedKey + 16 * i, roundKey);
        aes_round(state, roundKey);
    }
    createRoundKey(expandedKey + 16 * numRounds, roundKey);
    byteSub(state);
    shiftRows(state);
    keyAddition(state, roundKey);
}

char AES::aes_encrypt(unsigned char* input, unsigned char* output, unsigned char* key, enum keySize size)
{
    int expandedKeySize;
    int numRounds;
    unsigned char* expandedKey;
    unsigned char block[16];
    switch (size)
    {
    case SIZE_16:
        numRounds = 10;
        break;
    case SIZE_24:
        numRounds = 12;
        break;
    case SIZE_32:
        numRounds = 14;
        break;
    default:
        return ERROR_AES_UNKOWN_KEYSIZE;
        break;
    }
    expandedKeySize = 16 * (numRounds + 1);

    expandedKey = new unsigned char[expandedKeySize];

    
    if (!expandedKey) return ERROR_MEMORY_ALLOCATION_FAILED;
    else
    {
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) block[(i + (j * 4))] = input[(i * 4) + j];
        expandKey(expandedKey, key, size, expandedKeySize);
        aes_main(block, expandedKey, numRounds);
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) output[(i * 4) + j] = block[i + (j * 4)];
        delete expandedKey;
        expandedKey = nullptr;
    }
    return SUCCESS;
}

void AES::invByteSub(unsigned char *state)
{
    for (int i = 0; i < 16; i++) state[i] = getSBoxInvert(state[i]);
}

void AES::invShiftRow(unsigned char *state, unsigned char num)
{
    unsigned char tmp;
    for (int i = 0; i < num; i++)
    {
        tmp = state[3];
        for (int j = 3; j > 0; j--) state[j] = state[j - 1];
        state[0] = tmp;
    }
}

void AES::invShiftRows(unsigned char *state)
{
    for (int i = 0; i < 4; i++) invShiftRow(state + i * 4, i);
}

void AES::invMixColumn(unsigned char *column)
{
    unsigned char cpy[4];
    for (int i = 0; i < 4; i++) cpy[i] = column[i];
    column[0] = galois_multiplication(cpy[0], 14) ^ galois_multiplication(cpy[3], 9) ^ galois_multiplication(cpy[2], 13) ^ galois_multiplication(cpy[1], 11);
    column[1] = galois_multiplication(cpy[1], 14) ^ galois_multiplication(cpy[0], 9) ^ galois_multiplication(cpy[3], 13) ^ galois_multiplication(cpy[2], 11);
    column[2] = galois_multiplication(cpy[2], 14) ^ galois_multiplication(cpy[1], 9) ^ galois_multiplication(cpy[0], 13) ^ galois_multiplication(cpy[3], 11);
    column[3] = galois_multiplication(cpy[3], 14) ^ galois_multiplication(cpy[2], 9) ^ galois_multiplication(cpy[1], 13) ^ galois_multiplication(cpy[0], 11);
}

void AES::invMixColumns(unsigned char *state)
{
    unsigned char column[4];
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++) column[j] = state[(j * 4) + i];
        invMixColumn(column);
        for (int j = 0; j < 4; j++) state[(j * 4) + i] = column[j];

    }
}

void AES::aes_invRound(unsigned char *state, unsigned char *roundKey)
{
    invShiftRows(state);
    invByteSub(state);
    keyAddition(state, roundKey);
    invMixColumns(state);
}

void AES::aes_invMain(unsigned char *state, unsigned char *expandedKey, int numRounds)
{
    unsigned char roundKey[16];
    createRoundKey(expandedKey + 16 * numRounds, roundKey);
    keyAddition(state, roundKey);
    for (int i = numRounds - 1; i > 0; i--)
    {
        createRoundKey(expandedKey + 16 * i, roundKey);
        aes_invRound(state, roundKey);
    }
    createRoundKey(expandedKey, roundKey);
    invShiftRows(state);
    invByteSub(state);
    keyAddition(state, roundKey);

}

char AES::aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size)
{
    int expandedKeySize;
    int numRounds;
    unsigned char* expandedKey;
    unsigned char block[16];

    switch (size)
    {
    case SIZE_16:
        numRounds = 10;
        break;
    case SIZE_24:
        numRounds = 12;
        break;
    case SIZE_32:
        numRounds = 14;
        break;
    default:
        return ERROR_AES_UNKOWN_KEYSIZE;
        break;
    }
    expandedKeySize = (16 * (numRounds + 1));
    expandedKey = new unsigned char[expandedKeySize];
    if (!expandedKey) return ERROR_MEMORY_ALLOCATION_FAILED;
    else{
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) block[i + (j * 4)] = input[(i * 4) + j];
        expandKey(expandedKey, key, size, expandedKeySize);
        aes_invMain(block, expandedKey, numRounds);
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) output[(i*4) + j] = block[i + (j * 4)];
        delete expandedKey;
        expandedKey = nullptr;
    }
    return SUCCESS;
}



// public methods
AES::AES(){}

void AES::set_plaintext(unsigned char* plaintext){this->plaintext = plaintext;}
void AES::set_ciphertext(unsigned char* ciphertext){this->ciphertext = ciphertext;}
void AES::set_decryptedtext(unsigned char* decryptedtext){this->decryptedtext = decryptedtext;}
void AES::set_key(unsigned char* key){this->key = key;}
void AES::set_keySize(enum keySize size){this->size = size;}

unsigned char* AES::get_plaintext(){return plaintext;}
unsigned char* AES::get_ciphertext(){return ciphertext;}
unsigned char* AES::get_decryptedtext(){return decryptedtext;}


void AES::encrypt(){aes_encrypt(plaintext, ciphertext, key, size);}
void AES::decrypt(){aes_decrypt(ciphertext, decryptedtext, key, size);}

