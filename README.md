# Sistema de Manipulação de Dados da Justiça Eleitoral

Trabalho da faculdade que consiste em um sistema desenvolvido em **linguagem C** para a leitura, manipulação e análise de dados jurisdicionais provenientes de arquivos CSV[cite: 2]. [cite_start]O trabalho foi desenvolvido para a disciplina de Estrutura de dados da Universidade Católica de Brasília - UCB[cite: 1].

## Funcionalidades

O sistema utiliza o **TAD Lista** para gerenciar a base de dados [cite: 26] e oferece as seguintes operações:

* **Concatenação de Base:** Consolida múltiplos arquivos CSV em um único arquivo mestre[cite: 15].
* **Geração de Resumo:** Calcula medidas estatísticas por tribunal (Total de julgados, Metas 1, 2 e 4)[cite: 16].
* **Filtro por Município:** Gera um arquivo específico contendo todas as ocorrências de uma cidade informada pelo usuário[cite: 19, 20].

## Metas Calculadas

O sistema processa indicadores de desempenho baseados nas seguintes fórmulas[cite: 18]:

| Indicador | Descrição |
| :--- | :--- |
| **Meta 1** | Relação entre julgados e casos novos/baixados. |
| **Meta 2A/Ant** | Cumprimento de metas para processos antigos e do ano atual. |
| **Meta 4A/B** | Indicadores de produtividade específicos por grupo. |

