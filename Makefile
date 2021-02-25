CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -g
OBJ=aes.o tables.o
EXEC=aes
LFLAGS=-lm

aes: main.o $(OBJ)
	$(CC) main.o $(OBJ) $(LFLAGS) -o aes

main.o: main.c
	$(CC) $(CFLAGS) -c main.c $(LFLAGS) -o main.o

aes.o: aes.h aes.c
	$(CC) $(CFLAGS) -c aes.c -o aes.o

tables.o: aes.h tables.h tables.c
	$(CC) $(CFLAGS) -c tables.c -o tables.o

clean:
	rm -f $(EXEC) *.o *~

format:
	find . -name "*.c" | xargs indent -par -br -brf -brs -kr -ci2 -cli2 -i2 -l80 -nut
	find . -name "*.h" | xargs indent -par -br -brf -brs -kr -ci2 -cli2 -i2 -l80 -nut
