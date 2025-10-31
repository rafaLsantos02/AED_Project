#include "wrdmttns.h"


/*************************************************************************
 * dijkstra()
 * 
 * Argumentos: *aux - ponteiro para o dicionario 
 *             *G - ponteiro para o grafo
 *             partida - indice da palavra de partida no dicionario
 *             chegada - indice da palavra de chegada no dicionario
 *             permuta_max - número máximo de permuta permitido
 *             permuta_max_todos - permuta máxima permitida para a criação das arestas do grafo deste tamanho
 *             st[] - vetor onde vai ser criada a "arvore" com os caminhos de menor 
 *             custo 
 *             wt[] - vetor com os custos para se chegar a cada vertice
 * 
 * Return: return 1 se encontrar caminho, -1 se não encontrar
 * 
 * Descrição: Algoritmo que encontra o caminho com o menor custo entre duas palavras
 *            nota: Ligeira adaptação do algoritmo já conhecido Dijkstra
**************************************************************************/
int dijkstra(dicionario *aux, grafo *G, int partida, int chegada, int permuta_max, int permuta_max_todos, int *st, int *wt){

    int v, w;
    link *t;    

    PQinit(G->V);

    for(v = 0; v < G -> V; v++){
        st[v] = -1;
        wt[v] = maxWT;
    }

    
    wt[partida] = 0;
    PQinsert(partida, wt);
    
    while(!PQempty()){

        v = PQdelmin(wt); /*v= valor prioritario*/

        if(v == chegada){
            PQfree();
            return 1;
        }

        if( (t = G -> lista_vertices[v]) == NULL){
            preencheGrafo2(aux, G, v, permuta_max_todos);
        }

        for(t = G -> lista_vertices[v]; t != NULL; t = t -> next){

            w = t -> V; /* w= indice da palavra que está a comparar*/

            if( ( wt[w] > custo_total ) && ( t->custo <= (permuta_max*permuta_max) ) ){

                if( ta_fila(w)  == 0){

                    wt[w] = custo_total;
                    PQinsert(w, wt);
                    st[w] = v;

                }else{
                    
                    wt[w] = custo_total;
                    modify( wt, w);
                    st[w] = v;
                }
            }
        }
        
    }

    PQfree();


    return -1;

}


/*****************************************************************************
 * caminho()
 * 
 * Argumentos: *fsaida - ponteiro para o ficheiro de saida
 *             *lista - ponteiro para a lista com o dicionario de determinado tamanho
 *             *G - ponteiro para o grafo
 *             partida - indice da palavra de partida no dicionario
 *             chegada - indice da palavra de chegada no dicionario
 *             st[] - vetor onde está criada a "arvore" com os caminhos de menor custo 
 *             custo - custo total do caminho percorrida
 * Return:
 * 
 * Descrição: Vai imprimir o caminho entre duas palavras e o respetivo custo do mesmo
*******************************************************************************/
void caminho(FILE *fsaida, dicionario *lista, grafo *G, int partida, int chegada, int st[], int custo){


    if(st[chegada] != st[partida]){
        caminho(fsaida, lista, G, partida, st[chegada], st, custo);
    }
    else{
        fprintf(fsaida, "%s %d\n", lista -> dic[partida], custo);
        return;
    }    

    fprintf(fsaida, "%s\n", lista -> dic[chegada]);

    return;

}



