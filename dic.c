#include "wrdmttns.h"

static int cmpstringp(const void *p1, const void *p2);


/**************************************************************************
 * read_fdict()
 * 
 * Argumentos: fdict: ponteiro para o ficheiro .dict
 *             size_palavra: vetor com o total de palavras do mesmo tamanho
 * Return: void
 * 
 * Descrição:  Lê o ficheiro .dict todo, de forma a contar o número 
 *             total de palavras de todos os tamanhos que existem
***************************************************************************/
void read_fdict(FILE *fdict, int *size_palavra){

   char palavra[MAX_SIZE];

   while( fscanf(fdict, "%s" , palavra ) != EOF ) {

      size_palavra[strlen(palavra)]++;

   }

   rewind(fdict);

   return;

}


/*********************************************************************
 * tabelaDicionario()
 * 
 * Argumentos: tamanho_maximo - tamanho maximo que é possível uma palavra ter
 * 
 * Return: tabelaD - ponteiro para o início da tabela de estruturas do tipo dicionário
 * 
 * Descrição: Aloca o espaço necessário para a criação da tabela de dicionarios 
**********************************************************************/
dicionario **tabelaDicionario(int tamanho_maximo){
    int i;
    dicionario **tabelaD = NULL;

    tabelaD = (dicionario **) malloc(sizeof(dicionario*) * (tamanho_maximo + 1));
    if(tabelaD == NULL){
        exit(0); /*Erro na alocação de mémoria*/
    }

    for(i = 0; i <= tamanho_maximo; i++){
        tabelaD[i] = NULL;
    }

    return tabelaD;

}

/***************************************************************
 * criaDic()
 * 
 * Argumentos: size_palavra - número de ocorrências de palavras de um 
 *             determinado tamanho do ficheiro.dict
 * 
 * Return: aux - ponteiro para um dicionário
 * 
 * Descrição: Aloca a memória necessária para a estrutura dicionário
*****************************************************************/
dicionario *criaDic(int size_palavra){
    
    dicionario *aux;

    aux = (dicionario *) malloc(sizeof(dicionario));
    if(aux == NULL)
        exit(0); /*Erro na alocação de memória*/

    aux -> dic = (char **) malloc(sizeof(char*) * size_palavra);
    if(aux -> dic == NULL)  
        exit(0);/*Erro na alocação de memória*/

    return aux;

}

/****************************************************************
 * void inserpalavra()
 * 
 * Argumentos:  fdict - ponteiro para o ficheiro .dict
 *              tamanho_maximo - tamanho maximo que é possível uma palavra ter
 *              tabelaD - ponteiro para a tabela de dicionarios
 *              count - ponteiro para vetor do numero de palavras introduzidas
 * Return: void
 * 
 * Descrição: Dá scan ao ficheiro .dict, escolhe a estrutura dicionario onde 
 *            a palavra irá ser inserida e chama a função colocarpalavra
*******************************************************************/
void inserpalavra (FILE *fdict, int tamanho_maximo, dicionario **tabelaD, int *count){

    char palavra[MAX_SIZE];
    int tamanho;

    while(fscanf(fdict, "%s", palavra) != EOF) {

        tamanho = strlen(palavra);
        
        if(tamanho <= tamanho_maximo){
            if(tabelaD[tamanho] != NULL)
                colocarpalavra(palavra, tamanho, tabelaD[tamanho], count);  
        }

    }

    return;
}



 /******************************************************************************
 * colocarpalavra ()
 *
 * Arguments: palavra - ponteiro para a palavra lida
 *            lista - ponteiro para o inicio da lista  
 *            count - ponteiro para vetor do numero de palavras introduzidas
 *            
 * Returns: retorna o ponteiro para a lista 
 * 
 * Description: Aloca a memoria necessária para cada palavra e insere-a na tabela
 *****************************************************************************/
void colocarpalavra(char *palavra, int tamanho, dicionario *aux, int *count){

    int count_size = count[tamanho];

    aux -> dic[count_size] = (char*) malloc(sizeof(char) * (tamanho + 1));

    if(aux -> dic[count_size] == NULL){
        exit(0);
    }

    strcpy(aux-> dic[count_size], palavra);
    count[tamanho]++;

    return;
}



