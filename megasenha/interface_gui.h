/**Interface to the gui module.
 * Declares functions public and private to the gui module.
/*
 * @autor Douglas
 * @autor Isabella
 * @autor Thiago
 * @autor Tiago
 * @since 04/07/2014
 * @version 2.0
 *
 */

#ifndef GUI_HPP
#define GUI_HPP

#include "interface_palavra_e_dicas.h"

#ifdef GUI_OWN
    #define GUI_EXTERN
#else
    #define GUI_EXTERN extern
#endif


GUI_EXTERN int startInterface(int nPlayers, int playerToPlay);/**<starts the interface, receives command line arguments (argc and argv) (necessary for gtk) and the number of players is round (1 or 2) (if one player set which, if both set last value to any integer).*/

GUI_EXTERN void closeInterface();/**<function closes open windows.*/


GUI_EXTERN int updateInterface(void);/**<Returns a boolean that says if game wasn't closed, this function should be called constantly in a loop to allow the GUI to be updated.*/

/
int newWord(int player, wordAndHints newWordAndHint);/**<Starts new round for player with new word and hints.*/

GUI_EXTERN int waitingPlayer(void);/**<Retunrs a boolean that says if there's a player still guessing.*/

GUI_EXTERN int getPlayerScore(int player);/**<Returns number of hints used by player (1 or 2), if didn't get correct answer returns -1.*/


void updateInfoLabel (char *newInfo, char *color);/**<Function to show info on info screen (normal info in blue, errors in red).*/

void updatePlayerLabel (int newPlayer);/**<Update which player is playing in info window.*/

int gaveUp();/**<Check if player gave up.*/


GUI_EXTERN int updateGetName(void);/**<Returns a boolean that says if name was written, also updates the gui.*/

GUI_EXTERN char *getName(void);/**<Returns the name typed in the get name window.*/


GUI_EXTERN void startMainInterface(int argc, char *argv[]);// starts main window interface.*/

GUI_EXTERN int updateInitialInterface(void);// returns an integer that says if user chose any of the options (game, view ranking, add word), if it has returns which.*/

GUI_EXTERN void closeMainWindow();//closes main window.*/
enum {
    GUI_GAME = 1,
    GUI_VIEW_RANKING = 2,
    GUI_ADD_WORD = 3
};


void startRankingInterface(int argc, char *argv[]);// starts ranking window interface.*/

void destroyRankingWindow();/**<Closes ranking window.*/

int updateRankingInterface();/**<Updates ranking interface and returns if it was closed.*/


void startAddWordInterface();/**<Starts add word window interface.*/

void destroyAddWordWindow();/** <Closes add word window.*/

int updateAddWordInterface();/** <Updates add word interface and returns if it was closed.*/

int hasNewItemInAddWord();/** <Returns a boolean representing if there's a new word and hints item added.*/

wordAndHints getNewWordAndHints();/** <Returns the newest word and hints item that was added.*/


#ifdef GUI_OWN/** <Declare functions intern to GUI module.*/
    
    void destroy(GtkWidget *widget, gpointer data);/** <Receives callback if window was destroyed.*/

    
    int createWindow(Interface *gui, int player);/** <Creates player window.*/
    
    int initializeWindow(GtkWidget **window, int player);/** <Starts blank window.*/
    
    GdkPixbuf *createPixbuf(const gchar * filename);/** <Create GdkPixbuf used for window icon using filename.*/

    
    void addItemsToWindow(Interface *gui);/** <Add main items to window.*/
   
    void addTimer(GtkWidget **label, GtkWidget *hbox); /** <Adds timer to window, receives gui->timerLabel and the horizontal box where to put it.*/
    
    void addHints(Interface *gui, GtkWidget *hbox);/** <Adds hints to window, receives Interface item(gui) the horizontal box where to put it.*/
    
    void addTextBox(Interface *gui, GtkWidget *parentVbox);/** <Adds input text box to vertical box.*/
   
    void sendText(GtkWidget *widget, gpointer data); /** <Checks if correct answer and adds new hint if wrong, callback when user press enter or button to send guess.*/
    
    void createTextBox(Interface *gui, GtkWidget *frame);/** <Creates input text box, receives gui and frame where to put it.*/

   
    void updateTimerLabel (GtkWidget **label, double timePassed); /** <Updates timerbased on time passed.*/
    
    gboolean timerHandler(Interface *gui);/** <Handles time callback every second to update timer.*/
    
    void startTimer(Interface *gui);/** <Sets start time and initializes callback timeout to update timer every second.*/
    
    void updateHintLabel (GtkWidget **label, char *newHint);/** <Updates hint label with new hint.*/
    
    void restartHints (Interface *gui, wordAndHints newWordAndHint);/** <Restarts hints to only having first hint and nothing on the other two.*/

    
    int createInfoWindow(InfoInterface *infoGui);/** <Creates info window.*/
    
    int initializeInfoWindow(GtkWidget **window);/** <Initializes blank info window.*/
    void addItemsToInfoWindow(InfoInterface *gui);
    void addInfoLabel(InfoInterface *gui, GtkWidget *parentVbox);
    void addPlayer(GtkWidget **label, GtkWidget *parentHbox);
    void addQuitButton(InfoInterface *gui, GtkWidget *parentHbox);
    void quitGame(GtkWidget *widget, gpointer data);
    
    
    void startGetNameInterface();/** <Functions for get name window.*/
    int initializeGetNameWindow(GtkWidget **window);
    void addItemsToGetNameWindow(GetNameInterface *gui);
    void addGetNameTextBox(GetNameInterface *gui, GtkWidget *parentVbox);
    void createGetNameTextBox(GetNameInterface *gui, GtkWidget *frame);
    void sendName(GtkWidget *widget, gpointer data);

    
    int initializeMainWindow(GtkWidget **window);/** <Functions for initial window.*/
    void addItemsMainWindow(MainInterface *gui);
    void addButtonsToMain(GtkWidget *buttonsHbox);
    GtkWidget *addButtonToHbox(GtkWidget *buttonsHbox, char *buttonLabel);
    void setMainProgramMode(GtkWidget *widget, gpointer data);
    
    void destroyMainWindow(GtkWidget *widget, gpointer data);/** <Receives callback if window was destroyed.*/

    
    int initializeRankingWindow(GtkWidget **window);/** <Functions for ranking window.*/
    void addItemsRankingWindow(GtkWidget **window);
    void addRankingEntry(GtkWidget *parentVbox, Score score);

    
    int initializeAddWordWindow(GtkWidget **window);/** <Functions for add word window.*/
    void addItemsAddWordWindow(AddWordInterface *gui);
    void addWordAndHints(GtkWidget *widget, gpointer data);
#endif

#undef GUI_EXTERN
#endif /**<GUI_HPP.*/
