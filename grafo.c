#include "wrdmttns.h"

/*******************************************************
 * novo()
 * 
 * Argumentos: V - indice da palavra no dicionario
 *             custo - variavel que indica o custo da ligação
 *             *next - ponteiro para o próxima ligação
 * 
 * Return:  A estrutura que guarda a aresta/ligação
 * 
 * Descrição:   Aloca a memória necessária para guardar a ligação
 *              de um vertice a outro
*********************************************************/
link *novo(int V, int custo, link *next){
    
    link *aux = (link *) malloc(sizeof(link));

    if(aux == NULL)
        exit(0); /*Erro na alocação de memoria*/

    aux -> V = V;
    aux -> custo = custo * custo;
    aux -> next = next;
    return aux;

}


/********************************************************
 * iniciaGrafo()
 * 
 * Argumentos: V - nº total de palavras do dicionario, ou seja, o número total de vertices
 *             tamanho - flag que indica que nesta estrutura está
 *                       um grafo para as palavras de tamanho x
 * 
 * Return: Retorna a estrutura do grafo
 * 
 * Descrição:   Aloca a memória necessária para a estrutura grafo   
***********************************************************/
grafo *iniciarGrafo(int V){

    int i;

    grafo *G = (grafo*) malloc(sizeof(grafo)); 
    if(G == NULL)
        exit(0); /*Erro na alocação de memoria*/
    
    G -> V = V;
    G -> lista_vertices = (link **) malloc(V * sizeof(link *));

    if(G -> lista_vertices == NULL)
        exit(0); /*Erro na alocação de memoria*/
    
    for(i = 0; i < V; i++){
        G -> lista_vertices[i] = NULL;
    }

    return G;
}


/*****************************************************
 * insereGrafo2()
 * 
 * Argumentos: *G - ponteiro para um grafo
 *             v1 - posição da palavra 1 no dicionario
 *             v2 - posição da palavra 2 no dicionario 
 *             custo - variavel que indica o custo da ligação
 * 
 * Return:
 * 
 * Descrição: Inserir no grafo as ligações
*/
void insereGrafo2(grafo *G, int v1, int v2, int custo){

    G -> lista_vertices[v1] = novo(v2, custo, G -> lista_vertices[v1]); /*Insiro sempre no inicio*/
    
}


/******************************************************
 * preencheGrafo2()
 * 
 * Argumentos: *aux - ponteiro para a estrutura dicionario correta
 *             *G - ponteiro para a estrutura grafo correta
 *             *criar_grafo - vetor que tem o numero maximo de permutações permitidas
 *             *size_palavra - vetor com o total de palavras do mesmo tamanho
 *             tamanho - tamanho das palavras no dicionário correto
 * 
 * Return: 
 * 
 * Descrição:   Cria/Preenche o grafo certo para o dicionário de um determinado tamamho.
 *              Nota: Apenas quero criar um grafo para cada tamanho de palavras
*********************************************************/
void preencheGrafo2(dicionario *aux, grafo *G, int v1, int permuta_max_todos){
    
    int i, permuta; 

    for(i = 0; i < G -> V; i++){
        if(i != v1){
            permuta = _permuta(aux -> dic[v1], aux ->dic[i], permuta_max_todos);

            if(permuta <= permuta_max_todos){
                insereGrafo2(G, v1, i, permuta);
            } 
        }
    }
}




/*************************************************************************
 * tabelaGrafos()
 * 
 * Argumentos: tamanho_maximo - tamanho maximo que é possível uma palavra ter
 * 
 * Return: Duplo pointer da estrutura grafo, ou seja, dá retorno a uma tabela de ponteiros de grafos
 * 
 * Descrição:   Alocar a memória necessária para a tabela de grafos
***************************************************************************/
grafo **tabelaGrafos(int tamanho_maximo){

    grafo **tabelaG = NULL;
    int i;

    /*Alocar a tabela de grafos, onde cada indice corresponde a um grafo para o tamanho de palavra n*/
    tabelaG = (grafo **) malloc(sizeof(grafo *) * (tamanho_maximo + 1)); 
    if(tabelaG == NULL)
        exit(0); /*Erro na alocação de memoria*/

    for(i = 0; i <= tamanho_maximo; i++){
        tabelaG[i] = NULL;
    }

    return tabelaG;

}

/*****************************************************************
 * void freeGarfo()
 * 
 * Argumentos: *G - ponteiro para um grafo
 * 
 * Return:
 * 
 * Descrição:   Liberta a memória alocada para o garfo e as suas ligações
********************************************************************/
void freeGrafo(grafo *G){
    int i;
    link *aux1 = NULL, *aux2 = NULL;

    if(G != NULL){
        for(i=0; i < G -> V; i++){
            for(aux1 = G -> lista_vertices[i]; aux1 != NULL; aux1 = aux2){
                aux2 = aux1 -> next;
                free(aux1);
            }
        }

        free(G -> lista_vertices);

        free(G);
    }
    
}


/*****************************************************************
 * void freeTabelaGarfo()
 * 
 * Argumentos: **tabelaGrafo - ponteiro para a tabela de grafos
 *             *criar_dic - vetor que tem a 1, os tamanhos de dicionarios que foram criados
 * 
 * Return:
 * 
 * Descrição:   Liberta a memória alocada para a tabela dos garfos 
********************************************************************/
void freeTabelaGrafo(grafo **tabelaGrafo, int *criar_dic){
    int i, j, tamanho_maximo = 0;

    for(i = 0; i < MAX_SIZE; i++){
        if(criar_dic[i] == 1)
            tamanho_maximo = i;
    }

    for(j = 0; j <= tamanho_maximo; j++){
        freeGrafo(tabelaGrafo[j]);
    }

    free(tabelaGrafo);
}