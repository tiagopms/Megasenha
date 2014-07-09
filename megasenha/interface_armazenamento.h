/**
 * Interface to the armazenamento module.
 * Declares functions public and private to the armazenamento module.
 *
 * @autor Douglas
 * @autor Isabella
 * @autor Thiago
 * @autor Tiago
 * @since 04/07/2014
 * @version 2.0
 *
 */

#ifndef INTERFACE_ARMAZENAMENTO_H
#define INTERFACE_ARMAZENAMENTO_H
#ifdef INTERFACE_ARMAZENAMENTO_SERVIDOR
    #define EXT1
#else
    #define EXT1 extern
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "interface_palavra_e_dicas.h"

typedef struct ScoreStruct {/** <struct that holds the values for the name and the score of the players.*/
    char *name;
    int score;
} Score;

typedef struct RankingStruct {/** <struct that contains the score and the number of players.*/
    Score *scores;
    int size; 
} Ranking; 

void getWordFirstRound(FILE *arquivo, wordAndHints *newWordAndHint);

void getWordSecondRoundEasy(FILE*arquivo, wordAndHints *newWordAndHint);

void getWordSecondRoundMedium(FILE*arquivo, wordAndHints *newWordAndHint);

void getWordSecondRoundHard(FILE*arquivo, wordAndHints *newWordAndHint);

int countLines();

void insertNewWord(wordAndHints *newWordAndHint);

void ranking (int recorde, char *name);

Ranking readRanking();

int getSizeOfRanking(FILE *fp);

// declare functions only used in armazenamento module
#ifdef ARMAZENAMENTO_OWN
    void writeWordAndHint(PWordsAndHints Pwords, int linesNum);

    void writeRanking(Ranking ranking);
    void insertNewScoreInRanking(Ranking *ranking, Score newScore);
    Score fromNameAndPointsToScore(int points, char *name);
#endif

#endif
