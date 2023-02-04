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

A página web contruida para o relatório foi feita utilizando `hugo` e o build da pagina pode ser visualizado do diretório `docs/`. O tema utilizado pode ser acessado em https://themes.gohugo.io/themes/hugo-book/.

Para instalar hugo você pode seguir as intruções neste site https://gohugo.io/installation/linux/

O codigo fonte da pagina está presente em `site-relatorio-canhao`, e dentro dele você irá encontrar dois scripts:
- `update_github_site.sh`
- `visualiza_site.sh`

Para visualizar as mudanças feitas no site na maquina local `localhost:1313`, sem mudar o codigo em docs, basta executar
```
bash visualiza_site.sh
```

**ATENÇÃO!!!** o script que atualiza o site do github deleta o conteudo autal de `docs/` e copia o novo código de build, então use-o somente ao ter certeza que o site no localhost já está funcionando.
```
bash update_github_site.sh
```

### Execução

Para escutar a comunicação UDP (loopback), rodar em linha de comando:

    sudo tcpdump -i lo -s 0 host <name-host> and udp

site: https://gobbedu.github.io/Canhao-UDP/