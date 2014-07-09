/**
 * Controls the game.
 * Implements all the functions to control the game (first or second round).
 * Also controls the mode of the program being used (play game, view ranking, or add new word to "database").
 * 
/*
 * @autor Douglas
 * @autor Isabella
 * @autor Thiago
 * @autor Tiago
 * @since 04/07/2014
 * @version 2.0
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interface_gui.h"
#include"interface_armazenamento.h"

const static int GIVE_UP_TIME = 3; /**<Constant that represents, in seconds, time player has to give up.*/

/**
 * Function integer iniciaPrimeiraFase
 * Controls and runs the first round, openning the interface and controlling scores and turns.
 * Returns winner player's score through the input variable "int *score".
 * Returns winning player.
 */
int iniciaPrimeiraFase(int *score) {
  
    int primeiraIteracao = 1, pntPlayer1=0,pntPlayer2=0;
    int dicas[2]= {0,0}, i=0, j=0;
    int rodada = 0, playerVencedor=1, flag =0, inicial =1;
    char buf [150];
    int playerTurn = 0; /**<Variable has 0 value when player one's turn, and 1 when player two.*/
    FILE *arquivo;

    if((arquivo = fopen("dicas_primeira_fase.txt","r")) == NULL)
    {
        printf("Erro ao abrir arquivo!!!\n");
        exit(1);
    }

    wordAndHints newWordAndHint;
    startInterface(2, 1); /**<Starts interface for two players.*/
    updateInterface();
    sleep(1);
    updateInterface(); /**<Updates interface.*/
    sleep(1);
    while (rodada < 6) {  /**<While still in first three turns of any of two players.*/
        updatePlayerLabel(playerTurn+1); /**<Sets player who is playing in info window.*/
        
        getWordFirstRound(arquivo, &(newWordAndHint)); /**<Gets new word for this next round.*/
        newWord(playerTurn+1,newWordAndHint); /**<Sends new word to player whose turn it is.*/
        while (updateInterface()) {
            if (!waitingPlayer()) {
                break; /**<After player gets the answer, misses three times or time is over stops waiting.*/
            }
        }
        
        int playerScore = getPlayerScore(playerTurn+1); /**<if player score is -1 he didn't get the answer else, gets the number of hints used.*/
        if (playerScore != -1) {
            dicas[j]= dicas[j] + (4 - playerScore); /**<if player got the answer, update his score.*/
        } else {
            playerScore = 4;
        }

        sprintf(buf, "Palavra numero %d\nPontuacao do jogador foi %d!", rodada+1, 4 - playerScore);
        updateInfoLabel (buf, "blue"); /**<Print in info window number of points player got.*/
        //printf("\na pontuacao e %d\n",(4-getPlayerScore(playerTurn+1)) );
        playerTurn = !playerTurn; /**<Change to other player's turn.*/
        j =!j;
        rodada++; /**<Change to next turn.*/
    }

    sprintf(buf, "A pontuacao do player 1 e %d\nA pontuacao do player 2 e %d", dicas[0], dicas[1]);
    updateInfoLabel (buf, "pink"); /**<Print in info window points of both players.*/
    for(i=0;i<2;i++){
        printf("a pontuacao do player %d e %d \n", i+1, dicas[i]);
    }

    updateInterface();
    sleep(2); /**<Waits so players see their pontuation.*/


    pntPlayer1 = dicas[0]; /**<Gets first player's pontuation.*/
    pntPlayer2 = dicas[1]; /**<Gets second player's pontuation.*/
    rodada=1;
    playerTurn =0;
    j=0;
    rodada =0;
    if(pntPlayer1 == pntPlayer2){ /**<While players are tied, give extra rounds.*/
        while (flag == 0){
            while(rodada<2){
                wordAndHints newWordAndHint;
                updateInfoLabel ("Houve um empate!", "blue"); /**<Print in info window that players are tied.*/

                getWordFirstRound(arquivo, &newWordAndHint); /**<Gets new word for this next round.*/
                newWord(playerTurn+1, newWordAndHint); /**<Sends new word to player whose turn it is.*/
                while (updateInterface()) {
                    if (!waitingPlayer()) {
                        break; /**<After player gets the answer, misses three times or time is over stops waiting.*/
                    }
                }	

                if(getPlayerScore(playerTurn+1)!=-1){
                    dicas[j]= dicas[j] + (4-getPlayerScore(playerTurn+1)); /**<Updates player's pontuation.*/
                }
                printf("\na pontuacao e %d\n",(4-getPlayerScore(playerTurn+1)) );
                playerTurn = !playerTurn;
                j =!j;
                rodada++;
            }
            pntPlayer1 = dicas[0];
            pntPlayer2 = dicas[1];
            if (pntPlayer1 == pntPlayer2){
                rodada =0;
            }
            else{
                flag =1;
            }
        }
    }

    if(pntPlayer1 > pntPlayer2){
        updateInfoLabel ("O vencedor e o player 1", "blue"); /**<Show that player one won, and return this information.*/
        updateInterface();
        *score = pntPlayer1; /**<Sets *score because it returns the player's pontuation.*/
        return 1; /**<Returns that player one won.*/
    }else{
        updateInfoLabel ("O vencedor e o player 2", "blue"); /**<Show that player two won, and return this information.*/
        updateInterface();
        *score = pntPlayer2; /**<Sets *score because it returns the player's pontuation.*/
        return 2; /**<Returns that player two won.*/
    }
}

