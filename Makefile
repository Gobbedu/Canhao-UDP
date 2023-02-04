# Makefile para o Canhão UDP
# Autores: 
# 	Anderson Aparecido do Carmo Frasão
# 	Eduardo Gobbo Willi Vasconcellos Gonçalves
# Ultima atualização 03/02/2023

CC = gcc 

#-----------------------------------------------------------------------------#
all : servidor cliente

servidor: servidor.o

cliente: cliente.o

#-----------------------------------------------------------------------------#

clean :
	$(RM) *.o

#-----------------------------------------------------------------------------#

purge:
	$(RM) servidor cliente *.o