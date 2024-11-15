CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -lssh2 -lpthread
SRC = src/main.c src/messaging.c src/encryption.c src/utils.c
OBJ = $(SRC:.c=.o)
TARGET = secure_messaging

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)