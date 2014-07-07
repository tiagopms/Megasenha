/**Calls "interface_palavra_e_dicas.h"
 * Deals with all the functions that concerns the storage of the program
 * 
/*
 * @autor Douglas
 * @autor Isabella
 * @autor Thiago
 * @autor Tiago
 * @since 04/072014
 * @version 2.0
 * 
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_palavra_e_dicas.h"

typedef struct ScoreStruct {/** <struct that holds the values for the name and the score of the players.*/
    char *name;
    int score;
} Score;
typedef struct RankingStruct {/** <struct that contains the score and the number of players.*/
    Score *scores;
    int size;
} Ranking;

#define ARMAZENAMENTO_OWN
    #include "interface_armazenamento.h"
#undef ARMAZENAMENTO_OWN

char *RANKING_FILE = "ranking.txt";/**<variable that holds the name of the file that contains the ranking.*/


/**funtion void getWordFirstRound
 * function to randomly select words for the first part of the game.
*/
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
    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    
  
    i=3;/** <hints in random order .*/
    j=rand()%i;
    int temp2 = j;
    fscanf(file,"%s", (newWordAndHint->hints[j])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    while(j == temp2) {
        j=rand()%i;
    }
    fscanf(file,"%s", (newWordAndHint->hints[j])); /**<Reads the file and puts the second hint in the hint field of the struct.*/
    fscanf(file,"%s", temp);
    if(j!=2 && temp2 != 2) {
        j = 2;
    } else { if(j!=1 && temp2 != 1) {
        j = 1;
    } else {
        j = 0;
    }}
    fscanf(file,"%s", (newWordAndHint->hints[j]));/**<Reads the file and puts the third hint in the hint field of the struct.*/
    fscanf(file,"%s", temp);


}

/** function void getWordSeconfRoundEasy
 * function to randomly select words for the easy round of the  second part of the game. 
*/
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

        }
        
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
    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(file,"%s", (newWordAndHint->hints[0])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[1])); /**<Reads the file and puts the second hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[2]));/**<Reads the file and puts the third hint in the hint field of the struct.*/

}

/** function void getWordSeconfRoundMedium
 * function to randomly select words for the medium round of the  second part of the game. 
*/
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

        }while(dificulty_temp[0]==102 || dificulty_temp[0]==109);
        
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
    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(file,"%s", (newWordAndHint->hints[0])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[1]));  /**<Reads the file and puts the second hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[2]));/**<Reads the file and puts the third hint in the hint field of the struct.*/
}

/** function void getWordSeconfRoundHard
 * function to randomly select words for the hard round of the  second part of the game. 
*/
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

        }while(dificulty_temp[0]!=101);
        
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
    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    fscanf(file,"%s", (newWordAndHint->hints[0])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[1]));/**<Reads the file and puts the second hint in the hint field of the struct.*/ 
    fscanf(file,"%s", (newWordAndHint->hints[2]));/**<Reads the file and puts the third hint in the hint field of the struct.*/
}





/**
 * function type integer countLines
 * function to count the number of lines that owns the file. this function help to generate a random number that is within the number of rows that have 
the file.
*/
int countLines(){



  FILE *file = fopen("dicas_primeira_fase.txt", "r");
  char character;
  int exist_line = 0;
  int number_lines = 0;
    
  while((character = fgetc(file)) != EOF){/**< while the reading doesn't returns EOF, the number_lines keeps incrementing.*/
    exist_line = 1; 
      
    if(character == '\n'){
    
      number_lines++;             
    } 
  }
  
 
  if(exist_line)
    number_lines++;
  
 
  return number_lines;/**< Returns the number of lines of the file.*/
} 

/** function void ranking
 * function that calls functions to read, insert and write the rankings
*/
void ranking (int record, char *name)
{
    Ranking ranking;
    ranking = readRanking();/**<call to the function that reads the ranking file.*/
    
    Score newScore = fromNameAndPointsToScore(record, name);
    insertNewScoreInRanking(&ranking, newScore);/** <function that inserts the new score in the ranking.*/
    
    writeRanking(ranking);/**<function that writes the ranking in the file.*/
    
    return;
}
/** function type ranking readRanking
 * function that reads the ranking from the file
*/

Ranking readRanking() {
    FILE *fp;
    Ranking ranking;
    int i;
    int size;
	
    fp=fopen(RANKING_FILE,"r");/**<Opens the file for reading and writing.*/
    
    size = getSizeOfRanking(fp);/**<Gets the size of the ranking through the call of the function getSizeOfRanking.*/
    if(!size) {
        ranking.size = 0;
        return ranking;
    }
    
    ranking.scores = (Score *) malloc( 10 * sizeof(Score) );
    ranking.size = size;
    
    for (i = 0; i < size ; i++) {/**<Keeps incrementing until i reaches the value of the size of the file.*/
        
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


/** function type integer getSizeOfRanking
 * function that returns the size of the ranking
*/
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
    
    
    size--; /**< remove unexistent '\n' always counted.*/
    return size;
}

/** function void writeRanking
 * function that write the ranking in the ranking file.
*/
void writeRanking(Ranking ranking) {
    FILE *fp;
    int i;
    fp=fopen(RANKING_FILE, "w");
    
    for( i = 0 ; i < ranking.size ; i++ ) {
        fprintf(fp, "%s ", ( ranking.scores + i )->name );
        fprintf(fp, "%d\n", ( ranking.scores + i )->score );
    }
}
/** function void insertNewScoreInRanking
 * function that receives a ranking and a new score and adds the score in the ranking 
*/
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
/** function of type score fromNameANdPointsToScore
 * function that receives the points end the name of a player and attributes them to the score struct
*/
Score fromNameAndPointsToScore(int points, char *name) {
    Score score;
    score.name = name;
    score.score = points;
    
    return score;
}
