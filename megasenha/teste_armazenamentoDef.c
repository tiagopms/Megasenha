#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "modulo_armazenamento.c"
#include "interface_palavra_e_dicas.h"

//Tests to verify if the functions are assigning values to the address that is passed
void test_VerifygetWordFirstRoundisWorking(void){
     wordAndHints newWordAndHint;
     wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordFirstRound(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint.word , newWordAndHint2.word);
}

void test_VerifygetWordSecondRoundEasyisWorking(void){
     wordAndHints newWordAndHint;
      wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordSecondRoundEasy(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint2.word, newWordAndHint.word);
     
}

void test_VerifygetWordSecondRoundMediumisWorking(void){
     wordAndHints newWordAndHint;
      wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordSecondRoundMedium(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint2.word, newWordAndHint.word);
     
}

void test_VerifygetWordSecondRoundHardisWorking(void){
     wordAndHints newWordAndHint;
     wordAndHints newWordAndHint2;
     FILE *file;
     file = fopen("dicas_primeira_fase.txt","r");
     getWordSecondRoundHard(file, &(newWordAndHint));
    CU_ASSERT_NOT_EQUAL(newWordAndHint2.word , newWordAndHint.word);
     
}

void test_VerifygetSizeOfRankingisWorking(void){
    FILE *file;
    int size;
    file = fopen("ranking.txt","r");
    size = getSizeOfRanking(file);
    CU_ASSERT_TRUE(size!=0);
}

void test_VerifygetSizeofRankingEmptyFile(void){
  int size;
  FILE *file;
  file = fopen("rankingEmpty.txt", "r");
  size = getSizeOfRanking(file);
  CU_ASSERT_EQUAL(size,-1);
}

void test_VerifygetSizeofRankingNullPointer(void){
  int size;
  FILE *file;
  file = NULL;
  size = getSizeOfRanking(file);
  CU_ASSERT_EQUAL(size,0);
}

void test_VerifygetSizeofRankingSize4(void){
  int size;
  FILE *file;
  file = fopen("rankingTest.txt", "r");
  size = getSizeOfRanking(file);
  CU_ASSERT_EQUAL(size,4);
}


void test_VerifycountLinesisWorking(void){
    CU_ASSERT_TRUE( countLines() !=0);
}

void test_VerifyreadRankingisWorking(void){
    Ranking ranking;
    ranking = readRanking();
    CU_ASSERT_TRUE(ranking.size==10);
}



void  adicionar_testes_smo_datas(void){
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
}

int main(void){
	/*Inicializa o registro de suítes e testes do CUnit*/	
	if (CUE_SUCCESS != CU_initialize_registry())
    	return CU_get_error();
    
    /*Adiciona os testes ao registro*/ 	
   	adicionar_testes_smo_datas();
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
