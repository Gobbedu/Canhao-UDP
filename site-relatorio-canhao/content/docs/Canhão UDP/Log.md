---
title: "Log"
date: 2023-02-23T10:18:19-03:00
---


O log criado segue o seguinte formato:

### Cliente
Após executer `egwvg20@h10:Canhao-UDP$ ./cliente h11 2000 100`
```
Iniciando envio de mensagens!

Serão enviadas 100 mensagens!

Todas as mensagens foram enviadas com sucesso!
```

### Servidor
Após executar `egwvg20@h11:Canhao-UDP$ ./servidor 2000`
```
Servidor ouvindo na porta 2000
Servidor recebeu [ 1 .. 100 ] OK
Servidor canhao: Todas as mensagens foram recebidas!
Servidor canhao: foi recebido 100.00% do total de disparos!
Servidor ouvindo na porta 2000
```

### Rodada maior Cliente
Após rodar `./cliente h11 2000 1000000`
```
Iniciando envio de mensagens!

Serão enviadas 1000000 mensagens!

Todas as mensagens foram enviadas com sucesso!
```

### Rodada maior Servidor
```
Servidor ouvindo na porta 2000
Servidor recebeu [ 1 .. 13209 ] OK
Servidor esperava 13210, recebeu 13234 => fora de sequencia, espera 13235
Servidor recebeu [ 13235 .. 13373 ] OK
Servidor esperava 13374, recebeu 13447 => fora de sequencia, espera 13448
Servidor recebeu [ 13448 .. 13586 ] OK
Servidor esperava 13587, recebeu 13646 => fora de sequencia, espera 13647
Servidor recebeu [ 13647 .. 13715 ] OK
Servidor esperava 13716, recebeu 13797 => fora de sequencia, espera 13798
Servidor recebeu [ 13798 .. 13936 ] OK
.
. (comentado para breviedade)
.
Servidor esperava 715325, recebeu 715381 => fora de sequencia, espera 715382
Servidor recebeu [ 715382 .. 715450 ] OK
Servidor esperava 715451, recebeu 715482 => fora de sequencia, espera 715483
Servidor recebeu [ 715483 .. 715551 ] OK
Servidor esperava 715552, recebeu 715677 => fora de sequencia, espera 715678
Servidor recebeu [ 715678 .. 715746 ] OK
Servidor esperava 715747, recebeu 715749 => fora de sequencia, espera 715750
Servidor recebeu [ 715750 .. 716028 ] OK
Servidor esperava 716029, recebeu 716105 => fora de sequencia, espera 716106
Servidor recebeu [ 716106 .. 722474 ] OK
Servidor esperava 722475, recebeu 722480 => fora de sequencia, espera 722481
Servidor recebeu [ 722481 .. 722759 ] OK
Servidor esperava 722760, recebeu 722769 => fora de sequencia, espera 722770
Servidor recebeu [ 722770 .. 1000000 ] OK
Servidor erro timeout recv : (Resource temporarily unavailable); errno: (11)
Servidor canhao: foram perdidas 21367 mensagens
Servidor canhao: foi recebido 97.86% do total de disparos
Servidor canhao: foi perdido  2.13% do total de disparos
Servidor ouvindo na porta 2000
```


A média obtida da execução entre as máquinas h10 e h11 na rede do departamento de informatica foi de:
{{< hint danger >}}

Perda de disparos: **30%**
{{<\ hint >}}
