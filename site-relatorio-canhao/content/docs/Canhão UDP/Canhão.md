# Canhão UDP 

{{< figure src="../cannon.webp" width="400" class="center round" >}}

## Descrição
Este trabalho consiste da implementação de um sistema cliente-servidor, onde o sistema irá operar sobre o protocolo de transporte UDP.

Nesta implementação, o cliente irá enviar uma quantidade significativa de dados ("canhão") para o servidor. Ao receber os dados, o servidor irá tomar conta e analisar conforme as mensagens chegam, quais pacotes tiveram sua ordem invertida e quantos pacotes nunca chegaram.

## Objetivo
O objetivo deste trabalho é poder medir o desempenho da rede, ao medir quantos pacotes tiveram sua ordem de chegada invertida e quantos não chegaram ao final.

Primeiramente, o servidor deve ser executado e deixado "rodando" antes de se executar o cliente. Ao ser executado, o servidor irá tentar obter seu endereço IP, abrir um socket e solicitar o uso da porta especificada para o sistema operacional. Em seguida, o servidor entrará em um laço infinito, onde irá receber mensagens do cliente e irá salvar no log a sequência de eventos que vão ocorrer. Caso o número de pacotes enviados seja inferior ao número de pacotes recebidos, o servidor irá enviar um mensagem de erro após 10 segundos sem receber novos pacotes.

Os clientes iniciam em uma sequência de passos semelhante, onde irão tentar obter o endereço IP do servidor e criar um socket. Neste ponto, o sistema está pronto para iniciar o tráfego de mensagens.

Mais detalhes sobre a execução do [servidor](../servidor) e do [cliente](../cliente) são apresentados nestes links.