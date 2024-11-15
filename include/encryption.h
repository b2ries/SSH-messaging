#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdint.h>

void encrypt_message(const char *message, char *encrypted_message, char *iv);
void decrypt_message(const char *encrypted_message, const char *iv, char *decrypted_message);

#endif // ENCRYPTION_H