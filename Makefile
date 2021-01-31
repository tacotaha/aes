CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -g
OBJ=aes.o
EXEC=aes

aes: main.o $(OBJ)
	$(CC) main.o $(OBJ) -o aes

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

aes.o: aes.h aes.c
	$(CC) $(CFLAGS) -c aes.c -o aes.o

clean:
	rm -f $(EXEC) *.o *~
