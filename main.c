#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista.h"

int main() {

    Lista minhaLista;
    inicializarlista(&minhaLista); 

    int opcao;

    do {
        printf("\n----------Dados da Justica Federal----------\n");
        printf("1. Concatenar arquivo\n");
        printf("2. Gerar resumo\n");
        printf("3. Escolha de um municipio\n");
        printf("4. Sair\n"); 
        printf("--------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
            
        switch(opcao) {
            case 1:

                break;
            
            case 2:

                break;

            case 3:

                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Selecione uma opcao valida!\n"); 
        }
    } while(opcao != 4);
    
    return 0;
}