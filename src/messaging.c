#include "../include/messaging.h"
#include "../include/encryption.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For close()
#include <arpa/inet.h> // For socket functions
#include <pthread.h>
#include <libssh2.h>
#include <termios.h> // For hiding password input
#include <openssl/aes.h> // Include OpenSSL AES header

// Define AES_BLOCK_SIZE if not defined
#ifndef AES_BLOCK_SIZE
#define AES_BLOCK_SIZE 16 // AES block size in bytes
#endif

// Function to hide password input
void get_hidden_input(const char *prompt, char *buffer, size_t size) {
    struct termios oldt, newt;
    printf("%s", prompt);
    fflush(stdout);
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO); // Disable echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

void *receive_thread(void *arg) {
    const char *host = (const char *)arg;
    printf("Waiting for incoming messages from %s...\n", host);
    sleep(2); // Simulate waiting for a message
    printf("Received a message from %s!\n", host);
    return NULL;
}

void send_message(const char *message, const char *host) {
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    int rc;

    // Initialize libssh2
    if (libssh2_init(0) != 0) {
        fprintf(stderr, "Could not initialize SSH session\n");
        return;
    }

    // Create a session instance
    session = libssh2_session_init();
    if (!session) {
        fprintf(stderr, "Failed to create SSH session\n");
        return;
    }

    // Connect to the remote host
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(22); // SSH port
    inet_pton(AF_INET, host, &sin.sin_addr);

    if (connect(sock, (struct sockaddr *)(&sin), sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "Failed to connect to %s\n", host);
        return;
    }

    // Ask user for authentication method
    char auth_method[10];
    printf("Choose authentication method (password/key): ");
    scanf("%9s", auth_method);

    // Authentication
    if (strcmp(auth_method, "password") == 0) {
        char username[50];
        char password[50];
        printf("Enter username: ");
        scanf("%49s", username);
        get_hidden_input("Enter password: ", password, sizeof(password));

        rc = libssh2_userauth_password(session, username, password);
        if (rc) {
            fprintf(stderr, "Authentication by password failed\n");
            return;
        }
    } else if (strcmp(auth_method, "key") == 0) {
        char username[50];
        char privatekey[100];
        char passphrase[50];
        printf("Enter username: ");
        scanf("%49s", username);
        printf("Enter path to private key: ");
        scanf("%99s", privatekey);
        get_hidden_input("Enter passphrase (if any): ", passphrase, sizeof(passphrase));

        rc = libssh2_userauth_publickey_fromfile(session, username, NULL, privatekey, passphrase);
        if (rc) {
            fprintf(stderr, "Authentication by public key failed\n");
            return;
        }
    } else {
        fprintf(stderr, "Invalid authentication method\n");
        return;
    }

    // Open a channel
    channel = libssh2_channel_open_session(session);
    if (!channel) {
        fprintf(stderr, "Failed to open channel\n");
        return;
    }

    // Encrypt the message
    char encrypted_message[256];
    char iv[AES_BLOCK_SIZE];
    encrypt_message(message, encrypted_message, iv);

    // Send the IV and the encrypted message
    char command[512];
    snprintf(command, sizeof(command), "echo '%s:%s'", iv, encrypted_message);
    if (libssh2_channel_exec(channel, command)) {
        fprintf(stderr, "Failed to execute command\n");
        return;
    }

    // Cleanup
    libssh2_channel_send_eof(channel);
    libssh2_channel_wait_eof(channel);
    libssh2_channel_close(channel);
    libssh2_channel_free(channel);
    
    // Disconnect and cleanup
    libssh2_session_disconnect(session, "Normal Shutdown");
    libssh2_session_free(session);
    close(sock);
    libssh2_exit();

    printf("Sent message to %s: %s\n", host, message);
    
    // Start the receive thread
    pthread_t tid;
    if (pthread_create(&tid, NULL, receive_thread, (void *)host)) {
        fprintf(stderr, "Error creating thread\n");
        return;
    }
    pthread_detach(tid);
}

void receive_message(const char *encrypted_message, const char *iv) {
    char decrypted_message[256];
    decrypt_message(encrypted_message, iv, decrypted_message);
    printf("Decrypted message: %s\n", decrypted_message);
}
