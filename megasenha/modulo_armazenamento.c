/**Calls "interface_palavra_e_dicas.h"
 * Deals with all the functions that concerns the storage of the program
/* 
 *
 * @autor Douglas
 * @autor Isabella
 * @autor Thiago
 * @autor Tiago
 * @since 04/07/2014
 * @version 2.0
 * 
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface_palavra_e_dicas.h"

typedef struct PointerToWordStruct{/** <struct that holds an array of wordAndHints items and this array size, used to hold all current words (with their difficulty and hints) when adding a new word and its hints.*/
    wordAndHints *words;
    int size;
} PWordsAndHints;

#define ARMAZENAMENTO_OWN
    #include "interface_armazenamento.h"
#undef ARMAZENAMENTO_OWN

char *RANKING_FILE = "ranking.txt";/**<variable that holds the name of the file that contains the ranking.*/

/**
 * Function void getWordFirstRound
 * Function to randomly select words for the first part of the game.
*/
void getWordFirstRound(FILE *file, /*@out@*/ wordAndHints *newWordAndHint){
    static alreadyRandom = 0;
    int i, j, counter=0;
    char temporaria[BUFSIZ];
    char temp[5];
    int temp2;

    rewind(file);
    i = countLines();
    if(!alreadyRandom) {
        srand( (unsigned int) time(NULL));
        alreadyRandom = 1;
    }
    j=rand()%i;

    for(counter=1;counter<j;counter++){
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));
    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0];
    
    /** <hints in random order .*/
    i=3;
    j=rand()%i;

    temp2 = j;
    fscanf(file,"%s", (newWordAndHint->hints[j])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    while(j == temp2) {
        j=rand()%i;
    }
    fscanf(file,"%s", (newWordAndHint->hints[j])); /**<Reads the file and puts the second hint in the hint field of the struct.*/
    if(j!=2 && temp2 != 2) {
        j = 2;
    } else { if(j!=1 && temp2 != 1) {
        j = 1;
    } else {
        j = 0;
    }}
    fscanf(file,"%s", (newWordAndHint->hints[j])); /**<Reads the file and puts the third hint in the hint field of the struct.*/

// printf("\na palavra e %s\n", newWordAndHint->word);
}

/**
 * Function void getWordSeconfRoundEasy
 * Function to randomly select words for the easy round of the  second part of the game.
*/
void getWordSecondRoundEasy(FILE *file, /*@out@*/ wordAndHints *newWordAndHint){

    int i=0, j, counter=0;
    char dificulty_temp[1], temporaria[60], word_temp[15], Hint1[15], Hint2[15], Hint3[15];
    char temp[5];
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
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }
                     
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));

    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0]; /**<Puts the dificulty of the word (gotten from the file) in the dificulty field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[0])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[1])); /**<Reads the file and puts the second hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[2])); /**<Reads the file and puts the third hint in the hint field of the struct.*/

}

/**
 * Function void getWordSeconfRoundMedium
 * Function to randomly select words for the medium round of the  second part of the game. 
*/
void getWordSecondRoundMedium(FILE *file, /*@out@*/ wordAndHints *newWordAndHint){

    int i=0, k=0, j, counter=0;
    char dificulty_temp[1], temporaria[60], word_temp[15], Hint1[15], Hint2[15], Hint3[15];
    char temp[5];
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
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }
    for(counter=1;counter<j;counter++){
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }
                     
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));

    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0]; /**<Puts the dificulty of the word (gotten from the file) in the dificulty field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[0])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[1])); /**<Reads the file and puts the second hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[2])); /**<Reads the file and puts the third hint in the hint field of the struct.*/
}

