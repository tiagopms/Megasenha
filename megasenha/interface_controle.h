/**Interface to the controle module.
 * Declares functions public to the controle module (no private functions are present in this module).
 *
 * @author Douglas
 * @author Isabella
 * @author Thiago
 * @author Tiago
 * @since 04/07/2014
 * @version 2.0
 *
 */

#ifndef INTERFACE_CONTROLE_H
#define INTERFACE_CONTROLE_H

int iniciaPrimeiraFase(int *score);
void iniciaSegundaFase(int playerVencedor, int scoreFirstRound);
int startMainWindow(int argc, char *argv[]);
void showRanking(int argc, char *argv[]);

#endif
