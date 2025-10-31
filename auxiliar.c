#include "wrdmttns.h"

/*****************************************************************
 * val_arguments()
 * 
 * Argumentos: argc
 *             argv
 * Return: void
 * 
 * Descrição:  Verifica se a função foi chamada da maneira correta,
 *             caso não tenha sido, o programa termina com exit(0)
*****************************************************************/
void val_arguments(int argc, char *argv[]){

   char *dict, *pals;
   char dot = '.';
   char *aux0 = ".dict";
   char *aux1 = ".pals";


   if (argc != 3) 
   {
      exit(0);
   }
   

   dict = strrchr(argv[1], dot);
   pals = strrchr(argv[2], dot);

   if(dict == NULL || pals == NULL)
   {
      /*Nao tem ponto*/
      exit(0);
   }

   if(strcmp(dict, aux0) != 0 || strcmp(pals, aux1) != 0)
   {
      /*"Um não respeita a condicao .dict /.pals"*/
      exit(0);
   }

   /*"Validacao com sucesso!*/

   return;
}



/************************************************************
 * iniciaVetor()
 * 
 * Argumentos: vetor: ponteiro para um vetor de inteiros
 * Return: void
 * 
 * Descrição:  Inicia todas as posicões de um vetor de inteiros
 *             a zero
**************************************************************/
void iniciaVetor(int *vetor, int max){
    int i;
    for(i = 0; i < max; i++){
        vetor[i] = 0;
    }
}


/**************************************************************
 * nr_permuta()
 * 
 * Argumentos: *pal1 - ponteiro para a palavra 1
 *             *pal2 - ponteiro para a palavra 2
 * 
 * Return: Nº de permutações 
 * 
 * Descrição:  Percorre uma palavra e compara com a outra vendo quantos 
 *             caracteres é que são diferentes
 * ***********************************************************/
int nr_permuta(char* pal1, char* pal2){
   int i;
   int nr_permuta = 0;

   for(i=0; i < strlen(pal1); i++){
      if(pal1[i] != pal2[i])
         nr_permuta++;

   }

   return nr_permuta; 
}

/**************************************************************
 * _permuta()
 * 
 * Argumentos: *pal1 - ponteiro para a palavra 1
 *             *pal2 - ponteiro para a palavra 2
 *             permuta_max - nº máximo de caracteres que podem ser diferentes
 * 
 * Return: Nº de permutações 
 * 
 * Descrição:  Percorre uma palavra e compara com a outra vendo quantos 
 *             caracteres é que são diferentes, caso atinja a permuta_max acaba a função
 * ***********************************************************/
int _permuta(char *pal1, char *pal2, int permuta_max){
   int nr_permuta = 0;

   while(*pal1 != '\0' ){
      if(*pal1 != *pal2){
         nr_permuta++;
      
         if(nr_permuta > permuta_max)
            return nr_permuta;
      }
      
      pal1++;
      pal2++;
   }

   return nr_permuta;
}


/*****************************************************************
 *  *iniciaVetores_pals()
 * 
 * Argumentos: *info - ponteiro para a estrutura vetores_pals
 * 
 * Return: ponteiro da estrutura vetores_pals
 * 
 * 
 * Descrição:  Inicializa e aloca a memória necessária para a estrutura vetores_pals
**********************************************************************/
vetores_pals *iniciaVetores_pals(){
   vetores_pals *info;
   
   info = (vetores_pals *) malloc(sizeof(vetores_pals));
   if(info == NULL)
      exit(0);

   iniciaVetor(info->criar_dic, MAX_SIZE);
   iniciaVetor(info->criar_grafo, MAX_SIZE);

   info -> fpals = NULL;
   info -> tamanho_maximo = 0;

   return info;
}

/************************************************
 * free_vetores_pals()
 * 
 * Argumentos: *info - ponteiro para a estrutura info
 * 
 * Return:
 * 
 * Descrição: Liberta a memória alocada para a estrutura info 
********************************************************/
void free_vetores_pals(vetores_pals *info){
   free(info);
}



/**********************************************************
 * vetor_st()
 *
 * Argumentos: grafo *G - ponteiro para estrutura grafo
 *
 * Return: ponteiro st
 *
 * Descrição: Aloca o espaço necessário para o vetor st
**********************************************************/
int *vetor_st(grafo *G){
   int *st = (int *) malloc(sizeof(int) * (G->V));
   if(st == NULL)
      exit(0);

   return st;
}



/**********************************************************
 * vetor_wt()
 *
 * Argumentos: grafo *G - ponteiro para estrutura grafo
 *
 * Return: ponteiro wt
 *
 * Descrição: Aloca o espaço necessário para o vetor wt
**********************************************************/
int *vetor_wt(grafo *G){
   int *wt = (int *) malloc(sizeof(int) * (G -> V));
   if(wt == NULL)
      exit(0);

   return wt;
}



/************************************************
 * free_st_e_wt()
 * 
 * Argumentos: *st - ponteiro para o vetor st
 *             *wt - ponteiro para o vetor wt
 * 
 * Return:
 * 
 * Descrição: Liberta a memória alocada para os vetores st e wt
********************************************************/
void free_st_e_wt(int *st, int *wt){
   free(st);
   free(wt);

   return;
}

