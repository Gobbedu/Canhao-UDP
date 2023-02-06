/* 
    UM SERVIDOR TCP iterativo
    Autores: 
        Eduardo Gobbo Willi V.G.
        Anderson Aparecido do Carmo Frasão
    ultima atualizacao. 06/fev/2023
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
    bcopy((char*) server->h_addr, (char*) &servaddr.sin_addr, server->h_length);
    servaddr.sin_family = server->h_addrtype;

    if ((sock_escuta = socket(server->h_addrtype, SOCK_DGRAM, 0)) < 0 ){
        perror("Nao consegui criar socket");
        exit(1);
    }

    if (bind(sock_escuta, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
        perror("Nao consegui fazer o bind");
        exit(1);
    }

    listen(sock_escuta, TAM_FILA);

    int aux_cont = 1;
    char cont[6] = {0};
    // char* n_msg; // Descomentar depois, é usado para o teste de perda de mensagem
    char* n_sec;

    unsigned int i;
    while(1) {
        i = sizeof(clientaddr);
        // puts("Vou bloquear esperando mensagem.");

        // limpa o buffer
        memset(buffer, 0, BUFSIZ);

        // transforma int msg em char *dados;
        sprintf(cont, "%d", aux_cont);

        recvfrom(sock_escuta, buffer, BUFSIZ, 0, (struct sockaddr *) &clientaddr, &i);
        // printf("Sou o servidor, recebi a mensagem -----> %s\n", buffer);

        n_sec = strtok(buffer, " ");
        // n_msg = strtok(NULL, " "); // Descomentar depois, é usado para o teste de perda de mensagem

        // Verifica se o contador local esta igual ao numero de sequencia presente na mensagem
        // Esse verificador só funciona pra uma sequencia de mensagens
        // Caso queira mandar outra sequencia, resete o servidor!!!!!!
        if (strcmp(n_sec, cont) != 0)
            printf("As mensagens estão fora de ordem!\n");

        // int n_msg_aux = atoi(n_msg); // Descomentar depois, é usado para o teste de perda de mensagem

        // Verifica se o contador local é diferente do numero total de mensagens enviadas
        /* 
            Problema: o contador local só vai ser igual ao numero de mensagens enviadas na ultima mensagem,
            então essa verificação só deveria ser feita na ultima mensagem
            mas estamos dentro de um while(true), e não queremos ficar recebendo mensagem 
            de erro quando não esta errado...
            Possivel solução:

                le a primeira mensagem fora do laço
                faz um for com o segundo valor da mensagem como limitante
                e após o for, verifica se o contador local é igual ao numero de mensagens enviadas

            Porém se a gente perder alguma mensagem, o servidor vai ficar travado esperando
            podemos resolver isso com um timeout
        */
        // if(n_msg_aux != aux_cont)
        //     printf("Houve perda de mensagem!\n");

        aux_cont++;

        sendto(sock_escuta, buffer, BUFSIZ, 0, (struct sockaddr *) &clientaddr, i);
    }

    exit(0);
}