/**
 * Function void getWordSeconfRoundHard
 * Function to randomly select words for the hard round of the  second part of the game. 
*/
void getWordSecondRoundHard(FILE *file, /*@out@*/ wordAndHints *newWordAndHint){

    int i=0, k=0, l=0, j, counter=0;
    char dificulty_temp[1], temporaria[60], word_temp[15], Hint1[15], Hint2[15], Hint3[15];
    char temp[5];
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
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }

    for(counter=1;counter<=k;counter++){
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }
    for(counter=1;counter<j;counter++){
        (void) fgets(temporaria, (int) BUFSIZ, file);
    }
   
    newWordAndHint->word = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[0] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[1] = (char*) malloc(50*sizeof(char));
    newWordAndHint->hints[2] = (char*) malloc(50*sizeof(char));

    fscanf(file,"%s", (newWordAndHint->word)); /**<Reads the file and puts the word in the word field of the struct.*/
    fscanf(file,"%s", temp);
    newWordAndHint->dificulty = temp[0]; /**<Puts the dificulty of the word (gotten from the file) in the dificulty field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[0])); /**<Reads the file and puts the first hint in the hint field of the struct.*/
    fscanf(file,"%s", (newWordAndHint->hints[1])); /**<Reads the file and puts the second hint in the hint field of the struct.*/ 
    fscanf(file,"%s", (newWordAndHint->hints[2])); /**<Reads the file and puts the third hint in the hint field of the struct.*/
}

/**
 * Function integer countLines
 * Function to count the number of lines that owns the file. this function help to generate a random number that is within the number of rows that have 
the file.
*/
int countLines()
{
    FILE *file = fopen("dicas_primeira_fase.txt", "r");
    char character;
    int exist_line = 0;
    int number_lines = 0;

    while((character = fgetc(file)) != EOF){ /**< while the reading doesn't returns EOF, the number_lines keeps incrementing.*/
        exist_line = 1;

        if(character == '\n'){
            number_lines++;
        }
    }

    if(exist_line)
        number_lines++;

    fclose(file);

    return number_lines; /**< Returns the number of lines of the file.*/
}

/** 
 * Function void insertNewWord
 * Function that inserts a new word (with its hints and difficulty) in the corret position in the file, so this word might be picked in future games
*/
void insertNewWord(wordAndHints newWordAndHint){
    int i, j, k;
    int medium, hard;
    FILE *file;
    int linesNum;
    PWordsAndHints Pwords; /**<Variable that holds all words and hints already present in file to be rewritten later.*/

    j = countLines();
    j--;
    linesNum = j;

    medium = 0;
    hard = 0;

    file = fopen("dicas_primeira_fase.txt","r"); /**<Opens the file with words to be read.*/

    Pwords.words = (wordAndHints *) malloc ( (j + 1) * sizeof(wordAndHints));
    Pwords.size = j + 1;

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

    /**< If new word has dificulty easy, puts it in its correct place and writes all words back to file.*/
    if( newWordAndHint.dificulty=='f') {  
        for ( k = j - 1 ; k >= 0 ; k-- ) {
            *(Pwords.words + k + 1) = *(Pwords.words + k);
        }

        *(Pwords.words) = newWordAndHint;

        writeWordAndHint(Pwords, linesNum);   
        return;
    }

    /**< If new word has dificulty medium, puts it in its correct place and writes all words back to file.*/
    if(newWordAndHint.dificulty == 'm'){

        for ( k = j - 1 ; k >= ( j - medium - hard ) ; k-- ) {
            *(Pwords.words + k + 1) = *(Pwords.words + k);
        }

        i = ( j - medium - hard );

        *(Pwords.words + i) = newWordAndHint;

        writeWordAndHint(Pwords, linesNum);   
        return;
    }   

    /**< If new word has dificulty hard, puts it in its correct place and writes all words back to file.*/
    if ( newWordAndHint.dificulty == 'd' ){

        for ( k = j - 1 ; k >= ( j - hard ) ; k-- ) {
            *(Pwords.words + k + 1) = *(Pwords.words + k);
        }
        i = ( j - hard );

        *(Pwords.words + i) = newWordAndHint;

        writeWordAndHint(Pwords, linesNum);
        return;
    } 
}

