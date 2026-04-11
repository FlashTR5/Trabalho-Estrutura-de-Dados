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

