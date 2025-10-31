#include "wrdmttns.h"


int main(int argc, char *argv[]){

   dicionario **tabelaD = NULL;
   vetores_pals *info = NULL;
   grafo **tabelaG = NULL;
   int size_palavra[MAX_SIZE];
   int count[MAX_SIZE];
   int i, fempty;

   FILE *fdict = NULL;


   iniciaVetor(size_palavra, MAX_SIZE);

   iniciaVetor(count, MAX_SIZE);

   val_arguments(argc, argv);

   fdict = (FILE *) fopen(argv[1], "r");

   if (fdict == (FILE *) NULL) {
      /*Verificação
      Não é possível abrir o ficheiro*/
      exit(0);
   }

   /*Verificação se o ficheiro .dict está vazio*/
   if(fdict != (FILE *) NULL){
      fseek(fdict, 0, SEEK_END);
      fempty = ftell(fdict);
      if(fempty == 0)
         exit(0);
      
      rewind(fdict);
   }

   info = le_pals(argv, fdict);

   read_fdict(fdict , size_palavra);

   /*Aloco o espaço para a lista de dicionários*/
   tabelaD = tabelaDicionario(info -> tamanho_maximo);

   /*Aloco o espaço para cada dicionário individual*/
   for(i = 1; i <= info -> tamanho_maximo; i++){
      if(info -> criar_dic[i] == 1){
         if(size_palavra[i] != 0)
            tabelaD[i] = criaDic(size_palavra[i]);
      }
   }

   inserpalavra(fdict, info -> tamanho_maximo, tabelaD, count);

   organizadicionario(tabelaD, size_palavra, info -> tamanho_maximo);

   /*Vou criar os grafos aqui*/
   verifica_criar_grafos(info, tabelaD, size_palavra);

   /*Reservo o espaço para a tabela de grafos*/
   tabelaG = tabelaGrafos(info -> tamanho_maximo);

   /*Reservo o espaço para os grafos individualmente*/
   for(i = 1; i <= info -> tamanho_maximo; i++){
      
      if(info -> criar_grafo[i] != 0)
         tabelaG[i] = iniciarGrafo(size_palavra[i]);
      
   }

   escreveFicheiro(argv, info, tabelaD, tabelaG, size_palavra);

   fclose(fdict);

   freeTabelaD(tabelaD, info -> tamanho_maximo, count);

   freeTabelaGrafo(tabelaG, info -> criar_dic);

   free_vetores_pals(info);

}





   

   
