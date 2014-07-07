#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_palavra_e_dicas.h"

typedef struct PointerToWordStruct{
    wordAndHints *words;
    int size;
} PWordsAndHints;

#define ARMAZENAMENTO_OWN
    #include "interface_armazenamento.h"
#undef ARMAZENAMENTO_OWN

char *RANKING_FILE = "ranking.txt";

/////////////////////////////////////////////////////////////////////////////////
/* function to randomly select words for the first part of the game */

void getWordFirstRound(FILE*file, wordAndHints *newWordAndHint){
    static alreadyRandom = 0;

    int i, j, counter=0;
    char temporaria[BUFSIZ];
    rewind(file);
    i = countLines();
    if(!alreadyRandom) {
        srand(time(NULL));
        alreadyRandom = 1;
    }
    j=rand()%i;

    for(counter=1;counter<j;counter++){
        fgets(temporaria,BUFSIZ,file);
    }
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(file,"%s", (newWordAndHint->word));
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    
    // hints in random order
    i=3;
    j=rand()%i;
    int temp2 = j;
    fscanf(file,"%s", (newWordAndHint->hints[j]));
    while(j == temp2) {
        j=rand()%i;
    }
    fscanf(file,"%s", (newWordAndHint->hints[j]));
    if(j!=2 && temp2 != 2) {
        j = 2;
    } else { if(j!=1 && temp2 != 1) {
        j = 1;
    } else {
        j = 0;
    }}
    fscanf(file,"%s", (newWordAndHint->hints[j]));

// printf("\na palavra e %s\n", newWordAndHint->word);
}

/////////////////////////////////////////////////////////////////////////////////


void getWordSecondRoundEasy(FILE*file, wordAndHints *newWordAndHint){

    int i=0, j, counter=0;
    char dificulty_temp[1], temporaria[60], word_temp[15], Hint1[15], Hint2[15], Hint3[15];
    rewind(file);
    
        dificulty_temp[0]=102;
        while(dificulty_temp[0]==102){
            fscanf(file,"%s", word_temp);
            fscanf(file,"%s", dificulty_temp);
            fscanf(file,"%s", Hint1);
            fscanf(file,"%s", Hint2);
            fscanf(file,"%s", Hint3);
           
                if(dificulty_temp[0]==102){
                    i++;
           
                              }

        }//fim while
        
        rewind(file);
        j=rand()%i;
        for(counter=1;counter<j;counter++){
            fgets(temporaria,BUFSIZ,file);
            }
                     
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(file,"%s", (newWordAndHint->word));
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(file,"%s", (newWordAndHint->hints[0]));
    fscanf(file,"%s", (newWordAndHint->hints[1]));
    fscanf(file,"%s", (newWordAndHint->hints[2]));

}

/////////////////////////////////////////////////////////////////////////////////


void getWordSecondRoundMedium(FILE*file, wordAndHints *newWordAndHint){

    int i=0, k=0, j, counter=0;
    char dificulty_temp[1], temporaria[60], word_temp[15], Hint1[15], Hint2[15], Hint3[15];
    rewind(file);
    do{
        fscanf(file,"%s", word_temp);
        fscanf(file,"%s", dificulty_temp);
        fscanf(file,"%s", Hint1);
        fscanf(file,"%s", Hint2);
        fscanf(file,"%s", Hint3);

        if(dificulty_temp[0]==109){
            i++;
        }
        else{
            k++;
        }

    }while(dificulty_temp[0]==102 || dificulty_temp[0]==109);//fim while

    rewind(file);

    j=rand()%i;

    for(counter=1;counter<k;counter++){
        fgets(temporaria,BUFSIZ,file);
    }
    for(counter=1;counter<j;counter++){
        fgets(temporaria,BUFSIZ,file);
    }
                     
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(file,"%s", (newWordAndHint->word));
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(file,"%s", (newWordAndHint->hints[0]));
    fscanf(file,"%s", (newWordAndHint->hints[1]));
    fscanf(file,"%s", (newWordAndHint->hints[2]));
}


/////////////////////////////////////////////////////////////////////////////////


void getWordSecondRoundHard(FILE*file, wordAndHints *newWordAndHint){

    int i=0, k=0, l=0, j, counter=0;
    char dificulty_temp[1], temporaria[60], word_temp[15], Hint1[15], Hint2[15], Hint3[15];
    rewind(file);
   
   
    do{

        fscanf(file,"%s", word_temp);
        fscanf(file,"%s", dificulty_temp);
        fscanf(file,"%s", Hint1);
        fscanf(file,"%s", Hint2);
        fscanf(file,"%s", Hint3);

        if(dificulty_temp[0]==100){
            i++;
        }
        if(dificulty_temp[0]==102){
            k++;
        }


        if (dificulty_temp[0]==109){
            l++;
        }

    }while(dificulty_temp[0]!=101);//fim while

    rewind(file);

    j=rand()%i;

    for(counter=1;counter<=l;counter++){
        fgets(temporaria,BUFSIZ,file);
    }

    for(counter=1;counter<=k;counter++){
        fgets(temporaria,BUFSIZ,file);
    }
    for(counter=1;counter<j;counter++){
        fgets(temporaria,BUFSIZ,file);
    }
   
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    char temp[5];
    fscanf(file,"%s", (newWordAndHint->word));
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(file,"%s", (newWordAndHint->hints[0]));
    fscanf(file,"%s", (newWordAndHint->hints[1]));
    fscanf(file,"%s", (newWordAndHint->hints[2]));
}