/** 
 * Function void writeWordAndHint
 * Function that writes all words, hints and difficulties from a PWordsAndHints structure to the correct file.
*/
void writeWordAndHint(PWordsAndHints PWords, int linesNum) {
    FILE *file;
    int i;
    file = fopen("dicas_primeira_fase.txt", "w"); /**<Opens the file with words to be written.*/

    linesNum++;
    for( i = 0 ; i < linesNum ; i++ ) {
        fprintf(file, "%s ", ( PWords.words + i )->word );
        fprintf(file, "%c ", ( PWords.words + i )->dificulty);
        fprintf(file, "%s ", ( PWords.words + i )->hints[0]);
        fprintf(file, "%s ", ( PWords.words + i )->hints[1]);
        fprintf(file, "%s\n", ( PWords.words + i )->hints[2]);
    }
    
    fclose(file); /**<Closes the file with words to be played, it's important to close this file to ensure that file is correctly written to disk.*/
}

/** 
 * Function void ranking
 * Function that calls functions to read, insert and write the rankings.
*/
void ranking (int record, char *name)
{
    Ranking ranking;
    Score newScore; 
    ranking = readRanking(); /**<Reads the current ranking file with names and points and saves them in a Ranking structure.*/
    
    newScore = fromNameAndPointsToScore(record, name);
    insertNewScoreInRanking(&ranking, newScore); /**<Inserts new score in the Ranking structure (new name and point). Only inserts it if points are bigger than current worse in the ranking, or if there are less than 10 names in the ranking.*/
    
    writeRanking(ranking); /**<Writes new ranking scores to file.*/
    
    return;
}

/**
 * Function Ranking readRanking
 * Function that reads the current ranking file with names and points and saves them in a Ranking structure, returning this structure.
*/
Ranking readRanking() {
    FILE *fp;
    Ranking ranking;
    int i;
    int size;

    fp=fopen(RANKING_FILE,"r"); /**<Opens the file for reading.*/
    
    size = getSizeOfRanking(fp); /**<Gets the size of the ranking through the call of the function getSizeOfRanking.*/
    if(!size) {
        ranking.size = 0;
        ranking.scores = NULL;
        return ranking; /**<If size is 0, no current ranking entries, return empty Ranking, with size set to 0.*/
    }
    
    ranking.scores = (Score *) malloc( 10 * sizeof(Score) );
    ranking.size = size;
    
    for (i = 0; i < size ; i++) { /**<Loops, while incrementing i, until i reaches the value of the size of the file.*/
        
        (ranking.scores + i)->name = (char *) malloc (50 * sizeof(char));
        
        fscanf(fp, "%s", (ranking.scores + i)->name);
        fscanf(fp, "%d", &( (ranking.scores + i)->score ));
    }
    
    if(ranking.size > 10) {
        printf("Error: ranking in wrong format - More than 10 names\n");
        ranking.size = 10;
    }
    
    fclose(fp);
    
    return ranking; /**< Returns the current ranking, with names and respective points, saved in a Ranking structure.*/
}

/**
 * Function integer getSizeOfRanking
 * Function that returns the size of the ranking (in number of names/points entries).
*/
int getSizeOfRanking(FILE *fp) {
    int size = 0;
    char c;
    if( fp == NULL) {
        return 0;
    }
    
    while(!feof(fp)) {
        (void) fread(&c, sizeof(char), 1, fp);
        if(c == '\n') {
            size++;
        }
    }
    
    rewind(fp);
    
    size--; /**< Remove unexistent '\n' always counted at end of file.*/
    return size; /**<Returns size of ranking (number of entries in it).*/
}

/**
 * Function void writeRanking
 * Function that writes the ranking in the ranking file, using a Ranking structure for it.
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

/**
 * Function void insertNewScoreInRanking
 * Function that receives a ranking and a new score (name and respective point) and adds this new score in the correct position in the ranking. If the score is worse than all in ranking, and the ranking is already full (has ten entries) don't add it. 
*/
void insertNewScoreInRanking(/*@out@*/ Ranking *ranking, Score newScore) {
    int i = 0;
    int j = 0;
    int increaseSize = 0;

    if (ranking->size == 0) {
        ranking->scores = (Score *) malloc( sizeof(Score) );
        *(ranking->scores) = newScore;
        ranking->size++;
        return;
    }
    
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

/**
 * Function Score fromNameANdPointsToScore
 * Function that receives the points and the name of a player and attributes them to a Score struct.
*/
Score fromNameAndPointsToScore(int points, char *name) {
    Score score;
    score.name = name;
    score.score = points;
    
    return score;
}
