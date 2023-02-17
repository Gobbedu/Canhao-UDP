/* 
    UM SERVIDOR UDP iterativo
    Autores: 
        Eduardo Gobbo Willi V.G.
        Anderson Aparecido do Carmo Frasão
    ultima atualizacao. 10/fev/2023
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h> // sistema DNS-revis
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define TAM_FILA 5 // tamanho da fila no servidor
#define MAXHOSTNAME 30 // tamanho do ip do servidor pode mudar

/* 
    PRECISAMOS DE UM TIMEOUT PARA POSSIVEIS PERDAS DE MENSAGEM
*/

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

    // seta recv socket options to timeout at 10 seconds
    struct timeval optval;
    optval.tv_sec = 10;
    optval.tv_usec = 0;
    if (setsockopt(sock_escuta, SOL_SOCKET, SO_RCVTIMEO, &optval, sizeof(optval)) < 0) {
        perror("Nao consegui setar timeout");
        exit(1);
    }

    long int esperado = 1,  // primeira mensagem esperada
            num_total = -1, // numero total de mensagens
            contador = 0,   // contador de mensagens recebidas
            recebeu;        // mensagem recebida

    int recebendo_sequencia = 0; // flag para log de sequencia: serv recebeu [1 .. X] OK

    while(1){
        printf("Servidor ouvindo na porta %d\n", atoi(argv[1]));

        while(1) {
            unsigned int i = sizeof(clientaddr);
            // puts("Vou bloquear esperando mensagem.\n");

            memset(buffer, 0, BUFSIZ);  // Limpa o buffer

            // Recebe mensagem do cliente
            int bytes = recvfrom(sock_escuta, buffer, BUFSIZ, 0, (struct sockaddr *) &clientaddr, &i);
            
            // ouve erro no recv
            if((bytes < 1) && (errno == EAGAIN || errno == EWOULDBLOCK)){ 
                // nao faz nada se nao iniciou canhao
                // printf("kri kri, "); fflush(stdout);
                if(num_total == -1) {
                    continue;
                }
                // houve erro, encerra log com ultima mensagem recebida
                printf("%ld ] OK\n", esperado-1);
                printf("Servidor erro timeout recv : (%s); errno: (%d)\n", strerror(errno), errno);
                break;
            }
            
            // Encontra o numero de sequencia na mensagem
            recebeu = atol(strtok(buffer, " "));    
            contador++;

            // setar o numero total da sequencia uma vez
            if(num_total == -1) {
                num_total = atol(strtok(NULL, " "));
            }
    
            // esperava I, encontrou J => fora de sequencia, espera J++
            if(recebeu != esperado){
                // quebrou sequencia, finaliza seq no log
                if(recebendo_sequencia){
                    printf("%ld ] OK\n", esperado-1);
                }

                // avisa que perdeu sequencia no log
                printf(
                    "Servidor esperava %ld, recebeu %ld => fora de sequencia, espera %ld\n",
                    esperado, recebeu, recebeu+1
                );

                esperado = recebeu+1;
                recebendo_sequencia = 0;       
            }

            // recebeu [1 ate X] OK
            else if(recebeu == esperado){
                // reiniciando uma sequencia
                if(!recebendo_sequencia){
                    printf("Servidor recebeu [ %ld .. ", recebeu);
                    recebendo_sequencia = 1;
                }

                // no meio de sequencia, continua
                esperado = recebeu+1;
            }

            if(contador == num_total) {
                if(recebendo_sequencia){
                    printf("%ld ] OK\n", esperado-1);
                }
                printf("Servidor canhao: Todas as mensagens foram recebidas!\n");
                break;
            }
        }

        if(contador != num_total){
            printf("Servidor canhao: foram perdidas %ld mensagens\n", num_total - contador);
        }

        // reinicia para escutar novamente
        esperado = 1;  // primeira mensagem esperada
        num_total = -1; // numero total de mensagens
        contador = 0;   // contador de mensagens recebidas
        recebendo_sequencia = 0;
    }

    close(sock_escuta);
    exit(0);
}
