# Sistema de Manipulação de Dados da Justiça Eleitoral

Trabalho prático desenvolvido em Linguagem C para a disciplina de Estrutura de Dados da Universidade Católica de Brasília (UCB). O sistema realiza a leitura, manipulação e análise de dados jurisdicionais provenientes de arquivos CSV, aplicando conceitos avançados de alocação dinâmica, ponteiros e Estruturas de Dados.

## 1. Estrutura do Projeto
O código-fonte segue as boas práticas de modularização em C, dividindo a lógica de dados da lógica de interface. O projeto está estruturado em três arquivos principais:

* **`lista.h`**: Arquivo de cabeçalho (*Header*). Contém a definição da estrutura de dados principal (`struct Registro`), que armazena os 33 campos do CSV otimizados em tipos `char` e `int`. Também define a estrutura do `No`, a estrutura da `Lista` (com ponteiro para o início) e as assinaturas de todas as funções do TAD.
* **`lista.c`**: Arquivo de implementação do TAD. Contém a lógica estrutural da lista encadeada simples, incluindo as funções de inicialização, alocação de novos nós, inserção no final da estrutura e liberação da memória.
* **`main.c`**: Arquivo principal do programa. Gerencia a interface com o usuário via terminal (menu interativo), realiza a leitura e conversão (*parsing*) dos arquivos CSV e implementa as funções de regra de negócio exigidas pelos itens do trabalho (Concatenação, Resumo de Metas e Filtro por Município).

## 2. Como Compilar e Executar

Para compilar o projeto, abra o terminal na pasta raiz do projeto e execute o seguinte comando para compilar os múltiplos arquivos fonte em um único executável:

```bash
gcc main.c lista.c -o programa.exe
```

Após a compilação ser concluída sem erros, execute o programa gerado:
* No Windows:
```bash
.\programa.exe
```

**Atenção aos pré-requisitos de execução**: Para que o programa inicie corretamente, a pasta chamada `Base de Dados` (contendo os 27 arquivos `.csv` originais dos tribunais) deve estar localizada no mesmo diretório onde o arquivo executável for rodado.

## 3. Documentação das Funções
Abaixo está o detalhamento técnico de cada função implementada no escopo do projeto.

**3.1 Funções do TAD Lista (lista.c)**
* `inicializarLista(Lista *l)`: Recebe o ponteiro da lista e define o seu início como `NULL`. É o passo fundamental para evitar que a lista aponte para lixo de memória antes do carregamento dos dados.
  
* `inserirNoFim(Lista *l, Registro d)`: Recebe a lista e um dado do tipo `Registro`. Aloca dinamicamente um novo `No` usando a função `malloc()`. Se a lista estiver vazia, o novo nó se torna o início. Caso contrário, a função percorre a lista até o último elemento e faz o encadeamento. Essa abordagem garante a preservação da ordem original das linhas do CSV.
  
* `liberarLista(Lista *l)`: Função crítica para o gerenciamento de memória. É chamada antes do encerramento do programa para percorrer todos os nós da lista, aplicando o comando `free()` em cada um deles, evitando vazamento de memória (*memory leak*) após o uso de mais de 200 mil registros.

**3.2 Funções de Utilidade e Leitura (lista.c)**
* `limparBuffer()`: Função auxiliar de segurança que consome caracteres residuais do buffer do teclado, como o `\n` gerado pela tecla Enter. Impede que a função `scanf` pule entradas subsequentes durante a navegação do menu.
  
* `lerString(char *destino)` / `lerInt()`: Funções auxiliares criadas para trabalhar em conjunto com o `strtok`. Elas extraem os tokens isolados pelas vírgulas do CSV, removem espaços em branco acidentais e convertem os dados numéricos utilizando a função `atoi()`, garantindo a tipagem correta na struct.
  
* `carregarArquivo(Lista *l, char *nomeArquivo)`: Responsável por abrir o arquivo `.csv` em modo de leitura `("r")`, ignorar a primeira linha (cabeçalho) usando `fgets()`, e iterar sobre todas as linhas subsequentes. Cada linha é fatiada pelo delimitador `,`, convertida em um `Registro` e enviada para a função `inserirNoFim(Lista *l, Registro d)`.

**3.3 Funções dos Itens do Trabalho (main.c)**
* `gerarArquivoConcatenado(Lista *l, char *nomeSaida)`: (Resolve o Item 1). Abre um novo arquivo CSV em modo de escrita `("w")`, grava o cabeçalho padronizado e, em seguida, percorre toda a lista encadeada formatando e gravando todos os campos de cada registro em uma única linha.
  
* `resumoGeral(Lista *l, char *nomeSaida)`: (Resolve o Item 2). Gera um relatório estatístico consolidado por Tribunal (TRE-AC a TRE-TO). A função realiza uma única varredura por tribunal, acumulando simultaneamente as variáveis necessárias (casos novos, julgados, suspensos, etc.). Após o acúmulo, aplica as fórmulas matemáticas das Metas 1, 2A, 2Ant, 4A e 4B e exporta o resultado.
  
* `filtrarMunicipio(Lista *l)`: (Resolve o Item 3). Solicita ao usuário o nome de um município. O sistema utiliza a função nativa da biblioteca `string`, `stricmp`, para comparar a entrada com o campo `municipio_oj` de cada nó da lista. Todos os registros que apresentarem correspondência são exportados para um arquivo dinamicamente nomeado (ex: `resumo_MACAPA.csv`).

## 4. Detalhamento das Metas Matemáticas Calculadas
A função `resumoGeral` aplica as seguintes fórmulas estabelecidas para avaliação de desempenho do Judiciário, protegendo o sistema contra divisões por zero:

1. **Meta 1**: Avalia o número de processos julgados em relação aos distribuídos.
   * Fórmula: `(Julgados Totais / (Casos Novos + Dessobrestados - Suspensos)) * 100`
2. **Meta 2A**: Avalia processos antigos de fases específicas.
   * Fórmula: `(Julgados_M2A / (Distribuidos_M2A - Suspensos_M2A)) * (1000.0 / 7.0)`
3. **Meta 2Ant**: Avalia o passivo de anos anteriores.
   * Fórmula: `(Julgados_M2Ant / (Distribuidos_M2Ant - Suspensos_M2Ant - Dessobrestados_M2Ant)) * 100`
4. **Meta 4A**: Indicadores de produtividade de módulos específicos.
   * Fórmula: `(Julgados_M4a / (Distribuidos_M4a - Suspensos_M4a)) * 100`
5. **Meta 4B**: Indicadores de produtividade de módulos específicos.
   * Fórmula: `(Julgados_M4b / (Distribuidos_M4b - Suspensos_M4b)) * 100`
