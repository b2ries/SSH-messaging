#include "messaging.h"
#include <stdio.h>

int main() {
    const char *host = "192.28.16.32"; // Example host
    char message[256];

    printf("Que voulez vous envoyer ?\n");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline

    send_message(message, host);

    return 0;
}