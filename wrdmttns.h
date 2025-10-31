#ifndef HEADER_H_INCLUDED 
#define HEADER_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define custo_total (wt[v] + t -> custo)
#define maxWT 1000000
#define MAX_SIZE 70

typedef struct _dicionario{
    char** dic;
} dicionario;


typedef struct _vetores_pals{
    int criar_dic[MAX_SIZE];
    int tamanho_maximo;
    int criar_grafo[MAX_SIZE];
    FILE* fpals;
} vetores_pals;


typedef struct _link{
    int V;
    int custo;
    struct _link *next;
} link;


typedef struct _grafo{
    int V; /*Número total de vertices*/
    struct _link **lista_vertices;
} grafo;



/*Declarações das funções do ficheiro dic.c*/
void read_fdict(FILE *fdict, int *size_palavra);
dicionario **tabelaDicionario(int tamanho_maximo);
dicionario *criaDic(int size_palavra);
void inserpalavra (FILE *fdict, int tamanho_maximo, dicionario **tabelaD, int *count);
void colocarpalavra(char *palavra, int size, dicionario *aux, int *count);
void organizadicionario(dicionario** tabelaD, int *size_palavra, int tamanho_maximo);
int binarySearch(char **lista_palavras, int tamanho_lista, char *palavra_localizar);
void freeDic(dicionario *aux, int count);
void freeTabelaD(dicionario **tabelaD, int tamanho_maximo, int *count);



/*Declarações das funções do ficheiro stats.c*/
vetores_pals *le_pals(char *argv[], FILE *fdict);
void verifica_criar_grafos(vetores_pals *info, dicionario **tabelaD, int *size_palavra);
void resolve_pals(vetores_pals *info, FILE *fsaida, dicionario **tabelaD, grafo **tabelaG, int *size_palavra);
void escreveFicheiro(char *argv[], vetores_pals *info, dicionario **tabelaD, grafo **tabelaG, int *size_palavra);



/*Declarações das funções do ficheiro auxiliar.c*/
void val_arguments(int argc, char *argv[]);
void iniciaVetor(int *vetor, int tamanho_max);
int nr_permuta(char* pal1, char* pal2);
int _permuta(char *pal1, char *pal2, int tamanho_max);
vetores_pals *iniciaVetores_pals();
void free_vetores_pals(vetores_pals *info);
int *vetor_st(grafo *G);
int *vetor_wt(grafo *G);
void free_st_e_wt(int *st, int *wt);



/*Declarações das funções do ficheiro grafo.c*/
link *novo(int V, int custo, link *next);
grafo *iniciarGrafo(int V);
void insereGrafo2(grafo *G, int v1, int v2, int custo);
void preencheGrafo2(dicionario *aux, grafo *G, int v1, int permuta_max_todos);
grafo **tabelaGrafos(int tamanho_maximo);
void freeGrafo(grafo *G);
void freeTabelaGrafo(grafo **tabelaGrafo, int *criar_dic);



/*Declaração das funções do ficheiro queue.c*/
void PQinit(unsigned int Size);
void PQinsert(int I, int *wt);
int PQempty();
int PQdelmin(int *wt);
void FixUp(int I, int *wt);
void FixDown(int I, int Size, int *wt);
int lessPri(int a, int b);
int lessPriA(int a, int b);
void PQfree();
void troca(int *a, int *b);
void modify(int *wt, int indice);
int ta_fila(int indice);
int PQgetElemment();



/*Declarações das funções do ficheiro dijkstra.c*/
int dijkstra(dicionario *aux, grafo *G, int partida, int chegada, int permuta_max, int permuta_max_todos, int *st, int *wt);
void caminho(FILE *fsaida, dicionario *head, grafo *G, int partida, int chegada, int st[], int custo);


#endif













