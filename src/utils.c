#include "utils.h"
#include <string.h>

void secure_zero_memory(void *v, size_t n) {
    volatile char *p = v;
    while (n--) {
        *p++ = 0;
    }
}

void clear_memory(char *buffer, size_t size) {
    memset(buffer, 0, size); // Clear the buffer
}