/////////////////////////////////////////////////////////////////////////////////


/*function to count the number of lines that owns the file. this function
help to generate a random number that is within the number of rows that have
the file */

int countLines()
{

  FILE *file = fopen("dicas_primeira_fase.txt", "r");
  char character;
  int exist_line = 0;
  int number_lines = 0;
    
  while((character = fgetc(file)) != EOF){
    exist_line = 1;
      
    if(character == '\n'){
      number_lines++;
    }
  }
  
  if(exist_line)
    number_lines++;
  
  fclose(file);

  return number_lines;
}

////////////////////////////////////////////////////////////////////////////////

int insertNewWord(wordAndHints *newWordAndHint){
    int i, j, k;
    int medium, hard;
    FILE *file;

    j = countLines();
    j--;
    int linesNum = j;

    medium = 0;
    hard = 0;

    file = fopen("dicas_primeira_fase.txt","r");//Abre o arquivo para leitura

    PWordsAndHints Pwords;

    Pwords.words = (wordAndHints *) malloc ( (j + 1) * sizeof(wordAndHints));

    for (i = 0; i < j ; i++) {
        (Pwords.words + i)->word = (char *) malloc (50 * sizeof(char));
        (Pwords.words + i)->hints[0] = (char *) malloc (50 * sizeof(char));
        (Pwords.words + i)->hints[1] = (char *) malloc (50 * sizeof(char));
        (Pwords.words + i)->hints[2] = (char *) malloc (50 * sizeof(char));

        fscanf(file, "%s", (Pwords.words + i)->word);
        fscanf(file, " %c", &( (Pwords.words + i)->dificulty ));
        fscanf(file, "%s", (Pwords.words + i)->hints[0]);
        fscanf(file, "%s", (Pwords.words + i)->hints[1]);
        fscanf(file, "%s", (Pwords.words + i)->hints[2]);
        
        if( (Pwords.words + i)->dificulty == 'm'){
            medium++;
        }

        if( (Pwords.words + i)->dificulty == 'd'){
            hard++;
        }
    }
    hard++;

    fclose(file);

    //palavra facil   
    if( newWordAndHint->dificulty=='f') {  
        for ( k = j - 1 ; k >= 0 ; k-- ) {
            *(Pwords.words + k + 1) = *(Pwords.words + k);

        }

        *(Pwords.words + 0) = *newWordAndHint;

        writeWordAndHint(Pwords, linesNum);   
        return;
    }

    //palavra medio
    if(newWordAndHint->dificulty == 'm'){

        for ( k = j - 1 ; k >= ( j - medium - hard ) ; k-- ) {
            *(Pwords.words + k + 1) = *(Pwords.words + k);
        }

        i = ( j - medium - hard );

        *(Pwords.words + i) = *newWordAndHint;

        writeWordAndHint(Pwords, linesNum);   
        return;
    }   

    //palavrad dificil
    if ( newWordAndHint->dificulty == 'd' ){

        for ( k = j - 1 ; k >= ( j - hard ) ; k-- ) {
            *(Pwords.words + k + 1) = *(Pwords.words + k);
        }
        i = ( j - hard );

        *(Pwords.words + i) = *newWordAndHint;

        writeWordAndHint(Pwords, linesNum);
        return;
    } 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void writeWordAndHint(PWordsAndHints PWords, int linesNum) {
    FILE *file;
    int i;
    file = fopen("dicas_primeira_fase.txt", "w");

    linesNum++;
    for( i = 0 ; i < linesNum ; i++ ) {
        fprintf(file, "%s ", ( PWords.words + i )->word );
        fprintf(file, "%c ", ( PWords.words + i )->dificulty);
        fprintf(file, "%s ", ( PWords.words + i )->hints[0]);
        fprintf(file, "%s ", ( PWords.words + i )->hints[1]);
        fprintf(file, "%s\n", ( PWords.words + i )->hints[2]);
    }
    
    fclose(file);
}


/////////////////////////////////////////////////////////////////////////
void ranking (int record, char *name)
{
    Ranking ranking;
    ranking = readRanking();
    
    Score newScore = fromNameAndPointsToScore(record, name);
    insertNewScoreInRanking(&ranking, newScore);
    
    writeRanking(ranking);
    
    return;
}

Ranking readRanking() {
    FILE *fp;
    Ranking ranking;
    int i;
    int size;

    fp=fopen(RANKING_FILE,"r");//Abre o arquivo para leitura
    
    size = getSizeOfRanking(fp);
    if(!size) {
        ranking.size = 0;
        return ranking;
    }
    
    ranking.scores = (Score *) malloc( 10 * sizeof(Score) );
    ranking.size = size;
    
    for (i = 0; i < size ; i++) {
        
        (ranking.scores + i)->name = (char *) malloc (50 * sizeof(char));
        
        fscanf(fp, "%s", (ranking.scores + i)->name);
        fscanf(fp, "%d", &( (ranking.scores + i)->score ));
    }
    
    if(ranking.size > 10) {
        printf("Error: ranking in wrong format - More than 10 names\n");
        ranking.size = 10;
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
