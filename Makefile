CC = gcc
CFLAGS = -Wall -Wextra

all: mat jgrep move

mat: mat.c
	$(CC) $(CFLAGS) mat.c -o mat

jgrep: jgrep.c
	$(CC) $(CFLAGS) jgrep.c -o jgrep

move: move.c
	$(CC) $(CFLAGS) move.c -o move

clean:
	rm -f mat jgrep

install: mat jgrep move
	sudo cp mat jgrep move /usr/bin/
