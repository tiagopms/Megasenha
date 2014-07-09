/**
 * Interface to the gui module.
 * Declares functions public and private to the gui module.
 *
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

// starts the interface, receives command line arguments (argc and argv) (necessary for gtk) and the number of players is round (1 or 2) (if one player set which, if both set last value to any integer)
GUI_EXTERN int startInterface(int nPlayers, int playerToPlay);
// function closes open windows
GUI_EXTERN void closeInterface();

// returns a boolean that says if game wasn't closed, this function should be called constantly in a loop to allow the GUI to be updated
GUI_EXTERN int updateInterface(void);

// starts new round for player with new word and hints
int newWord(int player, wordAndHints newWordAndHint);
// retunrs a boolean that says if there's a player still guessing
GUI_EXTERN int waitingPlayer(void);
// returns number of hints used by player (1 or 2), if didn't get correct answer returns -1
GUI_EXTERN int getPlayerScore(int player);

// function to show info on info screen (normal info in blue, errors in red)
void updateInfoLabel (char *newInfo, char *color);
// update which player is playing in info window
void updatePlayerLabel (int newPlayer);
// check if player gave up
int gaveUp();

// returns a boolean that says if name was written, also updates the gui
GUI_EXTERN int updateGetName(void);
// returns the name typed in the get name window
GUI_EXTERN char *getName(void);

// starts main window interface
GUI_EXTERN void startMainInterface(int argc, char *argv[]);
// returns an integer that says if user chose any of the options (game, view ranking, add word), if it has returns which
GUI_EXTERN int updateInitialInterface(void);
//closes main window
GUI_EXTERN void closeMainWindow();
enum {
    GUI_GAME = 1,
    GUI_VIEW_RANKING = 2,
    GUI_ADD_WORD = 3
};

// starts ranking window interface
void startRankingInterface(int argc, char *argv[]);
// closes ranking window
void destroyRankingWindow();
// updates ranking interface and returns if it was closed
int updateRankingInterface();

// starts add word window interface
void startAddWordInterface();
// closes add word window
void destroyAddWordWindow();
// updates add word interface and returns if it was closed
int updateAddWordInterface();
// returns a boolean representing if there's a new word and hints item added
int hasNewItemInAddWord();
// returns the newest word and hints item that was added
wordAndHints getNewWordAndHints();

// declare functions intern to GUI module
#ifdef GUI_OWN
    // receives callback if window was destroyed
    void destroy(GtkWidget *widget, gpointer data);

    // creates player window
    int createWindow(Interface *gui, int player);
    // starts blank window
    int initializeWindow(GtkWidget **window, int player);
    // create GdkPixbuf used for window icon using filename
    GdkPixbuf *createPixbuf(const gchar * filename);

    // add main items to window
    void addItemsToWindow(Interface *gui);
    // adds timer to window, receives gui->timerLabel and the horizontal box where to put it
    void addTimer(GtkWidget **label, GtkWidget *hbox);
    // adds hints to window, receives Interface item(gui) the horizontal box where to put it
    void addHints(Interface *gui, GtkWidget *hbox);
    // adds input text box to vertical box
    void addTextBox(Interface *gui, GtkWidget *parentVbox);
    // checks if correct answer and adds new hint if wrong, callback when user press enter or button to send guess
    void sendText(GtkWidget *widget, gpointer data);
    // creates input text box, receives gui and frame where to put it
    void createTextBox(Interface *gui, GtkWidget *frame);

    // updates timerbased on time passed
    void updateTimerLabel (GtkWidget **label, double timePassed);
    // handles time callback every second to update timer
    gboolean timerHandler(Interface *gui);
    // sets start time and initializes callback timeout to update timer every second
    void startTimer(Interface *gui);
    // updates hint label with new hint
    void updateHintLabel (GtkWidget **label, char *newHint);
    // restarts hints to only having first hint and nothing on the other two
    void restartHints (Interface *gui, wordAndHints newWordAndHint);

    // creates info window
    int createInfoWindow(InfoInterface *infoGui);
    // initializes blank info window
    int initializeInfoWindow(GtkWidget **window);
    void addItemsToInfoWindow(InfoInterface *gui);
    void addInfoLabel(InfoInterface *gui, GtkWidget *parentVbox);
    void addPlayer(GtkWidget **label, GtkWidget *parentHbox);
    void addQuitButton(InfoInterface *gui, GtkWidget *parentHbox);
    void quitGame(GtkWidget *widget, gpointer data);
    
    // functions for get name window
    void startGetNameInterface();
    int initializeGetNameWindow(GtkWidget **window);
    void addItemsToGetNameWindow(GetNameInterface *gui);
    void addGetNameTextBox(GetNameInterface *gui, GtkWidget *parentVbox);
    void createGetNameTextBox(GetNameInterface *gui, GtkWidget *frame);
    void sendName(GtkWidget *widget, gpointer data);

    // functions for initial window
    int initializeMainWindow(GtkWidget **window);
    void addItemsMainWindow(MainInterface *gui);
    void addButtonsToMain(GtkWidget *buttonsHbox);
    GtkWidget *addButtonToHbox(GtkWidget *buttonsHbox, char *buttonLabel);
    void setMainProgramMode(GtkWidget *widget, gpointer data);
    // receives callback if window was destroyed
    void destroyMainWindow(GtkWidget *widget, gpointer data);

    // functions for ranking window
    int initializeRankingWindow(GtkWidget **window);
    void addItemsRankingWindow(GtkWidget **window);
    void addRankingEntry(GtkWidget *parentVbox, Score score);

    // functions for add word window
    int initializeAddWordWindow(GtkWidget **window);
    void addItemsAddWordWindow(AddWordInterface *gui);
    void addWordAndHints(GtkWidget *widget, gpointer data);
#endif

#undef GUI_EXTERN
#endif //GUI_HPP
