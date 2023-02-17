# Cliente UDP

O objetivo do cliente é simples, apenas execute 

```sh
./cliente <endereço servidor> <porta> <número de pacotes>
```

Para enviar ao servidor na porta **\<porta\>** com **\<número de pacotes\>** pacotes.
Estes pacotes serão enviados em ordem, de 1 a N, Cada pacote é enviado uma vez, e contém em seus dados o número da sequencia enviada e o número de pacotes totais a serem enviados.

## Kernel

A parte central de execução deste código é realçado abaixo

```c
long int num_total = atol(argv[3]); // ascii to long int

printf("Iniciando envio de mensagens!\n");
printf("Serão enviadas %ld mensagens!\n", num_total); 

for(long int msg = 1; msg <= num_total; msg++){ 
    memset(buffer,0,BUFSIZ+1);  // limpa o buffer

    // transforma int msg em char *dados;
    sprintf(dados, "%ld %ld", msg, num_total);  

    if(sendto(sockdescr, dados, strlen(dados)+1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) 
        != strlen(dados)+1) {
        perror("Nao consegui transmitir dados");
        exit(1);
    }
}

printf("Todas as mensagens foram enviadas com sucesso!\n\n");
```

## Fonte
{{< hint danger >}}
O código fonte RAW pode ser acessado [aqui](https://raw.githubusercontent.com/Gobbedu/Canhao-UDP/main/canhao-client.c). 
{{< /hint >}}
Mais informações sobre a origem do código fonte podem ser vistos na pagina [home](../../..) do site