## Entendendo o EP

Dois candidatos A e B
Número de Votantes = N
ƒ = probabilidade de falha
T = quantidade de simulações
tol = tolerância na probabilidade de erro
alpha = porcentagem de votantes em A

Falhas ocorrem de forma independente para cada votante

Probabilidade de erro pode ser estimada realizando experimentos aleatórios que simulam a eleição T vezes.

**Qual é a probabilidade de que o candidato B obtenha mais votos que A?**

Se esse evento ocorrer, a eleição teve **erro**
O erro é estimado simulando várias eleições. Quando uma eleição dá erro, subimos o score em 1. **A probabilidade de erro é a quantidade de erros/total de simulações**

A pegunta final que queremos responder é: **Qual a máxima probabilidade**