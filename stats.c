#include "wrdmttns.h"


/********************************************************
 * FILE *le_pals()
 * 
 * Argumentos: argv[]
 *             fdict - ponteiro para o ficheiro .dict
 * 
 * Return: fpals: ponteiro para o ficheiro dos problemas
 * 
 * Descrição:  Verifica se existe o ficheiro .pals, e caso 
 *             exista retorna o ponteiro para esse ficheiro.          
**********************************************************/
vetores_pals *le_pals(char *argv[], FILE *fdict){

   int fempty;
   char pal1[MAX_SIZE], pal2[MAX_SIZE];
   int permuta, tamanho;

   vetores_pals *aux = NULL;
   
   aux = iniciaVetores_pals(); 
  

   /*Verifica se é possível abrir o ficheiro .pals*/
   aux -> fpals = (FILE *) fopen(argv[2], "r");
   if (aux -> fpals == (FILE *) NULL) {
      /*Não é possível abrir o ficheiro*/
      fclose(fdict);
      exit(0);
   }
   
   /*Verificação se o ficheiro .pals está vazio*/
   if(aux -> fpals != (FILE *) NULL){
      fseek(aux -> fpals, 0, SEEK_END);
      fempty = ftell(aux -> fpals);
      if(fempty == 0){
         fclose(fdict);
         exit(0);
      }

      rewind(aux -> fpals);

   }

   while((fscanf(aux -> fpals, "%s %s %d", pal1, pal2, &permuta)) != EOF){
      
      /*Mete o vetor aux->criar_dic = 1, se o problema for válido
      para saber que temos que criar o dicionario para as palavras
      daquele tamanho*/
      tamanho = strlen(pal1);

      if((tamanho == strlen(pal2)) && (permuta >= 0)){
         aux -> criar_dic[tamanho] = 1;

         if((aux -> tamanho_maximo) < tamanho)
            aux -> tamanho_maximo = tamanho;   

      }
      
   }

   rewind(aux -> fpals);
   
   return aux;
}


/********************************************************
 * verifica_criar_grafos()
 * 
 * Argumentos: *info - ponteiro para a estrutura vetores_pals
 *             *tabelaD - ponteiro para tabela de dicionários
 *             size_palavra: vetor com o total de palavras do mesmo tamanho
 * 
 * Return: fpals: ponteiro para o ficheiro dos problemas
 * 
 * Descrição:  Verifica se existe o ficheiro .pals, e caso 
 *             exista retorna o ponteiro para esse ficheiro.          
**********************************************************/
void verifica_criar_grafos(vetores_pals *info, dicionario **tabelaD, int *size_palavra){
   
   char pal1[MAX_SIZE];
   char pal2[MAX_SIZE];
   int permuta, i, tamanho, letras_dif;
   int pos1, pos2;

   while((fscanf(info -> fpals, "%s %s %d", pal1, pal2, &permuta)) != EOF){
      
      /*Mete o vetor aux->criar_dic = 1, se o problema for válido
      para saber que temos que criar o dicionario para as palavras
      daquele tamanho*/
      tamanho = strlen(pal1);

      if((tamanho == strlen(pal2)) && (permuta >= 0)){

         i = size_palavra[ tamanho ]; /*i = nº total de palavras de um determinado tamanho*/

         if(tabelaD[tamanho] != NULL){

            pos1 = binarySearch( tabelaD[tamanho] -> dic, i, pal1);
            pos2 = binarySearch( tabelaD[tamanho] -> dic, i, pal2);

            if(pos1 != -1 && pos2 != -1 ){
               letras_dif = nr_permuta(pal1, pal2);

               if(letras_dif > 1){
                  if(info -> criar_grafo[tamanho] < permuta){
                     if(permuta >= letras_dif){
                        info -> criar_grafo[tamanho] = letras_dif - 1;
                     }
                     else
                        info -> criar_grafo[tamanho] = permuta;
                  }

               }
                  
            }
         
         }

      }

   }

   rewind(info -> fpals);

}




/*******************************************************************************
 * escreveFicheiro()
 * 
 * Argumentos: argv
 *             *info: ponteiro par a estrutura vetores_pals
 *             **tabelaD: ponteiro para a tabela de ponteiros para dicionarios
 *             **tabelaG: ponteiro para a tabela de ponteiros para grafos 
 *             size_palavra: vetor com o total de palavras do mesmo tamanho
 * Return: void
 * 
 * Descrição:  Vai criar o ficheiro de saida e escrever nele as respostas aos problemas 
 *             do ficheiro .pals
**********************************************************************************/
void escreveFicheiro(char *argv[], vetores_pals *info, dicionario **tabelaD, grafo **tabelaG, int *size_palavra){
   FILE *fsaida = NULL;
   char *nomesaida;

   nomesaida = (char*) malloc(sizeof(char) * (strlen(argv[2]) + 1 + strlen(".paths")));
   if (nomesaida == NULL ) {
      /*not enough memory available!*/
      exit (0);
   }

   strcpy (nomesaida, argv[2]);
   nomesaida[strlen(nomesaida)-5] = '\0';
   strcat (nomesaida, ".paths");

   fsaida = (FILE *) fopen(nomesaida, "w");
   if(fsaida == NULL){
      /*não é possível abrir o ficheiro"*/
      exit(0);
   }

   resolve_pals(info, fsaida, tabelaD, tabelaG, size_palavra);

   fclose(fsaida);

   free(nomesaida);
}



