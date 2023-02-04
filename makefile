CC=gcc
CFLAGS=-Wall


.PHONY: all clean purge 

all: servidor cliente

servidor: 
	$(CC) server-udp.c -o servidor

cliente:
	$(CC) client-udp.c -o cliente

clean:
	rm -f *.o ~*

purge: clean
	rm -f servidor cliente