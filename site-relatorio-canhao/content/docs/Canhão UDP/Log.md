---
title: "Log"
date: 2023-02-23T10:18:19-03:00
---

# Arquivo Log

- O log criado segue os seguintes formatos:

## Cliente
Após executar `egwvg20@h10:Canhao-UDP$ ./cliente h11 2000 100`. 
Apenas indica quando houve o fim da transmissão de disparos, como no exemplo abaixo:
```rust
Iniciando envio de mensagens!

Serão enviadas 100 mensagens!

Todas as mensagens foram enviadas com sucesso!
```

## Servidor
Após executar `egwvg20@h11:Canhao-UDP$ ./servidor 2000`
Fica em loop infinito, até que seja encerrado com Ctrl+C. Só é adicionado uma nova mensagem ao log 
caso:
1. Houve erro na recepção da sequência da mensagem
2. Recebeu todas as mensagens
3. O socket que recebe dados no servidor recebeu TIMEOUT

Se ocorrer **1 ou 3**, o log vai indicar quais mensagens chegaram corretamente em um intervalo:
```rust
Servidor recebeu [ X .. Y ] OK
```
Caso ocorra **1**, logo em seguida indica qual mensagem o servidor esperava e qual ele acabou recebendo.
Após a inversão de sequência, a mensagem esperada pelo servidor é atualizada como sendo a próxima sequência contando partir da sequência recebida.
```rust
Servidor esperava A, recebeu B => fora de sequencia, espera B+1
```

Ao final, é indicado a porcentagem de mensagens recebidas e perdidas.
```rust
Servidor canhao: foi recebido 100.00% do total de disparos!
Servidor canhao: foi perdido  0.00% do total de disparos!
```

### Exemplo com 100 disparos
```rust
Servidor ouvindo na porta 2000
Servidor recebeu [ 1 .. 100 ] OK
Servidor canhao: Todas as mensagens foram recebidas!
Servidor canhao: foi recebido 100.00% do total de disparos!
Servidor canhao: foi perdido  0.00% do total de disparos!
Servidor ouvindo na porta 2000
```


## Rodada maior Servidor
```rust
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
. (comentado para brevidade)
.
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
Servidor canhao: foi recebido 97.86% do total de disparos!
Servidor canhao: foi perdido  2.13% do total de disparos!
Servidor ouvindo na porta 2000
```

# Testes de perda Consecutivos:
**Somente relatório final apontado pelo servidor**

Para **1*10^6** mensagens: (1M)
```rust
Servidor canhao: foi perdido  14.26% do total de disparos!
Servidor canhao: foi perdido  7.68% do total de disparos!
Servidor canhao: foi perdido  1.32% do total de disparos!
```

Para **1*10^7** mensagens: (10M)
```rust
Servidor canhao: foi perdido  1.77% do total de disparos!
Servidor canhao: foi perdido  5.31% do total de disparos!
Servidor canhao: foi perdido  7.32% do total de disparos!
```

Para **1*10^8** mensagens: (100M)
```rust
Servidor canhao: foi perdido  8.80% do total de disparos!
Servidor canhao: foi perdido  8.79% do total de disparos!
Servidor canhao: foi perdido  15.49% do total de disparos!
Servidor canhao: foi perdido  12.31% do total de disparos!
```

## Resultado

Utilizando as execuções acima, no calculo abaixo
```python
(
    1e6*(14.26 + 7.68 + 1.32)/3 + 
    1e7*(1.77 + 5.31 + 7.32)/3 + 
    1e8*(8.80 + 8.79 + 15.49 + 12.31)/4
)/(1e6 + 1e7 + 1e8)
```
Podemos estimar que:
{{< hint danger >}}
A média obtida da execução entre as máquinas h10 e h11 na rede do departamento de informatica foi de:
- **10.73%**
{{<\ hint >}}
