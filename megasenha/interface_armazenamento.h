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

typedef struct ScoreStruct {
    char *name;
    int score;
} Score;

typedef struct RankingStruct {
    Score *scores;
    int size; 
} Ranking; 

void getWordFirstRound(FILE*arquivo, wordAndHints *newWordAndHint);

void getWordSecondRoundEasy(FILE*arquivo, wordAndHints *newWordAndHint);

void getWordSecondRoundMedium(FILE*arquivo, wordAndHints *newWordAndHint);

void getWordSecondRoundHard(FILE*arquivo, wordAndHints *newWordAndHint);

int countLines();

int insertNewWord(wordAndHints *newWordAndHint);

void ranking (int recorde, char *name);

Ranking readRanking();

int getSizeOfRanking(FILE *fp);

// declare functions intern to armazenamento module
#ifdef ARMAZENAMENTO_OWN
    void writeWordAndHint(PWordsAndHints Pwords, int linesNum);

    void writeRanking(Ranking ranking);
    void insertNewScoreInRanking(Ranking *ranking, Score newScore);
    Score fromNameAndPointsToScore(int points, char *name);
#endif

#endif
