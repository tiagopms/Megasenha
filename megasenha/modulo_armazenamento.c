#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_palavra_e_dicas.h"

typedef struct ScoreStruct {
    char *name;
    int score;
} Score;
typedef struct RankingStruct {
    Score *scores;
    int size;
} Ranking;

#define ARMAZENAMENTO_OWN
    #include "interface_armazenamento.h"
#undef ARMAZENAMENTO_OWN

char *RANKING_FILE = "ranking.txt";

/////////////////////////////////////////////////////////////////////////////////
/*funÁ„o para sortear palavra aleatorias para primeira parte do jogo*/
/*recebe como referencia um ponterio para um arquivo, um veror de caracter para receber
 a palavra(senha), tres vetores de caractere para receber as dicas */

void primeira_fase(FILE*arquivo, wordAndHints *newWordAndHint){
    static alreadyRandom = 0;

    int i, j, contador=0; 
    char palavra[15], nivel[1], temporaria[BUFSIZ];
    rewind(arquivo);
    /*nivel recebe o nivel da palavra(variavel local pois para essa fase nao ser√° importante saber o nivel. temporaria le a linha para poder chegar at√© a linha desejada*/ 
    i=contar_linhas(); 
    if(!alreadyRandom) {
        srand(time(NULL)); 
        alreadyRandom = 1;
    }
    j=rand()%i;

    for(contador=1;contador<j;contador++){ 
        fgets(temporaria,BUFSIZ,arquivo); 
    } 
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(arquivo,"%s", (newWordAndHint->word)); 
    fscanf(arquivo,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    
    // hints in random order 
    i=3;
    j=rand()%i;
    int temp2 = j;
    fscanf(arquivo,"%s", (newWordAndHint->hints[j])); 
    while(j == temp2) {
        j=rand()%i;
    }
    fscanf(arquivo,"%s", (newWordAndHint->hints[j])); 
    if(j!=2 && temp2 != 2) {
        j = 2;
    } else { if(j!=1 && temp2 != 1) {
        j = 1;
    } else {
        j = 0;
    }}
    fscanf(arquivo,"%s", (newWordAndHint->hints[j]));

//    printf("\na palavra e %s\n", newWordAndHint->word);
}

/////////////////////////////////////////////////////////////////////////////////


void segunda_fase_facil(FILE*arquivo, wordAndHints *newWordAndHint){

    int i=0, j, contador=0;
    char nivel[1], teste, temporaria[60], palavra[15], dica1[15], dica2[15], dica3[15];
    rewind(arquivo);
    
        nivel[0]=102;
        while(nivel[0]==102){
            fscanf(arquivo,"%s", palavra);
            fscanf(arquivo,"%s", nivel);
            fscanf(arquivo,"%s", dica1);
            fscanf(arquivo,"%s", dica2);
            fscanf(arquivo,"%s", dica3);
           
                if(nivel[0]==102){
                    i++;
           
                              }

        }//fim while
        
        rewind(arquivo);
        j=rand()%i;
        for(contador=1;contador<j;contador++){
            fgets(temporaria,BUFSIZ,arquivo);
            }
                     
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(arquivo,"%s", (newWordAndHint->word)); 
    fscanf(arquivo,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(arquivo,"%s", (newWordAndHint->hints[0])); 
    fscanf(arquivo,"%s", (newWordAndHint->hints[1])); 
    fscanf(arquivo,"%s", (newWordAndHint->hints[2]));

}

/////////////////////////////////////////////////////////////////////////////////


void segunda_fase_medio(FILE*arquivo, wordAndHints *newWordAndHint){

    int i=0, k=0, j, contador=0;
    char nivel[1], teste, temporaria[60], palavra[15], dica1[15], dica2[15], dica3[15];
    rewind(arquivo);
    
        do{
            fscanf(arquivo,"%s", palavra);
            fscanf(arquivo,"%s", nivel);
            fscanf(arquivo,"%s", dica1);
            fscanf(arquivo,"%s", dica2);
            fscanf(arquivo,"%s", dica3);
               
                if(nivel[0]==109){
                    i++;
           
                              }
                else{
                     
                    k++;
                                  }

        }while(nivel[0]==102 || nivel[0]==109);//fim while
        
        rewind(arquivo);
        
        j=rand()%i;
        
        for(contador=1;contador<k;contador++){
            fgets(temporaria,BUFSIZ,arquivo);
            }
        for(contador=1;contador<j;contador++){
            fgets(temporaria,BUFSIZ,arquivo);
            }
                     
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(arquivo,"%s", (newWordAndHint->word)); 
    fscanf(arquivo,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(arquivo,"%s", (newWordAndHint->hints[0])); 
    fscanf(arquivo,"%s", (newWordAndHint->hints[1])); 
    fscanf(arquivo,"%s", (newWordAndHint->hints[2]));
}


/////////////////////////////////////////////////////////////////////////////////


void segunda_fase_dificil(FILE*arquivo, wordAndHints *newWordAndHint){

    int i=0, k=0, l=0, j, contador=0;
    char nivel[1], teste, temporaria[60], palavra[15], dica1[15], dica2[15], dica3[15];
    rewind(arquivo);
   
   
        do{
                   
            fscanf(arquivo,"%s", palavra);
            fscanf(arquivo,"%s", nivel);
            fscanf(arquivo,"%s", dica1);
            fscanf(arquivo,"%s", dica2);
            fscanf(arquivo,"%s", dica3);

                if(nivel[0]==100){
                    i++;
           
                              }
                if(nivel[0]==102){
                     
                    k++;
                                  }
                                  
                
                if (nivel[0]==109){
                     
                    l++;
                                  }

        }while(nivel[0]!=101);//fim while
        
        rewind(arquivo);
        
        j=rand()%i;

        for(contador=1;contador<=l;contador++){
            fgets(temporaria,BUFSIZ,arquivo);
            }
            
        for(contador=1;contador<=k;contador++){
            fgets(temporaria,BUFSIZ,arquivo);
            }
        for(contador=1;contador<j;contador++){
            fgets(temporaria,BUFSIZ,arquivo);
            }
   
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(arquivo,"%s", (newWordAndHint->word)); 
    fscanf(arquivo,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(arquivo,"%s", (newWordAndHint->hints[0])); 
    fscanf(arquivo,"%s", (newWordAndHint->hints[1])); 
    fscanf(arquivo,"%s", (newWordAndHint->hints[2]));
}


/////////////////////////////////////////////////////////////////////////////////


/*funÁ„o para contar a quantidade de linhas que possui o arquivo. essa funÁ„o
ajuda para gerar um numero aleatorio que esteja dentro do numero de linhas que possui 
o arquivo*/

int contar_linhas()
{
  // nome e local do arquivo que ser–± aberto para
  // obtermos a quantidade de linhas
  FILE *arquivo = fopen("dicas_primeira_fase.txt", "r");
  char caractere;
  int existe_linhas = 0;
  int quant_linhas = 0;
    
  while((caractere = fgetc(arquivo)) != EOF){
    existe_linhas = 1; // h–± conte—ädo no arquivo
      
    if(caractere == '\n'){ // –π uma quebra de linha?
      // vamos incrementar a quantidade de linhas
      quant_linhas++;             
    } 
  }
  
  // se n–≥o houver uma quebra de linha na —ältima linha
  // a contagem ser–± sempre um a menos. Assim, –π melhor
  // incrementar quant_linhas mais uma vez
  if(existe_linhas)
    quant_linhas++;
  
  // vamos exibir o resultado
  
  return quant_linhas;
} 

////////////////////////////////////////////////////////////////////////////////

//int inserir_nova_palavra(FILE*arquivo, FILE*arquivo, char palavra[15], char dica1[15], char dica2[15], char dica3[15]){
    
    



//}


/////////////////////////////////////////////////////////////////////////
void ranking (int record, char *name)
{
    Ranking ranking;
    ranking = readRanking();
    
    Score newScore = fromNameAndPointsToScore(record, name);
    printf("Insert\n");
    insertNewScoreInRanking(&ranking, newScore);
    
    printf("Write\n");
    
    writeRanking(ranking);
    
    return;
}

Ranking readRanking() {
    FILE *fp;
    Ranking ranking;
    int i;
    int size;
	
    fp=fopen(RANKING_FILE,"r");//Abre o arquivo para leitura e gravaÁ„o
    
    size = getSizeOfRanking(fp);
    printf("Size: %d\n", size);
    if(!size) {
        ranking.size = 0;
        printf("Empty ranking, will create one\n");
        return ranking;
    }
    
    ranking.scores = (Score *) malloc( 10 * sizeof(Score) );
    ranking.size = size;
    
    for (i = 0; i < size ; i++) {
        
        (ranking.scores + i)->name = (char *) malloc (50 * sizeof(char));
        
        fscanf(fp, "%s", (ranking.scores + i)->name);
        fscanf(fp, "%d", &( (ranking.scores + i)->score ));
        printf("i=%d\n", i);
        printf("size=%d\n", ranking.size);
        printf("size=%d\n", (ranking.scores + i)->score);
        printf("name=%s\n", (ranking.scores + i)->name);
    }
    
    if(ranking.size > 10) {
        printf("Error: ranking in wrong format - More than 10 names\n");
        ranking.size = 10;
    }
    
    printf("Size: %d\n", ranking.size);
    for (i = 0; i < ranking.size ; i++) {
        printf("%s - %d\n", (ranking.scores + i)->name, (ranking.scores + i)->score);
    }
    
    fclose(fp);
    
    return ranking;
}

int getSizeOfRanking(FILE *fp) {
    int size = 0;
    char c;
    if( fp == NULL) {
        return 0;
    }
    
    while(!feof(fp)) {
        fread(&c, sizeof(char), 1, fp);
        if(c == '\n') {
            size++;
        }
    }
    
    rewind(fp);
    
    // remove unexistent '\n' always counted
    size--;
    return size;
}

void writeRanking(Ranking ranking) {
    FILE *fp;
    int i;
    fp=fopen(RANKING_FILE, "w");
    
    for( i = 0 ; i < ranking.size ; i++ ) {
        fprintf(fp, "%s ", ( ranking.scores + i )->name );
        fprintf(fp, "%d\n", ( ranking.scores + i )->score );
    }
}

void insertNewScoreInRanking(Ranking *ranking, Score newScore) {
    if (ranking->size == 0) {
        ranking->scores = (Score *) malloc( sizeof(Score) );
        *(ranking->scores) = newScore;
        ranking->size++;
        return;
    }
    
    int i = 0;
    int j = 0;
    int increaseSize = 0;
    
    while( ( i < ranking->size ) && ( (ranking->scores + i)->score > newScore.score ) ) {
        i++;
    }
    
    if ( i < 10 ) {
        increaseSize = 1;
        for ( j = ranking->size ; j >= i ; j-- ) {
            if ( j != 10 ) {
                *(ranking->scores + j + 1) = *(ranking->scores + j);
            } else {
                increaseSize = 0;
            }
        }
        
        *(ranking->scores + i) = newScore;
    }
    
    if (increaseSize) {
        ranking->size++;
    }
}

Score fromNameAndPointsToScore(int points, char *name) {
    Score score;
    score.name = name;
    score.score = points;
    
    return score;
}

/////////////////////////////////////////////////////////////////////////////////////
