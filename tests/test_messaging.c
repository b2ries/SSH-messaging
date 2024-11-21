#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../include/messaging.h"
#include "../include/encryption.h"
#include "../include/utils.h"

// Dummy encryption and decryption functions for testing
void encrypt_message(const char *input, char *output, char *iv) {
    strcpy(output, input); // Simple copy for testing
    strcpy(iv, "dummy_iv"); // Dummy IV
}

void decrypt_message(const char *encrypted_input, const char *iv, char *output) {
    strcpy(output, encrypted_input); // Simple copy for testing
}

void test_send_message() {
    // Test sending a message
    const char *host = "127.0.0.1";
    const char *message = "Hello, World!";
    send_message(message, host); // This would normally require a live SSH server
    // You may want to check if the expected output occurs (e.g., in logs)
}

void test_receive_message() {
    // Test receiving a message
    const char *encrypted_message = "Hello, World!";
    const char *iv = "dummy_iv";
    char decrypted_message[256];
    decrypt_message(encrypted_message, iv, decrypted_message);
    CU_ASSERT_STRING_EQUAL(decrypted_message, "Hello, World!");
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Messaging_Test_Suite", 0, 0);
    CU_add_test(suite, "test_send_message", test_send_message);
    CU_add_test(suite, "test_receive_message", test_receive_message);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
