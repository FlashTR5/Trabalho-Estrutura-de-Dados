#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lista.h"

void lerString(char *destino){
    //vai ate a virgula ou aspas
    char *token = strtok(NULL, ",\"\r\n");
    if(token != NULL){
        while(*token == ' ') token++; // Remove espaços em branco no início
        strcpy(destino, token);

        int len = strlen(destino);
        // Remove espaços em branco no final se tiver
        while(len > 0 && destino[len - 1] == ' '){
            destino[len - 1] = '\0';
            len--;
        }
    } else {
        destino[0] = '\0'; // Atribui string vazia se não houver token
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInt(){
    char *token = strtok(NULL, ",\"\r\n");
    
    if(token != NULL){
        return atoi(token);
    } 
    
    return 0;
}

void carregarArquivo(Lista *l, char *nomeArquivo){
    FILE *file = fopen(nomeArquivo, "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", nomeArquivo);
        return;
    }

    char linha[2048];
    fgets(linha, sizeof(linha), file); //Ignorar a primeira linha

    while(fgets(linha, sizeof(linha), file)){
        Registro novoDado;

        char *primeiro_token = strtok(linha, ",\"\r\n");

        if(primeiro_token == NULL) continue;
        strcpy(novoDado.sigla_tribunal, primeiro_token);

        lerString(novoDado.procedimento);
        lerString(novoDado.ramo_justica);
        lerString(novoDado.sigla_gr);
        lerString(novoDado.uf_oj);
        lerString(novoDado.municipio_oj);

        novoDado.id_ultimo_oj = lerInt();

        lerString(novoDado.nome);
        lerString(novoDado.mesano_cnm1);
        lerString(novoDado.mesano_sent);

        novoDado.casos_novos_2026 = lerInt();
        novoDado.julgados_2026 = lerInt();
        novoDado.prim_sent2026 = lerInt();
        novoDado.suspensos_2026 = lerInt();
        novoDado.dessobrestados_2026 = lerInt();
        novoDado.cumprimento_meta1 = lerInt();
        novoDado.distm2_a = lerInt();
        novoDado.julgm2_a = lerInt();
        novoDado.suspm2_a = lerInt();
        novoDado.cumprimento_meta2a = lerInt();
        novoDado.distm2_ant = lerInt();
        novoDado.julgm2_ant = lerInt();
        novoDado.suspm2_ant = lerInt();
        novoDado.desom2_ant = lerInt();
        novoDado.cumprimento_meta2ant = lerInt();
        novoDado.distm4_a = lerInt();
        novoDado.julgm4_a = lerInt();
        novoDado.suspm4_a = lerInt();
        novoDado.cumprimento_meta4a = lerInt();
        novoDado.distm4_b = lerInt();
        novoDado.julgm4_b = lerInt();
        novoDado.suspm4_b = lerInt();
        novoDado.cumprimento_meta4b = lerInt();

        inserirNoFim(l, novoDado);
    }

    fclose(file);
}

void gerarArquivoConcatenado(Lista *l, char *nomeSaida){
    FILE *file = fopen (nomeSaida, "w");
    if(file == NULL){
        printf("Erro ao criar o arquivo: %s\n", nomeSaida);
        return;
    }

    //gravar o cabeçalho primeiro 
    fprintf(file, "sigla_tribunal;procedimento;ramo_justica;sigla_gr;uf_oj;municipio_oj;id_ultimo_oj;nome;mesano_cnm1;mesano_sent;casos_novos_2026;julgados_2026;prim_sent2026;suspensos_2026;dessobrestados_2026;cumprimento_meta1;distm2_a;julgm2_a;suspm2_a;cumprimento_meta2a;distm2_ant;julgm2_ant;suspm2_ant;desom2_ant;cumprimento_meta2ant;distm4_a;julgm4_a;suspm4_a;cumprimento_meta4a;distm4_b;julgm4_b;suspm4_b;cumprimento_meta4b\n");

    No *atual = l->inicio;

    while (atual != NULL){
        Registro d = atual -> dado;

        fprintf(file, "%s;%s;%s;%s;%s;%s;%d;%s;%s;%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
                d.sigla_tribunal, d.procedimento, d.ramo_justica, d.sigla_gr, d.uf_oj, d.municipio_oj,
                d.id_ultimo_oj, d.nome, d.mesano_cnm1, d.mesano_sent, d.casos_novos_2026, d.julgados_2026,
                d.prim_sent2026, d.suspensos_2026, d.dessobrestados_2026, d.cumprimento_meta1, d.distm2_a,
                d.julgm2_a, d.suspm2_a, d.cumprimento_meta2a, d.distm2_ant, d.julgm2_ant, d.suspm2_ant,
                d.desom2_ant, d.cumprimento_meta2ant, d.distm4_a, d.julgm4_a, d.suspm4_a, d.cumprimento_meta4a,
                d.distm4_b, d.julgm4_b, d.suspm4_b, d.cumprimento_meta4b);
                
        atual = atual->proximo;
    }

    fclose(file);
    printf("Arquivo %s gerado com sucesso!\n", nomeSaida);
}

void filtrarMunicipio(Lista *l){
    system("cls");
    char busca[35];
    char nomeArquivo[50];
    

    printf("----- Gerar resumo de um municipio -----\n");
    printf("Digite o nome do municipio que deseja filtrar: ");
    scanf(" %[^\n]", busca); //pra ler string com espaços
    limparBuffer();

    for(int i = 0; busca[i]; i++){
        busca[i] = toupper(busca[i]);   
    }

    //nome do arquivo
    sprintf(nomeArquivo, "resumo_%s.csv", busca);

    FILE *file = fopen(nomeArquivo, "w");
    if(file == NULL){
        printf("Erro ao criar o arquivo %s!\n", nomeArquivo);
        system("pause");
        return;
    }

    //cabeçalho do arquivo de resumo
    fprintf(file, "municipio_oj,sigla_tribunal,procedimento,ramo_justica,sigla_gr,uf_oj,id_ultimo_oj,nome,mesano_cnm1,mesano_sent,casos_novos_2026,julgados_2026,prim_sent2026,suspensos_2026,dessobrestados_2026,cumprimento_meta1,distm2_a,julgm2_a,suspm2_a,cumprimento_meta2a,distm2_ant,julgm2_ant,suspm2_ant,desom2_ant,cumprimento_meta2ant,distm4_a,julgm4_a,suspm4_a,cumprimento_meta4a,distm4_b,julgm4_b,suspm4_b,cumprimento_meta4b\n");

    int encontrado = 0;
    No *atual = l->inicio;

    while(atual != NULL){
        if(strcmp(atual->dado.municipio_oj, busca) == 0){
            Registro d = atual->dado;
            fprintf(file, "%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    d.municipio_oj, d.sigla_tribunal, d.procedimento, d.ramo_justica, d.sigla_gr, d.uf_oj, 
                    d.id_ultimo_oj, d.nome, d.mesano_cnm1, d.mesano_sent, d.casos_novos_2026, d.julgados_2026,
                    d.prim_sent2026, d.suspensos_2026, d.dessobrestados_2026, d.cumprimento_meta1, d.distm2_a,
                    d.julgm2_a, d.suspm2_a, d.cumprimento_meta2a, d.distm2_ant, d.julgm2_ant, d.suspm2_ant,
                    d.desom2_ant, d.cumprimento_meta2ant, d.distm4_a, d.julgm4_a, d.suspm4_a, d.cumprimento_meta4a,
                    d.distm4_b, d.julgm4_b, d.suspm4_b, d.cumprimento_meta4b);
            encontrado++;
        }
        atual = atual->proximo;
    }

    fclose(file);

    if(encontrado > 0){
        printf("Arquivo %s gerado com sucesso! %d registros encontrados.\n", nomeArquivo, encontrado);
        system("pause");
    } else {
        printf("Nenhum registro encontrado para o municipio: %s\n", busca);
        system("pause");
        remove(nomeArquivo); // Remove o arquivo vazio
    }

}

void Meta1(Lista *l, char *nomeSaida){
    FILE *file = fopen (nomeSaida, "w");
    if (file == NULL){
        printf("Erro ao criar o arquivo: %s\n", nomeSaida);
        return;
    }

    fprintf(file, "sigla_tribunal;Meta1\n");

    printf("\n--- Resultados de Meta 1 ---\n");

    //Lista de todos os tribunais que foram carregados
    char *tribunais[] = {"TRE-AC", "TRE-AL", "TRE-AM", "TRE-AP", "TRE-BA", "TRE-CE", "TRE-DF", "TRE-ES", "TRE-GO", "TRE-MA", "TRE-MG", "TRE-MS", "TRE-MT", "TRE-PA", "TRE-PB", "TRE-PE", "TRE-PI", "TRE-PR", "TRE-RJ", "TRE-RN", "TRE-RO", "TRE-RR", "TRE-RS", "TRE-SC", "TRE-SE", "TRE-SP", "TRE-TO"};

    int num_tribunais = 27;

    for(int i = 0; i < num_tribunais; i++){
        int soma_julgados = 0, soma_casos_novos = 0, soma_dessobrestados = 0, soma_suspensos = 0;

        No *atual = l->inicio;

        //percorre a lista procurando dados do tribunal atual e soma os valores
        while(atual != NULL){
            if(strcmp(atual->dado.sigla_tribunal, tribunais[i]) == 0){
                soma_julgados += atual->dado.julgados_2026;
                soma_casos_novos += atual->dado.casos_novos_2026;
                soma_dessobrestados += atual->dado.dessobrestados_2026;
                soma_suspensos += atual->dado.suspensos_2026;
            }
            atual = atual->proximo;
        }

        //Faz o calculo do Meta1
        int denominador = soma_casos_novos + soma_dessobrestados - soma_suspensos;
        float meta1 = 0.0;

        if (denominador != 0){
            meta1 = ((float)soma_julgados / denominador) * 100;
        }

        printf("%s: %.2f%%\n", tribunais[i], meta1);
        fprintf(file, "%s;%.2f\n", tribunais[i], meta1);
    }

    fclose(file);
    printf("----------------------------------\n");
    printf("Arquivo %s gerado com sucesso!\n", nomeSaida);

}

void Meta2A(Lista *l, char *nomeSaida){
	FILE *file =fopen (nomeSaida, "w");
	if (file == NULL){
	printf("Erro ao criar o arquivo: %s\n", nomeSaida);
	return;
	}

	fprintf(file, "sigla tribunal;Meta2\n");

	printf("\n--- Resultados de Meta 2 ---\n");

	char *tribunais[] = {"TRE-AC", "TRE-AL", "TRE-AM", "TRE-AP", "TRE-BA", "TRE-CE", "TRE-DF", "TRE-ES", "TRE-GO", "TRE-MA", "TRE-MG", "TRE-MS", "TRE-MT", "TRE-PA", "TRE-PB", "TRE-PE", "TRE-PI", "TRE-PR", "TRE-RJ", "TRE-RN", "TRE-RO", "TRE-RR", "TRE-RS", "TRE-SC", "TRE-SE", "TRE-SP", "TRE-TO"};

    int num_tribunais = 27;

    for (int i = 0; i<num_tribunais; i++){
	int soma_julgm2_a = 0, soma_distm2_a = 0, soma_suspm2_a = 0;
	
	No *atual =l->inicio;

	while(atual != NULL){
	   if(strcmp(atual->dado.sigla_tribunal, tribunais[i]) == 0){
	      soma_julgm2_a += atual->dado.julgm2_a;
	      soma_distm2_a += atual->dado.distm2_a;
              soma_suspm2_a += atual->dado.suspm2_a;
	    }
        atual = atual->proximo;
    }

    int denominador = soma_distm2_a - soma_suspm2_a;
	float meta2 = 0.0;
	
	if (denominador != 0){
	    meta2 = ((float)soma_julgm2_a/denominador) * 1000/7;
	}

	printf("%s: %.2f%%\n", tribunais[i], meta2);
	fprintf(file, "%s;%.2f\n", tribunais[i], meta2);
	}

    fclose(file);
    printf("----------------------------------\n");
    printf("Arquivo %s gerado com sucesso!\n", nomeSaida);
}

void Meta4A(Lista *l, char *nomeSaida) {
    FILE *file = fopen(nomeSaida, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo: %s\n", nomeSaida);
        return;
    }

    // Cabeçalho
    fprintf(file, "sigla_tribunal;Meta4A\n");

    char *tribunais[] = {
        "TRE-AC","TRE-AL","TRE-AM","TRE-AP","TRE-BA","TRE-CE","TRE-DF","TRE-ES","TRE-GO","TRE-MA","TRE-MG","TRE-MS","TRE-MT","TRE-PA","TRE-PB","TRE-PE","TRE-PI","TRE-PR","TRE-RJ","TRE-RN","TRE-RO","TRE-RR","TRE-RS","TRE-SC","TRE-SE","TRE-SP","TRE-TO"
    };

    int num_tribunais = 27;

    for(int i = 0; i < num_tribunais; i++){
        int soma_julg = 0, soma_dist = 0, soma_susp = 0;

        No *atual = l->inicio;

        while(atual != NULL){
            if(strcmp(atual->dado.sigla_tribunal, tribunais[i]) == 0){
                soma_julg += atual->dado.julgm4_a;
                soma_dist += atual->dado.distm4_a;
                soma_susp += atual->dado.suspm4_a;
            }
            atual = atual->proximo;
        }

        int denominador = soma_dist + soma_susp;
        float meta4A = 0.0;

        if (denominador != 0){
            meta4A = ((float)soma_julg / denominador) * 100;
        }

        printf("%s: %.2f%%\n", tribunais[i], meta4A);
        fprintf(file, "%s;%.2f\n", tribunais[i], meta4A);
    }

    fclose(file);
    printf("Arquivo %s gerado com sucesso!\n", nomeSaida);
}

void Meta4B(Lista *l, char *nomeSaida) {
    FILE *file = fopen(nomeSaida, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo: %s\n", nomeSaida);
        return;
    }

    // Cabeçalho do CSV conforme o padrão do trabalho
    fprintf(file, "sigla tribunal;Meta4B\n");

    char *tribunais[] = {"TRE-AC", "TRE-AL", "TRE-AM", "TRE-AP", "TRE-BA", "TRE-CE", "TRE-DF", "TRE-ES", "TRE-GO", "TRE-MA", "TRE-MG", "TRE-MS", "TRE-MT", "TRE-PA", "TRE-PB", "TRE-PE", "TRE-PI", "TRE-PR", "TRE-RJ", "TRE-RN", "TRE-RO", "TRE-RR", "TRE-RS", "TRE-SC", "TRE-SE", "TRE-SP", "TRE-TO"};
    int num_tribunais = 27;

    for (int i = 0; i < num_tribunais; i++) {
        // Acumuladores específicos para a Meta 4B (campos 30, 31 e 32)
        int soma_julgm4_b = 0, soma_distm4_b = 0, soma_suspm4_b = 0;
        
        No *atual = l->inicio; // Declarado apenas uma vez aqui

        while (atual != NULL) {
            if (strcmp(atual->dado.sigla_tribunal, tribunais[i]) == 0) {
                soma_julgm4_b += atual->dado.julgm4_b; // Campo 31 [cite: 12]
                soma_distm4_b += atual->dado.distm4_b; // Campo 30 [cite: 12]
                soma_suspm4_b += atual->dado.suspm4_b; // Campo 32 [cite: 12]
            }
            atual = atual->proximo;
        }

        // Aplicando a fórmula do PDF: (Julgados / (Distribuídos - Suspensos)) * 100 [cite: 18]
        int denominador = soma_distm4_b - soma_suspm4_b;
        float meta4b_resultado = 0.0;

        if (denominador != 0) {
            meta4b_resultado = ((float)soma_julgm4_b / denominador) * 100;
        }
        printf("%s: %.2f%%\n", tribunais[i], meta4b_resultado);
        fprintf(file, "%s;%.2f\n", tribunais[i], meta4b_resultado);
    }


    fclose(file);
    printf("Arquivo %s gerado com sucesso!\n", nomeSaida);
}

int main() {

    Lista minhaLista;
    inicializarlista(&minhaLista);

    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-AC.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-AL.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-AM.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-AP.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-BA.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-CE.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-DF.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-ES.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-GO.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-MA.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-MG.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-MS.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-MT.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-PA.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-PB.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-PE.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-PI.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-PR.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-RJ.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-RN.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-RO.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-RR.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-RS.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-SC.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-SE.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-SP.csv");
    carregarArquivo(&minhaLista, "Base de Dados/teste_TRE-TO.csv");

    int opcao;

    do {
        system("cls");

        printf("\n----------Dados da Justica Federal----------\n");
        printf("1. Concatenar arquivo\n");
        printf("2. Calcular Meta1\n");
        printf("3. Calcular Meta2A\n");
        printf("4. Calcular Meta2Ant\n");
        printf("5. Calcular Meta4A\n");
        printf("6. Calcular Meta4B\n");  
        printf("7. Gerar resumo de um municipio\n");
        printf("8. Sair\n"); 
        printf("--------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        //Opções diferentes no menu só para testar as funções de calculo, trocar a mensagem de não implementada depois pela função real
        //depois colocar todo o resultado do resumo em um mesmo csv (Gabe: vou fazer isso quando vcs terminarem essas funções, para não ter que ficar editando o código toda hora)

        switch(opcao) {
            case 1:
                gerarArquivoConcatenado(&minhaLista, "base_concatenada.csv");
                printf("\n");
                system("pause");
                break;
            case 2:
                Meta1(&minhaLista, "resumo_meta1.csv");
                printf("\n");
                system("pause");
                break;
            case 3:
                Meta2A(&minhaLista, "resumo_meta2_a.csv");
                printf("\n");
                system("pause");
                break;
            case 4:
                printf("Funcao Meta2Ant ainda nao implementada!\n");
                break;  
            case 5:
                printf("Funcao Meta4A ainda nao implementada!\n");
                break;
            case 6:
                Meta4B(&minhaLista, "resumo_meta4b.csv"); 
                printf("\n");     
                system("pause");
                break;
            case 7:
                filtrarMunicipio(&minhaLista);
                break;
            case 8:
                liberarLista(&minhaLista);
                printf("Saindo...\n");
                exit(1);
            default:
                printf("Selecione uma opcao valida!\n");
                system("pause");
        }
    } while(opcao != 8);
    
    return 0;
}