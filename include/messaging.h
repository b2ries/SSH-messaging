#ifndef MESSAGING_H
#define MESSAGING_H

void send_message(const char *message, const char *host);
void receive_message(const char *encrypted_message, const char *iv);

#endif // MESSAGING_H
