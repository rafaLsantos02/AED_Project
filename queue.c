#include "wrdmttns.h"

static int *queue; /*fila prioritaria que vai receber os indices das palavras, ou seja, um vertice*/
static int *pos_queue; /*posição de um vertice na fila prioritaria*/
static int fre; /*primeira posição vazia da fila*/
static int hsize; /*tamanho da fila prioritaria*/


/*******************************************************************
 * PQinit()
 * 
 * Argumentos: Size - tamanho da fila prioritaria
 * 
 * Return: 
 * 
 * Descrição:  Aloca o espaço necessário para a fila prioritária 
*********************************************************************/
void PQinit(unsigned int Size){
    queue = (int *) malloc(sizeof(int) * Size);
    if(queue == NULL){
        exit(0); /*Verificação se a memória foi bem alocada*/
    }

    pos_queue = (int *) malloc(sizeof(int) * Size);
    if(pos_queue == NULL){
        exit(0); /*Verificação se a memória foi bem alocada*/
    }

    /*Depois experimentar omitir esta inicialização do pos_queue*/
    for(int i = 0; i < Size; i++){
        pos_queue[i] = -1;
    }

    fre = 0;
    hsize = Size;

    return;
}


/********************************************************************
 * PQinsert()
 * 
 * Argumentos: I - indice da palavra 
 *             *wt - ponteiro para o vetor de custos
 * 
 * Return;
 * 
 * Descrição: Insere novo elemento no fim da fila e restabelece ordenação 
 *            com FixUp
***********************************************************************/
void PQinsert(int I, int *wt){

    if((fre) <= hsize){

        queue[fre] = I;
        pos_queue[I] = fre;

        FixUp( I, wt);
        
        fre++;
    }
}


/****************************************************************
 * PQempty()
 * 
 * Argumentos:
 * 
 * Return: 1 se a fila tiver vazia, 0 se não
 * 
 * Argumentos: Verifica se existem elementos na fila
 * ****************************************************************/
int PQempty(){
    if(fre == 0){
        return 1;
    }
    else return 0;
}



/****************************************************************************
 * PQdelmin()
 * 
 * Argumentos: *wt - ponteiro para o vetor de custos
 * 
 * Return: Elemento com maior prioridade, neste caso, o elemento com menor custo
 * 
 * Descrição: Retira o primeiro elemento da fila, que corresponde ao de menor custo
*****************************************************************************/
int PQdelmin( int *wt){

    troca(&pos_queue[ (queue[0]) ], &pos_queue[ (queue[fre-1]) ] );
    troca(&queue[0], &queue[fre-1]);

    FixDown( queue[0], (fre-2) , wt);

    pos_queue[ queue[fre-1] ] = -1;

    return queue[--fre];

}



/************************************************************************
 * FixUp()
 * 
 * Argumentos: I - indice da palavra a mudar ou nao
 *             *wt - ponteiro para o vetor de custos
 * 
 * Retunr:
 * 
 * Descrição: Se a prioridade de um nó for aumentada, enquanto não for restabelecida a condição de acervo 
 *            ou atingida a raiz, trocar com o nó ascendente
******************************************************************************/
void FixUp(int I, int *wt){

    int aux;

    while( (pos_queue[I] > 0) && lessPriA( wt[ queue[ (pos_queue[I] -1 )/2 ]], wt[I] ) ){
 
        aux = queue[( pos_queue[I] - 1) /2];
        
        troca(&queue[ pos_queue[I] ], &queue[ (pos_queue[I] - 1) /2] );
        troca(&pos_queue[I], &pos_queue[aux]);

    }

}


/***************************************************************************************
 * FixDown()
 * 
 * Argumentos: I - Indice da palavra no dicionário
 *             Size - tamanho do "acervo" num dado instante
 *             *wt - ponteiro para o vetor de custos
 * 
 * Return:
 * 
 * Descrição: Se prioridade de um nó for diminuida, enquanto não restabelecer a condição de acervo 
 *            ou atingir uma folha, troca com o maior descendente
*****************************************************************************************/
void FixDown(int I, int Size, int *wt){

    int child, aux;
   
    while( ( 2 * pos_queue[I] ) < (Size) ){

        child = (2 * pos_queue[I] ) + 1 ;

        if(child < (Size) && lessPriA( wt[queue[child]], wt[queue[child+1]] ))
            child ++;

        if(!lessPriA( wt[I], wt[queue[child]] ))
            break;

        aux = queue[child];
        troca( &queue[ pos_queue[I] ] , &queue[child]);
        troca(&pos_queue[I], &pos_queue[ aux ]);

    }

    return;
}
   

  

/***************************************************************************************
 * FixDown()
 * 
 * Argumentos: wt - ponteiro para o vetor de custos
 *             indice - indice da palavra a comparar (que alterou a sua prioridade)
 * 
 * Return:
 * 
 * Descrição: Reorganiza  a prioridade do acervo/fila prioritária
*****************************************************************************************/
void modify(int *wt, int I){

    int posicao = pos_queue[I];


    if(posicao != 0){
            
        if( lessPri( wt[ I ], wt[ queue[ (posicao-1)/2 ] ] ) == -1 ){
            FixUp(I, wt);

        }else if( lessPri( wt[ I ], wt[ queue[ (posicao-1)/2 ] ] ) == 1 ){
            FixDown(I, fre-1 , wt);
        }
        return;
    }
    else{
        FixDown(I, fre-1, wt);
    }    
    return;
}


/****************************************************************
 * lessPri()
 * 
 * Argumentos: a - valor 1
 *             b - valor 2
 * 
 * Return: 1 caso a for maior que o b, se não 0
 * 
 * Descrição: Compara dois valores
*****************************************************************/
int lessPri(int a, int b){

    if(a > b){
        return 1;
    }
    else if( a == b) 
        return 0;
    else
        return -1;

}



/****************************************************************
 * lessPriA()
 * 
 * Argumentos: a - valor 1
 *             b - valor 2
 * 
 * Return: 1 caso a for maior que o b, se não 0
 * 
 * Descrição: Compara dois valores
*****************************************************************/
int lessPriA(int a, int b){

    if(a > b){
        return 1;
    }
    else 
        return 0;
    

}


/***********************************************************************
 * PQfree()
 * 
 * Argumentos: 
 * 
 * Return:
 * 
 * Descrição: Liberta a memória alocada para o vetor queue e pos_queue
*************************************************************************/
void PQfree(){
    free(queue);
    free(pos_queue);
}


/***********************************************************************
 * troca()
 * 
 * Argumentos: a - valor 1 
 *             b - valor 2
 * 
 * Return:
 * 
 * Descrição: Troca o valor de dois inteiros num vetor
*************************************************************************/
void troca(int *a, int *b){

    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

}

/***********************************************************************
 * ta_fila()
 * 
 * Argumentos: indice - indice da palavra a verificar
 * 
 * Return: 0 - se não está na fila
 *         1 - se está na fila
 * 
 * Descrição: Vê se uma palavra está na fila
*************************************************************************/
int ta_fila(int indice){

    if(pos_queue[indice] == -1){
        return 0;
    }else
        return 1;
}


/***********************************************************************
 * PQgetElement()
 * 
 * Argumentos: 
 * 
 * Return: queue[0] - indíce da palavra na posição 0 da fila prioritaria
 * 
 * Descrição: Dá retorno ao indíce da palavra na posição 0 da fila prioritaria
*************************************************************************/
int PQgetElemment(){

    return queue[0];
}