/******************************************************************************
 * organizadicionario ()
 *
 * Arguments: head - ponteiro para o primeiro nó da lista
 *            size_palavra - ponteiro para vetor do numero de ocorrencias 
 *                   de palavras de cada tamanho
 *            
 * Returns: retorna o ponteiro para o primeiro nó da lista
 * 
 * Description: Realiza a organização do dicionario pela ordem alfabética,
 *              recorrendo à função qsort.
 *****************************************************************************/
void organizadicionario (dicionario** tabelaD, int *size_palavra, int tamanho_maximo){

    int i;

    for(i = 0; i <= tamanho_maximo; i++){
        if(tabelaD[i] != NULL)
            qsort(tabelaD[i] -> dic, size_palavra[i], sizeof(char*), cmpstringp);
    }
    
    return;
}


/******************************************************************************
 * static int cmpstringp()
 *
 * Arguments: palavra1 - ponteiro para uma string 1 
 *            palavra2 - ponteiro para uma string 2
 *            
 * Returns: retorna o valor da função strcmp entre as duas palavras
 * 
 * Description: 
 *     Função complementar ao qsort
 * 
 *****************************************************************************/
static int cmpstringp(const void *palavra_1, const void *palavra_2) {

    return strcmp(* (char * const* ) palavra_1, *(char * const *) palavra_2);

}



/******************************************************************************
 * binarySearch ()
 *
 * Arguments: lista_palavras - duplo ponteiro para lista de palavras
 *            tamanho_lista - numero de elementos em cada lista
 *            palavra_localizar - ponteiro para a palavra que se pretende encontrar
 *            
 * Returns: int - retorna -1 se não encontrar a palavra, ou a posição onde se 
 *                encontra a palavra
 * 
 * Description: 
 *     Realiza a procura da posição de uma palavra numa tabela onde
 *     se encontram todas as palavras do mesmo tamanho da procurada
 *     Nota: Função retirada do forum TutorialRide.com
 * 
 *****************************************************************************/
int binarySearch(char **lista_palavras, int tamanho_lista, char *palavra_localizar){

    int bot = 0;
    int mid;
    int top = tamanho_lista - 1;

    while(bot <= top){
        mid = (bot + top)/2;
        if (strcmp(lista_palavras[mid], palavra_localizar) == 0){
            return mid;
        }
        if (strcmp(lista_palavras[mid], palavra_localizar) > 0){
            top = mid - 1;
        }
        if ((strcmp(lista_palavras[mid], palavra_localizar)) < 0){
            bot = mid + 1;
        }
    }
    return -1;
}



/*****************************************************
 * freeDic()
 * 
 * Argumentos: aux - ponteiro para um dicionario
 *             count - nº de palavras num dicionário em específico
 * 
 * Return:
 * 
 * Argumentos: Liberta a memória usada na criação dos dicionários, nomeadamente
 *             a mémoria usada no interior da estrutura dicionário
*********************************************************/
void freeDic(dicionario *aux, int count){
    int i;

    for(i = 0; i < count; i++){
        free(aux -> dic[i]);
    }

    free(aux -> dic);
    free(aux);

    return;
}

/*****************************************************
 * freeTabelaD()
 * 
 * Argumentos: tabelaD - ponteiro para a tabela de dicionários
 *             tamanho_maximo - tamanho maximo que é possível uma palavra ter
 *             count - ponteiro para vetor do numero de palavras introduzidas
 * 
 * Return:
 * 
 * Argumentos: Liberta a memória usada na criação dos dicionários, nomeadamente
 *             a mémoria alocada para a tabela de estruturas do tipo dicionário
*********************************************************/
void freeTabelaD(dicionario **tabelaD, int tamanho_maximo, int *count){
    int i;

    for(i = 0; i <= tamanho_maximo; i++){
        if(tabelaD[i] != NULL){
            freeDic(tabelaD[i], count[i]);
        }
    }

    free(tabelaD);

    return;
    
}