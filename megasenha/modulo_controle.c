#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"interface_gui.h"
#include"interface_armazenamento.h"


int iniciaPrimeiraFase(int *score) {
  
    int primeiraIteracao = 1, pntPlayer1=0,pntPlayer2=0;
    int dicas[2]= {0,0} , i=0,j=0;
    int rodada = 0, playerVencedor=1, flag =0, inicial =1;
    char buf [150];
    int playerTurn = 0; // zero for player 1 and 1 for player 2
    FILE *arquivo;

    if((arquivo = fopen("dicas_primeira_fase.txt","r")) == NULL)
    {
        printf("Erro ao abrir arquivo!!!\n");
        exit(1);
    }

    wordAndHints newWordAndHint;
    startInterface(2, 1);
    updateInterface();
    sleep(1);
    while (rodada<6) {

        getWordFirstRound(arquivo, &(newWordAndHint));
        newWord(playerTurn+1,newWordAndHint); 
        while (updateInterface()) {
            if (!waitingPlayer()) {
                break;
            }
        }
        //wait(4);
        // if player score is -1 he didn't get the answer else, it returns number of hints used
        int playerScore = getPlayerScore(playerTurn+1);
        if (playerScore != -1) {
            dicas[j]= dicas[j] + (4 - playerScore);
        } else {
            playerScore = 4;
        }

        sprintf(buf, "Palavra numero %d\nPontuacao do jogador foi %d!", rodada+1, 4 - playerScore);
        updateInfoLabel (buf, "blue");
        //printf("\na pontuacao e %d\n",(4-getPlayerScore(playerTurn+1)) );
        playerTurn = !playerTurn;
        j =!j;
        rodada++;
    }

    sprintf(buf, "A pontuacao do player 1 e %d\nA pontuacao do player 2 e %d", dicas[0], dicas[1]);
    updateInfoLabel (buf, "pink");
    for(i=0;i<2;i++){
        printf("a pontuacao do player %d e %d \n", i+1, dicas[i]);
    }

    updateInterface();
    sleep(2);


    pntPlayer1 = dicas[0];
    pntPlayer2 = dicas[1];
    rodada=1;
    playerTurn =0;
    j=0;
    rodada =0;
    if(pntPlayer1 == pntPlayer2){
        while (flag == 0){
            while(rodada<2){
                wordAndHints newWordAndHint;
                updateInfoLabel ("Houve um empate!", "blue");

                getWordFirstRound(arquivo, &newWordAndHint);
                newWord(playerTurn+1, newWordAndHint); 
                while (updateInterface()) {
                    if (!waitingPlayer()) {
                        break;
                    }
                }	

                if(getPlayerScore(playerTurn+1)!=-1){
                    dicas[j]= dicas[j] + (4-getPlayerScore(playerTurn+1));
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
        updateInfoLabel ("O vencedor e o player 1", "blue");
        updateInterface();
        *score = pntPlayer1;
        return 1;
    }else{
        updateInfoLabel ("O vencedor e o player 2", "blue");
        updateInterface();
        *score = pntPlayer2;
        return 2;
    }
}

void iniciaSegundaFase(int playerVencedor, int scoreFirstRound){
    int primeiraIteracao = 1, pntPlayer1=0,pntPlayer2=0;
    int dicas[2], i=0,j=0;
    char buf[150];
    int etapa = 0;// playerVencedor=1;
    int playerTurn = 0, flag = 0; // zero for player 1 and 1 for player 2
    char resposta;
    int perdeu = 0;
    int pontosFinais[8] = {10, 100, 500, 1000, 5000, 10000, 500000, 1000000};

    FILE *arquivo;

    if((arquivo = fopen("dicas_primeira_fase.txt","r")) == NULL)
    {
        printf("Erro ao abrir arquivo!!!\n");
        exit(1);
    }

    wordAndHints newWordAndHint;
    updatePlayerLabel (playerVencedor);
    startInterface(1, playerVencedor);

    while (etapa<9 && flag==0) {
        while (updateInterface()) {
            if(!waitingPlayer()) {
                //printf("Deseja parar e ganhar seus pontos?");
                etapa++;

                if (etapa > 8) {
                    flag = 1;
                    break;
                }

                if (etapa >= 2 && getPlayerScore(playerVencedor) == -1) {
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
                updateInfoLabel (buf, "blue");
                updateInterface();
                sleep(1);
                sleep(1);
                sleep(1);
                updateInterface();

                if (gaveUp()) {
                    flag =1;
                    break;
                }
                sprintf(buf, "Jogue! A etapa é %d", etapa);
                updateInfoLabel (buf, "blue");

                if(etapa<4){
                    getWordSecondRoundEasy(arquivo, &newWordAndHint);
                    newWord(playerVencedor, newWordAndHint); 
                } else {
                if(etapa>3 && etapa<7){
                    getWordSecondRoundMedium(arquivo, &newWordAndHint);
                    newWord(playerVencedor, newWordAndHint); 
                }
                else{
                    getWordSecondRoundHard(arquivo, &newWordAndHint);
                    newWord(playerVencedor, newWordAndHint); 
                } }
            }
        }

        //wait(2);
    }

    closeInterface();
    updateInterface();
    sleep(2);
    
    if(perdeu) {
        sprintf(buf, "Sinto muito, você perdeu, sua pontuacao eh 0");
        updateInfoLabel (buf, "red");

        updateInterface();
        sleep(2);

        return;
    }

    printf("Parabens! Sua pontuacao foi de %d pontos!\n", pontosFinais[etapa-1] * scoreFirstRound);
    sprintf(buf, "Parabens! Sua pontuacao foi de %d pontos!", pontosFinais[etapa-1] * scoreFirstRound);
    updateInfoLabel (buf, "green");

    startGetNameInterface();

    // get winner's name
    while (updateGetName());
    char *name = getName();

    ranking(pontosFinais[etapa-1] * scoreFirstRound, name);

    printf("%s\n", name);
    sleep(2);
}

int startMainWindow(int argc, char *argv[]) {
    startMainInterface(argc, argv);
    int choice = 0;
    
    while(!choice) {
        choice = updateMainInterface();
    }

    closeMainWindow();
  //  sleep(1);
  //  updateMainInterface();
    
    return choice;
}

void showRanking(int argc, char *argv[]) {
    startRankingInterface(argc, argv);
    while(updateRankingInterface());
}

void startAddWordWindow() {
    wordAndHints newItem; 
    startAddWordInterface();
    while(updateAddWordInterface()) {
        if(hasNewItemInAddWord()) {
            newItem = getNewWordAndHints();
        }
    }
}
