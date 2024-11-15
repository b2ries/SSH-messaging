#include "encryption.h"
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

void encrypt_message(const char *message, char *encrypted_message, char *iv) {
    AES_KEY enc_key;
    unsigned char key[32]; // AES-256 key
    RAND_bytes(key, sizeof(key)); // Generate a random key
    RAND_bytes((unsigned char *)iv, AES_BLOCK_SIZE); // Generate a random IV

    AES_set_encrypt_key(key, 256, &enc_key);

    // Pad message to be multiple of AES_BLOCK_SIZE
    size_t len = strlen(message);
    size_t padded_len = ((len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;
    unsigned char *padded_message = malloc(padded_len);
    memset(padded_message, 0, padded_len);
    memcpy(padded_message, message, len);

    AES_cbc_encrypt(padded_message, (unsigned char *)encrypted_message, padded_len, &enc_key, (unsigned char *)iv, AES_ENCRYPT);

    free(padded_message);
}

void decrypt_message(const char *encrypted_message, const char *iv, char *decrypted_message) {
    AES_KEY dec_key;
    unsigned char key[32]; // AES-256 key
    RAND_bytes(key, sizeof(key)); // Use the same key for decryption

    AES_set_decrypt_key(key, 256, &dec_key);
    AES_cbc_encrypt((unsigned char *)encrypted_message, (unsigned char *)decrypted_message, AES_BLOCK_SIZE, &dec_key, (unsigned char *)iv, AES_DECRYPT);
}