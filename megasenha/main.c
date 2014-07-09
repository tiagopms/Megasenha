/**Calls "interface_palavra_e_dica.h","interface_gui.h" and "interface_controe.h"
 * Main that shows the option select from the menu and the winner player.
/* 
 * @author Douglas
 * @author Isabella
 * @author Thiago
 * @author Tiago
 * @since 04/07/2014
 * @version 2.0
 *
 */

#include "interface_palavra_e_dicas.h"
#include "interface_gui.h"
#include "interface_controle.h"

int main(int argc, char *argv[]) {
    int choice;
    int playerVencedor = 1; /** < Integer of the nunber of the winner player.*/
    int scoreFirstRound = 0; /**< Integer of the score of the first round.*/
    choice = startMainWindow(argc, argv);/**<Select the option from menu. */

    switch(choice) {
        case GUI_GAME:/**<Select the option play in the menu. */

            playerVencedor = iniciaPrimeiraFase(&scoreFirstRound);/**< Receive the winner player*/
            closeInterface();
            updateInterface();
            printf("o player vencedor e %d\n", playerVencedor);/**< Show the winner player*/
            iniciaSegundaFase(playerVencedor, scoreFirstRound);/**<Started the second round.*/

            break;
        case GUI_VIEW_RANKING:/**<Select the option view ranking in the menu. */
            showRanking(argc, argv);
            printf("View ranking\n");
            break;
        case GUI_ADD_WORD:/**<Select the option add word in the menu. */
            startAddWordWindow();
            printf("Add word\n");
            break;
        default:
            printf("Window closed without any option chosen\n");/**<Show this mesange when no option select in the menu. */
            break;
    }
}
