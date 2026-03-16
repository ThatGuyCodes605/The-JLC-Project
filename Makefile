CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = mat
SRC = mat.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

install: $(TARGET)
	sudo cp $(TARGET) /usr/bin/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean install
