#ifndef LISTA_H
#define LISTA_H

//struct das funçoes presentes nos arquivos csv
//Cuidado pra não gastar memoria guys
typedef struct
{
    char sigla_tribunal[10]; 
    char procedimento[35];   
    char ramo_justica[20];   
    char sigla_gr[6];        
    char uf_oj[5];           
    char municipio_oj[45];   
    int id_ultimo_oj;
    char nome[55];           
    char mesano_cnm1[12];    
    char mesano_sent[12];   
    
    // Campos inteiros (4 bytes cada)
    int casos_novos_2026, julgados_2026, prim_sent2026, suspensos_2026, dessobrestados_2026;
    int cumprimento_meta1, distm2_a, julgm2_a, suspm2_a, cumprimento_meta2a;
    int distm2_ant, julgm2_ant, suspm2_ant, desom2_ant, cumprimento_meta2ant;
    int distm4_a, julgm4_a, suspm4_a, cumprimento_meta4a;
    int distm4_b, julgm4_b, suspm4_b, cumprimento_meta4b;

}Registro;

typedef struct no {
    Registro dado;
    struct no *proximo; 
} No;

typedef struct lista {
    No *inicio;
    No *fim;
    int tamanho;
} Lista;


void inicializarlista(Lista* l);
void inserirNoFim(Lista* l, Registro dado);
void liberarLista(Lista* l);

void limparBuffer();
int lerInt();
void lerString(char *destino);

void carregarArquivo(Lista *l, char *nomeArquivo);

//pra conseguir ler os municipios com acentos;
void sanitizarString(const char *origem, char *destino);

#endif