# Makefile para o Canhão UDP
# Autores: 
# 	Anderson Aparecido do Carmo Frasão
# 	Eduardo Gobbo Willi Vasconcellos Gonçalves
# Ultima atualização 03/02/2023


CC=gcc
CFLAGS=-Wall


.PHONY: all clean purge 

all: servidor cliente

servidor: 
	$(CC) server-udp.c -o servidor

cliente:
	$(CC) client-udp.c -o cliente

#-----------------------------------------------------------------------------#

clean:
	rm -f *.o ~*

purge: clean
	rm -f servidor cliente