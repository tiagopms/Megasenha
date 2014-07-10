#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "modulo_armazenamento.c"
#include "interface_palavra_e_dicas.h"

/** function void test_VerifygetWordFirstRoundisWorking
*Test that verifies if the getWordFirstRound is working. The function checks if there is any change in the values passed to the function.
*/
void test_VerifygetWordFirstRoundisWorking(void){
     wordAndHints newWordAndHint;
     wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordFirstRound(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint.word , newWordAndHint2.word);
}

/** function void  test_VerifygetWordSecondRoundEasyisWorking
*Test that verifies if the getWordSecondRoundEasy is working.The function checks if there is any change in the values passed to the function.
*/
void test_VerifygetWordSecondRoundEasyisWorking(void){
     wordAndHints newWordAndHint;
      wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordSecondRoundEasy(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint2.word, newWordAndHint.word);
     
}


/**function void test_VerifygetWordSecondRoundMediumisWorking
*Test that verifies if the getWordSecondRoundMedium is working. The function checks if there is any change in the values passed to the function.
*/
void test_VerifygetWordSecondRoundMediumisWorking(void){
     wordAndHints newWordAndHint;
      wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordSecondRoundMedium(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint2.word, newWordAndHint.word);
     
}
/**function void test_VerifygetWordSecondRoundHardisWorking
*Test that verifies if the getWordSecondRoundHard is working properly. The function checks if there is any change in the values passed to the function.
*/
void test_VerifygetWordSecondRoundHardisWorking(void){
     wordAndHints newWordAndHint;
     wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordSecondRoundHard(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint2.word , newWordAndHint.word);
     
}

/**function void test_VerifygetSizeOfRankingisWorking
*Tests if the function getSizeOfRanking is working. If it returns the value -1, it means that it isn't working.
*/
void test_VerifygetSizeOfRankingisWorking(void){
    FILE *file;
    int size;
    file = fopen("ranking.txt","r");
    size = getSizeOfRanking(file);
    CU_ASSERT_TRUE(size!=-1);
}

/**function void test_VerifygetSizeofRankingEmptyFile
* Tests the behavior of the function getSizeOfRanking if it is passed an empty file. The return shoud be -1. In this case, we tested with the 
* class equivalence criteria for testing. With this test we can also cover the criteria of edges. Because with the two next tests 
* we cover all the possibilities and each run in a different edge of the function
*/
void test_VerifygetSizeofRankingEmptyFile(void){
  int size;
  FILE *file;
  file = fopen("rankingEmpty.txt", "r");
  size = getSizeOfRanking(file);
  CU_ASSERT_EQUAL(size,-1);
}

/**function void test_VerifygetSizeofRankingNullPointer
* Tests the behavior of the function getSizeOfRanking if it is passed an null pointer. The return shoud be 0.In this case, we tested with the 
* class equivalence criteria for testing.
*/
void test_VerifygetSizeofRankingNullPointer(void){
  int size;
  FILE *file;
  file = NULL;
  size = getSizeOfRanking(file);
  CU_ASSERT_EQUAL(size,0);
}

/**function void test_VerifygetSizeofRankingSize4
* Tests the behavior of the function getSizeOfRanking for a random value. The return shoud be 4.
*/
void test_VerifygetSizeofRankingSize4(void){
  int size;
  FILE *file;
  file = fopen("rankingTest.txt", "r");
  size = getSizeOfRanking(file);
  CU_ASSERT_EQUAL(size,4);
}

/**function void test_VerifycountLinesisWorking
* Tests if the function contLines is working. If the function return a value different from 0, the function is counting
*/
void test_VerifycountLinesisWorking(void){
    CU_ASSERT_TRUE( countLines() !=0);
}

/**function void test_VerifyreadRankingisWorking
* Tests if the function readRanking is reading the ranking file properly by comparing the return with the max size of the raking.
*/
void test_VerifyreadRankingisWorking(void){
    Ranking ranking;
    ranking = readRanking();
    CU_ASSERT_TRUE(ranking.size<11);
}

/**function void test_VerifyfromNameAndPointsToScoreisWorking
* Tests if the function fromNameAndPointsToScore is seting correctly the name and the score in the score struct.
*/
void test_VerifyfromNameAndPointsToScoreisWorking(void){
    
    Score scoreTest;
    char name[10] = "Teste";
    int score = 1000;
    scoreTest = fromNameAndPointsToScore(score, name);
    CU_ASSERT_EQUAL(scoreTest.score, 1000)
}


/**function void add_tests_smo_datas
* This function adds the tests to the suite.
*/
void  add_tests_smo_datas(void){
	CU_pSuite suite;
	
	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes da smo_datas",NULL,NULL);
	
	
	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, test_VerifygetWordFirstRoundisWorking);
	CU_ADD_TEST(suite, test_VerifygetWordSecondRoundEasyisWorking);
	CU_ADD_TEST(suite, test_VerifygetWordSecondRoundMediumisWorking);
	CU_ADD_TEST(suite, test_VerifygetWordSecondRoundHardisWorking);
	CU_ADD_TEST(suite, test_VerifycountLinesisWorking);
	CU_ADD_TEST(suite, test_VerifyreadRankingisWorking);
	CU_ADD_TEST(suite, test_VerifygetSizeofRankingEmptyFile);
	CU_ADD_TEST(suite, test_VerifygetSizeofRankingNullPointer);
	CU_ADD_TEST(suite, test_VerifygetSizeofRankingSize4);
	CU_ADD_TEST(suite, test_VerifygetSizeOfRankingisWorking);
	CU_ADD_TEST(suite, test_VerifyfromNameAndPointsToScoreisWorking);
}

int main(void){
	/*Inicializa o registro de suítes e testes do CUnit*/	
	if (CUE_SUCCESS != CU_initialize_registry())
    	return CU_get_error();
    
    /*Adiciona os testes ao registro*/ 	
   	add_tests_smo_datas();
	/*Muda o modo do CUnit para o modo VERBOSE
	 O modo VERBOSE mostra algumas informacoes a
	 mais na hora da execucao*/
	CU_basic_set_mode(CU_BRM_VERBOSE);
	/*Roda os testes e mostra na tela os resultados*/
	CU_basic_run_tests();
	/*Limpa o registro*/
	CU_cleanup_registry();
	return CU_get_error();
}
