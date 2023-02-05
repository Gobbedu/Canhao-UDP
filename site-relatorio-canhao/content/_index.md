---
title: Introdução
type: docs
---

# Canhão UDP

- Usando o tema "{{< param BookTheme >}}"

## Descrição do Trabalho


{{< hint info >}}
O trabalho deve ser feito em **dupla**; o código, os testes e o relatório devem ser feitos por ambos os membros da dupla. Use esta oportunidade para melhorar sua habilidade de trabalhar em equipe.
{{< /hint >}}


1. O objetivo do Canhão UDP é examinar se há perda de pacote UDP/IP na nossa rede, e qual é a taxa aproximada desta perda. Além disso, deve ser verificado também se as mensagens são entregues fora de ordem.
2. Faça um sistema cliente servidor UDP/IP. O cliente envia uma sequência de mensagens para o servidor, com um número de sequência: 1, 2, 3, 4... O servidor deve registrar se não recebeu alguma mensagem, ou sequências de mensagens, e se recebeu mensagens fora da ordem.
3. Devem ser apresentados logs para múltiplas execuções com cliente e servidor executando em hosts distintos. Mostre com clareza situações em que há perda de mensagens, ou entrega fora de ordem.
Cada dupla pode fazer a implementação na linguagem que escolher, o professor sugere Python pela produtividade, mas neste semestre específico quem implementar em Python deve implementar também em C. A diversidade é bem vinda: vão ser valorizados trabalhos em outras linguagens.

## Kernel 
{{< hint danger >}}
Parte principal do código que envia mensagens repetidamente.

Cliente Canhão UDP :
{{< /hint >}}


```c
for(int msg = 1; msg <= cont; msg++){
    memset(buffer,0,BUFSIZ+1);  // limpa o buffer

    // transforma int msg em char *dados;
    sprintf(dados, "%d", msg); 

    if(sendto(sockdescr, dados, strlen(dados)+1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) 
        != strlen(dados)+1) {
        perror("Nao consegui transmitir dados");
        exit(1);
    }

    // se servaddr nao eh NULL, preenche i bytes do sender com ele
    recvfrom(sockdescr, buffer, BUFSIZ, 0, (struct sockaddr *) &servaddr, &i); 
    fprintf(stdout, "Sou o cliente, recebi: %s\n", buffer);
}
```

## Autores

- Eduardo Gobbo Willi Vasconcellos Gonçalves, ([Github](https://github.com/Gobbedu))
- Anderson Aparecido do Carmo Frasão, ([Github](https://github.com/carmofrasao))

