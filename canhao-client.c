/* 
    UM CLIENTE TCP
    Autores: 
        Eduardo Gobbo Willi V.G.
        Anderson Aparecido do Carmo Frasão
    ultima atualizacao. 05/fev/2023
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // close()
#include <netdb.h> // sistema DNS-revis
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    int sockdescr;
    // int numbytesrecv; // nao usa
    struct sockaddr_in servaddr;
    struct hostent *server; // hp
    char buffer[BUFSIZ+1];
    char *hostname;
    char dados[6] = {0};

    // unsigned int i;


    if(argc != 4) {
        puts("Uso correto: cliente <nome-servidor> <porta> <dados>");
        exit(1);
    }

    hostname = argv[1];
    long int cont = atoi(argv[3]);

    if((server = gethostbyname(hostname)) == NULL) { // cliente DNS chamado de resolvedor
        perror("Nao consegui obter of endereco IP do servidor");
        exit(1);
    }

    bcopy((char*) server->h_addr, (char*) &servaddr.sin_addr, server->h_length);
    servaddr.sin_family = server->h_addrtype;
    servaddr.sin_port = htons(atoi(argv[2])); // faz a conversao Little endian -> Big endian

    if((sockdescr = socket(server->h_addrtype, SOCK_DGRAM, 0)) < 0) {
        perror("Nao consegui criar socket");
        exit(1);
    }

    printf("\nIniciando envio de mensagens!\n\n");
    printf("Serão enviadas %ld mensagens!\n\n", cont);

    for(long int msg = 1; msg <= cont; msg++){
        memset(buffer,0,BUFSIZ+1);  // limpa o buffer

        // transforma int msg em char *dados;
        sprintf(dados, "%ld %ld", msg, cont); 

        if(sendto(sockdescr, dados, strlen(dados)+1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) 
            != strlen(dados)+1) {
            perror("Nao consegui transmitir dados");
            exit(1);
        }

        // Não exclui pois podemos usar de debug se necessario
        // recvfrom(sockdescr, buffer, BUFSIZ, 0, (struct sockaddr *) &servaddr, &i); // se servaddr nao eh NULL, preenche i bytes do sender com ele
        // fprintf(stdout, "Sou o cliente, recebi: %s\n", buffer);
    }

    printf("Todas as mensagens foram enviadas com sucesso!\n\n");

    close(sockdescr);
    exit(0);
}