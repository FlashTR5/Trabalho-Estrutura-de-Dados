#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "lista.h"

//Inicializador da lista
void inicializarlista(Lista* l){
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;
}

void inserirNoFim(Lista* l, Registro dado){
    No *novo = (No*)malloc(sizeof(No));

    novo ->dado = dado;
    novo ->proximo = NULL;

    //se a lista for vazia o novo nó é o primeiro e o ultimo
    if(l->inicio == NULL){
        l->inicio = novo;
        l->fim = novo;
    } else {
        //percorre até achar o ultimo nó
        l->fim->proximo = novo;
        l->fim = novo;
    }

    l->tamanho++; 
}

void liberarLista(Lista* l) {
    No *atual = l->inicio;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;

    printf("Lista liberada com sucesso!\n");
}

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

int lerInt(){
    char *token = strtok(NULL, ",\"\r\n");
    
    if(token != NULL){
        return atoi(token);
    } 
    
    return 0;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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