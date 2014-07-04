#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "modulo_armazenamento.c"

void adicionar_testes_smo_datas(void);

//void teste_nomefuncao(void);
void 
/*void teste_nomefuncao(void){

CU_ASSERT_TRUE();
} 
 */

void adicionar_testes_smos_ddatas(void){
CU_pSuite suite;
suite = CU_add_suite("Testes da smao_datas",NULL,NULL);

//CU_ADD_TEST(suite,funçãoteste);
}
int main (void){

if (CUE_SUCCESS != CU_initialize_registry())
return CU_get_error();

adicionar_testes_smo_datas();

CU_basic_set_mode(CU_BRM_VERBOSE);

CU_basis_run_tests();

CU_cleanup_registry();
return CU_grt_error();
}

