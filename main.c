#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "lista.h"

void gerarArquivoConcatenado(Lista *l, char *nomeSaida){
    FILE *file = fopen (nomeSaida, "w");
    if(file == NULL){
        printf("Erro ao criar o arquivo: %s\n", nomeSaida);
        return;
    }

    //gravar o cabeçalho primeiro 
    fprintf(file, "sigla_tribunal,procedimento,ramo_justica,sigla_gr,uf_oj,municipio_oj,id_ultimo_oj,nome,mesano_cnm1,mesano_sent,casos_novos_2026,julgados_2026,prim_sent2026,suspensos_2026,dessobrestados_2026,cumprimento_meta1,distm2_a,julgm2_a,suspm2_a,cumprimento_meta2a,distm2_ant,julgm2_ant,suspm2_ant,desom2_ant,cumprimento_meta2ant,distm4_a,julgm4_a,suspm4_a,cumprimento_meta4a,distm4_b,julgm4_b,suspm4_b,cumprimento_meta4b\n");

    No *atual = l->inicio;

    while (atual != NULL){
        Registro d = atual -> dado;

        fprintf(file, "%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
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

void resumoGeral(Lista *l, char *nomeSaida){
    system("cls");
    FILE *file = fopen(nomeSaida, "w");
    if(file == NULL){
        printf("Erro ao criar o arquivo de resumo!\n");
        return;
    }

    //cabeçalho do arquivo de resumo
    fprintf(file, "sigla_tribual,total_julgados,Meta1,Meta2A,Meta2Ant,Meta4A,Meta4B\n");

    printf("-------------------------------RESUMO GERAL-------------------------------\n");
    printf("Tribunal        |Julgados  |Meta1    |Meta2A   |Meta2Ant |Meta4A   |Meta4B\n");
    printf("--------------------------------------------------------------------------\n");

    char *tribunais[] = {"TRE-AC", "TRE-AL", "TRE-AM", "TRE-AP", "TRE-BA", "TRE-CE", "TRE-DF", "TRE-ES", "TRE-GO", "TRE-MA", "TRE-MG", "TRE-MS", "TRE-MT", "TRE-PA", "TRE-PB", "TRE-PE", "TRE-PI", "TRE-PR", "TRE-RJ", "TRE-RN", "TRE-RO", "TRE-RR", "TRE-RS", "TRE-SC", "TRE-SE", "TRE-SP", "TRE-TO"};
    int num_tribunais = 27;

    for(int i = 0; i < num_tribunais; i++){
        int julgados_total = 0, c_novos = 0, dessob = 0, susp = 0;
        int julg2a = 0, dist2a = 0, susp2a = 0;
        int julg2ant = 0, dist2ant = 0, susp2ant = 0, deso2ant = 0;
        int julg4a = 0, dist4a = 0, susp4a = 0;
        int julg4b = 0, dist4b = 0, susp4b = 0;

        No *atual = l->inicio;
        while(atual != NULL){
            if(strcmp(atual->dado.sigla_tribunal, tribunais[i]) == 0){
                Registro d = atual->dado;
                julgados_total += d.julgados_2026;
                // Meta 1
                c_novos += d.casos_novos_2026; dessob += d.dessobrestados_2026; susp += d.suspensos_2026;
                // Meta 2A
                julg2a += d.julgm2_a; dist2a += d.distm2_a; susp2a += d.suspm2_a;
                // Meta 2Ant
                julg2ant += d.julgm2_ant; dist2ant += d.distm2_ant; susp2ant += d.suspm2_ant; deso2ant += d.desom2_ant;
                // Meta 4A
                julg4a += d.julgm4_a; dist4a += d.distm4_a; susp4a += d.suspm4_a;
                // Meta 4B
                julg4b += d.julgm4_b; dist4b += d.distm4_b; susp4b += d.suspm4_b;
            }
            atual = atual->proximo;
        }

        //Calculo Meta1
        int denominador_meta1 = c_novos + dessob - susp;
        float meta1 = 0.0;
        if(denominador_meta1 != 0){
            meta1 = (float)julgados_total/denominador_meta1 * 100;
        }

        //Calculo Meta2A
        int denominador_meta2a = dist2a - susp2a;
        float meta2a = 0.0;
        if(denominador_meta2a != 0){
            meta2a = (float) julg2a / denominador_meta2a * (1000.0/7.0);
        }

        //Calculo Meta2Ant
        int denominador_meta2ant = dist2ant - susp2ant - deso2ant;
        float meta2ant = 0.0;
        if(denominador_meta2ant != 0){
            meta2ant = (float) julg2ant / denominador_meta2ant * 100;
        }

        //Calculo Meta4A
        int denominador_meta4a = dist4a - susp4a;
        float meta4a = 0.0;
        if(denominador_meta4a != 0){
            meta4a = (float) julg4a / denominador_meta4a * 100;
        }

        //Calculo Meta4B
        int denominador_meta4b = dist4b - susp4b;
        float meta4b = 0.0;
        if(denominador_meta4b != 0){
            meta4b = (float) julg4b / denominador_meta4b * 100;
        }

        
        printf("%-15s | %-8d | %-6.2f%% | %-6.2f%% | %-6.2f%% | %-6.2f%% | %-6.2f%%\n", tribunais[i], julgados_total, meta1, meta2a, meta2ant, meta4a, meta4b);
        fprintf(file, "%s,%d,%.2f,%.2f,%.2f,%.2f,%.2f\n", tribunais[i], julgados_total, meta1, meta2a, meta2ant, meta4a, meta4b);

    }

    fclose(file);
    printf("Arquivo '%s' gerado com sucesso!\n", nomeSaida);    
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
        busca[i] = toupper((unsigned char)busca[i]);
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
    fprintf(file, "sigla_tribunal,procedimento,ramo_justica,sigla_gr,uf_oj,municipio_oj,id_ultimo_oj,nome,mesano_cnm1,mesano_sent,casos_novos_2026,julgados_2026,prim_sent2026,suspensos_2026,dessobrestados_2026,cumprimento_meta1,distm2_a,julgm2_a,suspm2_a,cumprimento_meta2a,distm2_ant,julgm2_ant,suspm2_ant,desom2_ant,cumprimento_meta2ant,distm4_a,julgm4_a,suspm4_a,cumprimento_meta4a,distm4_b,julgm4_b,suspm4_b,cumprimento_meta4b\n");

    int encontrado = 0;
    No *atual = l->inicio;

    while(atual != NULL){
        if(strcmp(atual->dado.municipio_oj, busca) == 0){
            Registro d = atual->dado;
            fprintf(file, "%s,%s,%s,%s,%s,%s,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                    d.sigla_tribunal, d.procedimento, d.ramo_justica, d.sigla_gr, d.uf_oj, d.municipio_oj,
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
    } else {
        printf("Nenhum registro encontrado para o municipio: %s\n", busca);
        remove(nomeArquivo); // Remove o arquivo vazio
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

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

        printf("\n----------SISTEMA DE DADOS DA JUSTICA FEDERAL----------\n");
        printf("1. Concatenar arquivo (Item 1)\n");
        printf("2. Gerar Resumo (Item 2)\n");
        printf("3. Filtrar por Municipio (Item 3)\n");
        printf("4. Sair\n"); 
        printf("-------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        if(scanf("%d", &opcao) != 1){
            opcao= -1; //Opção Invalida
        }
        limparBuffer(); 

        switch(opcao) {
            case 1:
                gerarArquivoConcatenado(&minhaLista, "base_concatenada.csv");
                printf("\n");
                system("pause");
                break;
            case 2:
                resumoGeral(&minhaLista, "resumo_geral.csv");
                printf("\n");
                system("pause");
                break;
            case 3:
                filtrarMunicipio(&minhaLista);
                printf("\n");
                system("pause");
                break;
            case 4:
                liberarLista(&minhaLista);
                printf("Saindo...\n");
                exit(1);
            default:
                printf("Selecione uma opcao valida!\n");
                system("pause");
        }
    } while(opcao != 4);
    
    return 0;
}