/**********************************************************************************
 * resolve_pals()
 * 
 * Argumentos: *info: ponteiro par a estrutura vetores_pals
 *             fsaida: ponteiro para o ficheiro de saida (.stats)
 *             **tabelaD: ponteiro para a tabela de ponteiros para dicionarios
 *             **tabelaG: ponteiro para a tabela de ponteiros para grafos 
 *             size_palavra: vetor com o total de palavras do mesmo tamanho
 * Return: void
 * 
 * Descrição:  Vai resolver cada problema do ficheiro .pals e imprimir a solução
 *             para o ficheiro .paths
***********************************************************************************/
void resolve_pals(vetores_pals *info, FILE *fsaida, dicionario **tabelaD, grafo **tabelaG, int *size_palavra){

   char pal1[MAX_SIZE], pal2[MAX_SIZE];
   int *st = NULL, *wt = NULL;
   int permuta, letras_dif, caminho_encontrado;
   int i, tamanho, pos1, pos2, custo;



   while((fscanf(info -> fpals, "%s %s %d", pal1, pal2, &permuta)) != EOF){
      
      /*Verificação se as duas palavras tem o mesmo tamanho*/
      tamanho = strlen(pal1);

      if(tamanho <= info -> tamanho_maximo){

         if(tabelaD[tamanho] != NULL){

            if(tamanho == strlen(pal2) && permuta >= 0){
         
            i = size_palavra[tamanho]; /*i = nº total de palavras de um determinado tamanho*/

               pos1 = binarySearch(tabelaD[tamanho] -> dic, i, pal1);
               pos2 = binarySearch(tabelaD[tamanho] -> dic, i, pal2);
                  
                  /*Verificação se as duas palavras existem no dicionario*/
                  if((pos1 != -1) && (pos2 != -1)){
                     /*Caso em que pal1 é igual à pal2*/
                     if(strcmp(pal1, pal2) == 0){
                        fprintf(fsaida, "%s 0\n%s\n\n", pal1, pal2);
                        continue;
                     }

                     /*A permuta peritida é maior que zero*/
                     if(permuta > 0){ 

                        letras_dif = nr_permuta(pal1, pal2);

                        /*Caso em que a pal1 e a pal2 apenas diferem um caracter*/
                        if(letras_dif == 1){
                           fprintf(fsaida, "%s %d\n%s\n\n", pal1, 1, pal2);
                           continue;
                        }
                        else{ /*Caso em que temos que encontrar caminho*/

                           st = vetor_st(tabelaG[tamanho]);
                           wt = vetor_wt(tabelaG[tamanho]);

                           caminho_encontrado = dijkstra(tabelaD[tamanho], tabelaG[tamanho], pos1, pos2, permuta, info -> criar_grafo[tamanho], st, wt);

                           custo = wt[pos2];

                           /*Caso em que há caminho*/
                           if(caminho_encontrado == 1){
                              if(custo >= letras_dif*letras_dif && permuta >= letras_dif){
                                 fprintf(fsaida, "%s %d\n%s\n\n", pal1, (letras_dif*letras_dif), pal2);
                              }
                              else {
                                 caminho(fsaida, tabelaD[tamanho], tabelaG[tamanho], pos1, pos2, st, custo);
                                 fprintf(fsaida, "\n");
                              }                      
                           }
                           /*Caso em que "não há" caminho*/
                           else{
                              /*Caso em que apenas existe o caminho direto*/
                              if(permuta >= letras_dif){
                                 fprintf(fsaida, "%s %d\n%s\n\n", pal1, (letras_dif*letras_dif), pal2);
                              }
                              else{ /*Caso em que não existe mesmo caso*/
                                 fprintf(fsaida, "%s -1\n%s\n\n", pal1, pal2);
                              }
                           }

                           free_st_e_wt(st, wt);
                           continue;
                        }

                     }
                     else{ /*Se a permuta é igual a zero*/
                        /*Caso em que a permuta é zero, mas as palavras são diferentes*/
                        fprintf(fsaida, "%s -1\n%s\n\n", pal1, pal2);
                        continue;
                     }
                  }
                  else { /*Caso em que uma das palavras não está no dicionário*/
                     fprintf(fsaida, "%s -1\n%s\n\n", pal1, pal2);
                     continue;
                  }
                  
            } 

            else { /*Caso em que as palavras tem tamanho diferente ou permuta negativa*/
               fprintf(fsaida, "%s -1\n%s\n\n", pal1, pal2);
               continue;
            }

         } 
         else /*Caso em que as palavras não estão no dicionario*/
            fprintf(fsaida, "%s -1\n%s\n\n", pal1, pal2);
      }
      else 
         fprintf(fsaida, "%s -1\n%s\n\n", pal1, pal2);
   }
   
      

   fclose(info -> fpals);

}

