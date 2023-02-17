# Servidor UDP

O objetivo do servidor é analisar as mensagens recebidas e imprimir em um log a sequência de eventos que vão ocorrer. Por exemplo, qual sequência chegou em ordem, em qual momento uma mensagem chegou fora da sequência, etc.

O servidor deve ser executado da seguinte maneira:
```sh
./servidor <porta>
```

De forma que o socket ficará ouvindo em um loop infinito na porta **\<porta\>**.
O socket do servidor foi configurado para retornar um erro de timeout a cada 10 segundos, função que nos auxilia a verificar se mensagens do cliente nunca chegaram, para o servidor encerrar esta análise e voltar a ouvir na porta, esperando uma nova leva de mensagens.

O socket foi configurado da seguinte maneira para retornar timeout: 

```c
 // seta recv socket options to timeout at 10 seconds
    struct timeval optval;
    optval.tv_sec = 10;
    optval.tv_usec = 0;
    if (setsockopt(sock_escuta, SOL_SOCKET, SO_RCVTIMEO, &optval, sizeof(optval)) < 0) {
        perror("Nao consegui setar timeout");
        exit(1);
    }
```

## Kernel

A parte central de execução deste código é realçado abaixo, a sessão que reinicia os parâmetros para ouvir a uma nova leva de mensagem foram omitidos aqui, mas podem ser visualizados no código RAW disponibilizado no link no final desta página.

```c
long int esperado = 1,  // primeira mensagem esperada
        num_total = -1, // numero total de mensagens
        contador = 0,   // contador de mensagens recebidas
        recebeu;        // mensagem recebida

int recebendo_sequencia = 0; // flag para log de sequencia: serv recebeu [1 .. X] OK

while(1) {
    unsigned int i = sizeof(clientaddr);
    memset(buffer, 0, BUFSIZ);  // Limpa o buffer

    // Recebe mensagem do cliente
    int bytes = recvfrom(sock_escuta, buffer, BUFSIZ, 0, (struct sockaddr *) &clientaddr, &i);
    
    // houve erro no recv
    if((bytes < 1) && (errno == EAGAIN || errno == EWOULDBLOCK)){ 
        // nao faz nada se nao iniciou canhao
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
        printf("Servidor esperava %ld, \
            recebeu %ld => fora de sequencia, espera %ld\n",
            esperado, recebeu, recebeu+1);

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
```

## Fonte
{{< hint danger >}}
O código fonte RAW pode ser acessado [aqui](https://raw.githubusercontent.com/Gobbedu/Canhao-UDP/main/canhao-server.c). 
{{< /hint >}}
Mais informações sobre a origem do código fonte podem ser vistos na pagina [home](../../..) do site.
