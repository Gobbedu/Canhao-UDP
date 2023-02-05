# Makefile para o Canhão UDP
# Autores: 
# 	Anderson Aparecido do Carmo Frasão
# 	Eduardo Gobbo Willi Vasconcellos Gonçalves
# Ultima atualização 03/02/2023


CC=gcc
CFLAGS=-Wall -g


.PHONY: all clean purge 

all: servidor cliente

servidor: 
	$(CC) $(CFLAGS) server-udp.c -o servidor

cliente:
	$(CC) $(CFLAGS) canhao-client.c -o cliente

#-----------------------------------------------------------------------------#

clean:
	rm -f *.o ~*

purge: clean
	rm -f servidor cliente