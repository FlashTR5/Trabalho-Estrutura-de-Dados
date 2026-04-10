#ifndef LISTA_H
#define LISTA_H

//struct das funçoes presentes nos arquivos csv
typedef struct
{
    char sigla_tribunal[10];
    char procedimento[50];
    char ramo_justica[50];
    char sigla_gr[10];
    char uf_oj[10];
    char municipio_oj[40];
    int id_ultim_oj;
    char nome[50];
    char mesano_cnm1[50];
    char mesano_sent[40];
    int casos_novos_2026;
    int julgados_2026;
    int prim_sent2026;
    int suspensos_2026;
    int dessobrestados_2026;
    int cumprimento_meta1;
    int distm2_a;
    int julgm2_a;
    int suspm2_a;
    int cumprimento_meta2a;
    int distm2_ant;
    int julgm2_ant;
    int suspm2_ant;
    int desom2_ant;
    int cumprimento_meta2ant;
    int distm4_a;
    int julgm4_a;
    int suspm4_a;
    int cumprimento_meta4a;
    int distm4_b;
    int julgm4_b;
    int suspm4_b;
    int cumprimento_meta4b;

}Registro;

typedef struct no {
    Registro dado;
    struct no *proximo; 

} No;

typedef struct lista {
    No *inicio;
    int tamanho;
} Lista;


void inicializarlista(Lista* l);


#endif