# Canhão UPD

Autores: 
- Anderson Aparecido do Carmo Frasão
- Eduardo Gobbo Willi Vasconcellos Gonçalves
Ultima atualização 04/02/2023

### Descrição do Trabalho

1. O objetivo do Canhão UDP é examinar se há perda de pacote UDP/IP na nossa rede, e qual é a taxa aproximada desta perda. Além disso, deve ser verificado também se as mensagens são entregues fora de ordem.
2. O cliente envia uma sequência de mensagens para o servidor, com um número de sequência: 1, 2, 3, 4... O servidor registra se não recebeu alguma mensagem, ou sequências de mensagens, e se recebeu mensagens fora da ordem.
3. Apresenta logs para múltiplas execuções com cliente e servidor executando em hosts distintos. Mostrando com clareza situações em que há perda de mensagens, ou entrega fora de ordem.

### Estrutura

A página web contruida para o relatório foi feita utilizando `hugo` e o build da pagina pode ser visualizado do diretório `docs/`, o codigo fonte da pagina não está presente em nenhum repositório atualmente.

### Execução

Para escutar a comunicação UDP (loopback), rodar em linha de comando:

    sudo tcpdump -i lo -s 0  -w tcpdump.pcap host <name-host> and udp

Para ler o arquivo tcpdump.pcap:

    Usar wireshark:

        sudo apt install wireshark-qt

        wireshark tcpdump.pcap

site: https://gobbedu.github.io/Canhao-UDP/