/**
 * Function void iniciaSegundaFase
 * Controls and runs the second round, openning the interface and controlling the score and how many words player already got.
 */
void iniciaSegundaFase(int playerVencedor, int scoreFirstRound){
    int primeiraIteracao = 1, pntPlayer1=0,pntPlayer2=0;
    int dicas[2], i=0,j=0;
    char buf[150];
    int etapa = 0;
    int playerTurn = 0, flag = 0;
    char resposta;
    int perdeu = 0;
    int pontosFinais[9] = {0, 10, 100, 500, 1000, 5000, 10000, 500000, 1000000};

    FILE *arquivo; /**<File with words, dificulties and hints.*/

    if((arquivo = fopen("dicas_primeira_fase.txt","r")) == NULL) {
        printf("Erro ao abrir arquivo!!!\n");
        exit(1);
    }

    wordAndHints newWordAndHint;
    updatePlayerLabel(playerVencedor); /**<Sets player who is playing in info window.*/
    startInterface(1, playerVencedor); /**<Starts interface for only one player, the one that won first round.*/

    while (etapa<9 && flag==0) { /**<Runs game until player has beaten all 8 words or given up.*/
        while (updateInterface()) { /**<Continues running the game unless interface has been closed abruptly by user.*/
            if(!waitingPlayer()) { /**<Waits in loop until player has answered or gotten wrong answer, or time has ended. After this enters in this if to get answer information.*/
                //printf("Deseja parar e ganhar seus pontos?");
                etapa++; /**<Sets player to be in next turn.*/

                if (etapa > 8) { /**<If in turn 9, player has won.*/
                    flag = 1;
                    break;
                }

                if (etapa >= 2 && getPlayerScore(playerVencedor) == -1) { /**<If player hasn't gotten right answer in last turn, he lost.*/
                    sprintf(buf, "Voce perdeu!");
                    updateInfoLabel (buf, "blue");
                    updateInterface();
                    sleep(3);

                    flag = 1;
                    perdeu = 1;
                    break;
                }

                if(etapa > 1) {
                    free(newWordAndHint.word);
                    free(newWordAndHint.hints[0]);
                    free(newWordAndHint.hints[1]);
                    free(newWordAndHint.hints[2]);
                }

                sprintf(buf, "Aperte give up para manter seus pontos atuais\n%d", pontosFinais[etapa-1] * scoreFirstRound);
                updateInfoLabel (buf, "blue"); /**<Tell player he can give up to keep current score.*/
                updateInterface();
                int sleepCounter = 0;
                for (sleepCounter = 0 ; sleepCounter < GIVE_UP_TIME ; sleepCounter++) { /**<Wait for player to give up if he wants.*/
                    sleep(1);
                    updateInterface();
                }

                if (gaveUp()) { /**<If player gave up, end game.*/
                    flag =1;
                    break;
                }
                sprintf(buf, "Jogue! A etapa é %d", etapa);
                updateInfoLabel (buf, "blue"); /**<Show player current round.*/

                if(etapa<4){ /**<For first three words, give player a word listed as difficulty easy.*/
                    getWordSecondRoundEasy(arquivo, &newWordAndHint);
                    newWord(playerVencedor, newWordAndHint); 
                } else { if(etapa>3 && etapa<7){ /**<For fourth, fifth and sixth words, give player a word listed as difficulty medium.*/
                    getWordSecondRoundMedium(arquivo, &newWordAndHint);
                    newWord(playerVencedor, newWordAndHint); 
                } else{ /**<For last two words, give player a word listed as difficulty hard.*/
                    getWordSecondRoundHard(arquivo, &newWordAndHint);
                    newWord(playerVencedor, newWordAndHint); 
                } }
            }
        }

        //wait(2);
    }

    closeInterface(); /**<Close game window.*/
    updateInterface();
    sleep(2);
    
    if(perdeu) {
        sprintf(buf, "Sinto muito, você perdeu, sua pontuacao eh 0");
        updateInfoLabel (buf, "red"); /**<If player lost, tell him.*/

        updateInterface();
        sleep(2);

        return;
    }

    printf("Parabens! Sua pontuacao foi de %d pontos!\n", pontosFinais[etapa-1] * scoreFirstRound);
    sprintf(buf, "Parabens! Sua pontuacao foi de %d pontos!", pontosFinais[etapa-1] * scoreFirstRound);
    updateInfoLabel (buf, "green"); /**<Show player's score.*/

    startGetNameInterface(); /**<Open interface to get player's name for ranking.*/

    // get winner's name
    while (updateGetName()); /**<Wait for player to write his name.*/
    char *name = getName(); /**<Get player's name.*/

    ranking(pontosFinais[etapa-1] * scoreFirstRound, name); /**<Write new score to ranking.*/

    sleep(2);
}

