/* 
    UM SERVIDOR TCP iterativo
    Autor: Eduardo Gobbo Willi V.G.
    ultima atualizacao. 01/fev/2023
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h> // sistema DNS-revis
#include <stdlib.h>
#include <string.h>

#define TAM_FILA 5 // tamanho da fila no servidor
#define MAXHOSTNAME 30 // tamanho do ip do servidor pode mudar

int main(int argc, char *argv[]) {
    int sock_escuta; // socket para escuta
    int sock_atende; // para atender cliente    
    struct sockaddr_in servaddr, clientaddr; // addr do servidor e cliente
    struct hostent *server; // registro que o DNS retorna pra nós (hp)
    char localhost[MAXHOSTNAME]; // ip do servidor
    char buffer[BUFSIZ+1]; // buffer para receber dados

    
    if(argc != 2) {
        puts("Uso correto: servidor <porta>");
        exit(1);
    }
    
    // obtem nome do host no qual o servidor esta rodando
    gethostname(localhost, MAXHOSTNAME); // SYSTEM CALL

    if((server = gethostbyname(localhost)) == NULL) {
        perror("Nao consegui obter meu proprio endereco IP do servidor");
        exit(1);
    }

    servaddr.sin_port = htons(atoi(argv[1]));
    servaddr.sin_family = server->h_addrtype;
    bcopy((char*) server->h_addr, (char*) &servaddr.sin_addr, server->h_length);

    if ((sock_escuta = socket(server->h_addrtype, SOCK_DGRAM, 0)) < 0 ){
        perror("Nao consegui criar socket");
        exit(1);
    }

    if (bind(sock_escuta, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("Nao consegui fazer o bind");
        exit(1);
    }

    listen(sock_escuta, TAM_FILA);

    int i;
    while(1) {
        i = sizeof(servaddr);
        puts("Vou bloquear esperando mensagem.");

        //clean buffer
        memset(buffer, 0, BUFSIZ);

        recvfrom(sock_escuta, buffer, BUFSIZ, 0, (struct sockaddr *) &clientaddr, &i);
        printf("Sou o servidor, recebi a mensagem -----> %s\n", buffer);

        sendto(sock_escuta, buffer, BUFSIZ, 0, (struct sockaddr *) &clientaddr, i);
        close(sock_atende);

    }

    exit(0);
}
