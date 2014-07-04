#include "interface_palavra_e_dicas.h"
#include "interface_gui.h"
#include "interface_controle.h"


int main(int argc, char *argv[]) {
  int playerVencedor = 1;
  int scoreFirstRound = 0;
  
  playerVencedor = iniciaPrimeiraFase(argc, argv, &scoreFirstRound);
  closeInterface();
  updateInterface();
  printf("o player vencedor e %d\n", playerVencedor);
  iniciaSegundaFase(argc, argv, playerVencedor, scoreFirstRound);
}

// TODO: add interface to add new words
// TODO: interface to see ranking
// TODO: word can be called two times
// TODO: give more time to give up