/**
 * Function integer startMainWindow
 * Opens program main window, which allow player to choose between playing the game, viewing the ranking, or adding a new word to the game.
 * Returns program mode chosen by user.
 */
int startMainWindow(int argc, char *argv[]) {
    startMainInterface(argc, argv); /**<Starts main program window.*/
    int choice = 0;
    
    while(!choice) { /**<Waits for player to choose an option.*/
        choice = updateMainInterface(); /**<Gets mode user has chosen to run program (game, view ranking, or add word), or 0 if he hasn't chosen yet.*/
    }

    closeMainWindow(); /**<Closes main program window.*/
    
    return choice; /**<Returns program mode chosen by user as an int.*/
}

/**
 * Function void showRanking
 * Opens ranking window, which shows all ranking information.
 */
void showRanking(int argc, char *argv[]) {
    startRankingInterface(argc, argv); /**<Starts ranking window.*/
    while(updateRankingInterface()); /**<Waits until player closes window.*/
}

/**
 * Function void startAddWordWindow
 * Opens window to add word and adds the new word, with its hints and difficulty to the file (by calling a function in armazenamento module).
 */
void startAddWordWindow() {
    wordAndHints newItem; 
    startAddWordInterface(); /**<Starts add word window.*/
    while(updateAddWordInterface()) { /**<Waits until player closes window, updating it.*/
        if(hasNewItemInAddWord()) { /**<If player added a word, get it and add it to file.*/
            newItem = getNewWordAndHints();
            insertNewWord(&newItem);
        }
    }
}
