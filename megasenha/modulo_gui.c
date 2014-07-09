/**Creates windows so user can interact whith the game
 * GUI module (Graphical User Interface)
 * Implements all the functions to control the interface.
 * 
 * Library used for creating windows is gtk-2.0/gtk/gtk.h
 * Calls "interface_palavra_e_dica.h"
/*
 * 
 * @author Douglas
 * @author Isabella
 * @author Thiago
 * @author Tiago
 * @since 04/072014
 * @version 2.0
 * 
 */

#ifndef S_SPLINT_S

#include <gtk-2.0/gtk/gtk.h>
#include "interface_palavra_e_dicas.h"
#include "interface_armazenamento.h"
#include <time.h>

typedef struct InterfaceStruct { /** <Structure used to be able to modify timer and hints and get player information at anytime.*/
    int player;
    GtkWidget *window;
    GtkWidget *timerLabel;
    GtkWidget *hintsLabel[3];
    GtkWidget *inputTextBox;

    time_t startTime;
    wordAndHints wordAndHints;
    int numberOfHints;
    int gotCorrectAnswer;

    int waitingForAnswer;
} Interface;

typedef struct InfoInterfaceStruct { /** <Structure used to be able to show information strings to player. This info can be strings, or the number player whose turn it is.*/
    int player;
    GtkWidget *window;
    GtkWidget *buttonAndPlayerHbox;
    GtkWidget *playerLabel;
    GtkWidget *infoLabel;
} InfoInterface;

typedef struct GetNameInterfaceStruct { /** <Structure used to be hold the get name window used to get player's name for the ranking.*/
    GtkWidget *window;
    GtkWidget *inputTextBox;

    int gotName;
    char *name;
} GetNameInterface;

typedef struct MainInterfaceStruct { /** <Structure used to be hold the main window and which program mode was chosen.*/
    GtkWidget *window;

    int choice;
} MainInterface;

typedef struct AddWordInterfaceStruct { /** <Structure used to be hold the add word window used when program in add word mode to get new word, hints and difficulty.*/
    GtkWidget *window;

    GtkWidget *wordTextBox;
    GtkWidget *hintTextBox[3];
    GtkWidget *difficultyComboBox;

    int newItem;
    wordAndHints newWordAndHints;
    
    int closed;
} AddWordInterface;

#define GUI_OWN
    #include "interface_gui.h"
#undef GUI_OWN

// vector that holds information about open GUIs
static Interface interfaces[2]; /** <Vector that holds information about open game GUIs (individual player's GUIs).*/
static int numberOfPlayers; /** <Integer of number of players playing round.*/
static int playerPlaying = 0; /** <Integer of player whose round it is.*/
static InfoInterface infoInterface; /** <Information window.*/
static GetNameInterface getNameInterface; /** <Get name window.*/
static MainInterface mainInterface; /** <Main window.*/
static AddWordInterface addWordInterface; /** <Add word window.*/
static int rankingWindowClosed = 0; /** <Boolean representing if ranking was closed.*/

/** <Closing program control variables.*/
static quitApplication = 0; /** <Variable representing if game was closed.*/
static stopTimeOuts[2] = {0, 0}; /** <Variable used to stop timers in game when game windows are closed.*/
static int playerGaveUp = 0; /** <Variable representing if a player gave up.*/

/**
 * Function void destroy
 *
 * If window closed abruptly print that player surrendered and quit program.
 */
void destroy(GtkWidget *widget, gpointer data) {
    if(!quitApplication) { /** <If application closed abruptly.*/
        g_print ("Player %s surrendered (closed application)\n", (char *) data);
        quitApplication = 1;
    }
    stopTimeOuts[0] = 1;
    stopTimeOuts[1] = 1;
}

/**
 * Function integer startInterface
 *
 * Starts all in game interface (info window and players windows).
 */
int startInterface(int nPlayers, int playerToPlay) {
    if(nPlayers == 2) { /** <Creates windows for all players.*/
        createInfoWindow(&infoInterface); /** <Creates info window.*/

        sleep(1);
        createWindow(&interfaces[0], 1); /** <Creates window for player 1.*/
        createWindow(&interfaces[1], 2); /** <Creates window for player 2.*/
    } else {
        createWindow(&interfaces[playerToPlay-1], playerToPlay); /** <If only one window, open correct one.*/
        playerPlaying = playerToPlay; /** <Set player who is playing.*/
    }

    numberOfPlayers = nPlayers; /** <Saves number of players.*/

    return 1;
}

/**
 * Function void closeInterface
 *
 * Closes players game interfaces.
 */
void closeInterface() {
    quitApplication = 1;
     // if window hasn't been closed, close it
    if (interfaces[0].window != NULL && GTK_IS_WIDGET(interfaces[0].window)) { /** <If window hasn't been closed, close it.*/
        gtk_widget_destroy(interfaces[0].window);
    }
    if (interfaces[1].window != NULL && GTK_IS_WIDGET(interfaces[1].window)) { /** <If window hasn't been closed, close it.*/
        gtk_widget_destroy(interfaces[1].window);
    }

    quitApplication = 0; /** <Allow application to be restarted (for second round maybe).*/
    stopTimeOuts[0] = 1;
    stopTimeOuts[1] = 1;
    numberOfPlayers = 0;
}

/**
 * Function integer createWindow
 *
 * Creates player game window.
 */
int createWindow(Interface *gui, int player) {
    gui->player = player; /** <Initializes player conditions.*/
    gui->waitingForAnswer = FALSE;
    gui->gotCorrectAnswer = FALSE;

    initializeWindow(&(gui->window), player); /** <Intializes blank window.*/
    addItemsToWindow(gui); /** <Adds items to window.*/
    gtk_widget_show_all(gui->window); /** <Shows everything in window.*/
}

/**
 * Function integer initializeWindow
 *
 * Initializes player's window
 */
int initializeWindow(GtkWidget **window, int player) {
    if (player != 1 && player != 2) { /** <If not valid player, raise error.*/
        printf("Error, invalid player number window opened\n");
        return 0;
    }

    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /** <Initialize window.*/

    char buf[50];
    sprintf(buf, "megasenha - player %d", player);
    gtk_window_set_title(GTK_WINDOW(*window), buf); /** <Set window's title.*/

    gtk_window_set_default_size(GTK_WINDOW(*window), 597, 177); /** <Set size and position and connects close window with destroy function.*/
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    if(player == 1) {
        gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()*1/10, gdk_screen_height()/2 - 150);
        gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroy), (gpointer) "1");
    } else {
        gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()*9/10 - 500, gdk_screen_height()/2 - 150);
        gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroy), (gpointer) "2");
    }

    sprintf(buf, "p%d.png", player); /** <Creates and sets icons for window and tells windows manager not to put them together.*/
    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf(buf));
    sprintf(buf, "player %d", player);
    gtk_window_set_wmclass(GTK_WINDOW (*window), buf, "megasenha"); 

    return 1;
}

/** Function createPixbuf
 *
 * Generates icon image used by window for task bar.
 */ 
GdkPixbuf *createPixbuf(const gchar * filename)
{
    GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
    if(!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
    }

    return pixbuf;
}

/**
 * Function void addItemsToWindow
 *
 * Adds items to player's window (buttons, labels, etc..).
 */
void addItemsToWindow(Interface *gui) {
    GtkWidget *parentVbox; /** <Creates vertical box to hold everything.*/
    parentVbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentVbox);

    GtkWidget *timerHintsHbox; /** <Creates horizontal box to hold timer and hints.*/
    timerHintsHbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentVbox), timerHintsHbox, FALSE, FALSE, 0);

    addTimer(&(gui->timerLabel), timerHintsHbox); /** <Adds timer, hints and input text boxes.*/
    addHints(gui, timerHintsHbox);
    addTextBox(gui, parentVbox);
}

/**
 * Function void addTimer
 *
 * Adds a timer to a hbox.
 */
void addTimer(GtkWidget **label, GtkWidget *parentHbox) {
    GtkWidget *frame; /** <Creates timer frame.*/
    frame = gtk_frame_new("Timer");
    gtk_widget_set_size_request (frame, 100, 100);
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, FALSE, FALSE, 0);

    *label = gtk_label_new ("Stopped"); /**<Initializes it with word "Stopped".*/
    gtk_container_add (GTK_CONTAINER (frame), *label);
}

/**
 * Function void addTimer
 *
 * Adds a hints field to a hbox.
 */
void addHints(Interface *gui, GtkWidget *parentHbox) {
    GtkWidget *frame; /** <Creates frame to hold hints.*/
    frame = gtk_frame_new("Hints");
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, TRUE, TRUE, 0);

    GtkWidget *vbox; /** <Creates vertical box to align three hints.*/
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), vbox);

    int i; /** <Writes "no hints yet" in three labels.*/
    for(i=0; i<3; i++) {
        gui->hintsLabel[i] = gtk_label_new ("No hints yet");
        gtk_box_pack_start(GTK_BOX(vbox), gui->hintsLabel[i], TRUE, TRUE, 0);
    }
}

/**
 * Function void addTextBox
 *
 * Adds input text box to window
 */
void addTextBox(Interface *gui, GtkWidget *parentVbox) {
    GtkWidget *vbox; /** <Generates vertical box that holds items.*/
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentVbox), vbox, FALSE, FALSE, 0);

    GtkWidget *frame; /**<Generates input box frame.*/
    frame = gtk_frame_new ("Write word");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    createTextBox(gui, frame); /** <Create input box.*/
}

/**
 * Funtion void sendText
 * Callback function related to text box in game window that captures words the player tryied to guess.
 * Tests if player got the correct word and if not calls functions to show next hint.
 */
void sendText(GtkWidget *widget, gpointer data)
{
    Interface *gui = (Interface *) data; /** <Simplify notation.*/
    int numberOfHints = gui->numberOfHints;
    
    if(numberOfHints > 3 || !gui->waitingForAnswer) { /** <If already 3 hints over or time done do nothing.*/
        return;
    }

    char *answer = (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox)); /** <Get answer from entry box.*/

    if(strcmp(answer, gui->wordAndHints.word) != 0) { /** <Checks if right answer.*/
        if(numberOfHints < 3) { /** <Show new hint if less than three so far or set to not waiting player anymore.*/
            updateHintLabel(&(gui->hintsLabel[numberOfHints]), gui->wordAndHints.hints[numberOfHints]);
        } else {
            gui->waitingForAnswer = FALSE;
        }
        gui->numberOfHints++; /** <If wrong increase number of hints used.*/
        
    } else { /** <If correct set player to no more waiting and got correct answer.*/
        gui->waitingForAnswer = FALSE;
        gui->gotCorrectAnswer = TRUE;
    }

    g_print ("Player sent value \"%s\"\n", (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox)));
    gtk_entry_set_text (GTK_ENTRY(gui->inputTextBox), ""); /** <Empty entry box.*/
}

/**
 * Funtion void createTextBox
 * Creates an input text box so player can make attempts to guess the word.
 */
void createTextBox(Interface *gui, GtkWidget *frame)
{
    GtkWidget *hbox; /** <Creates horizontal box to hold text box and enter button.*/
    hbox = gtk_hbox_new(FALSE, 0);

    gui->inputTextBox = gtk_entry_new(); /** <Creates input box and binds enter key (activate) to sendText function.*/
    gtk_entry_set_text (GTK_ENTRY (gui->inputTextBox), "");
    gtk_box_pack_start (GTK_BOX (hbox), gui->inputTextBox, TRUE, TRUE, 0);
    gtk_signal_connect(GTK_OBJECT(gui->inputTextBox), "activate", GTK_SIGNAL_FUNC(sendText), (gpointer) gui);

    GtkWidget *button; /** <Creates enter button and binds click to sendText function.*/
    button = gtk_button_new_with_label("Enter");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(sendText), (gpointer) gui);

    gtk_container_add(GTK_CONTAINER(frame), hbox);
}

/**
 * Funtion void updateTimerLabel
 * Updates the timer label so as a certain time has passed with the value 15-timePassed.
 */
void updateTimerLabel (GtkWidget **label, double timePassed) {
    char buf[50], *color; /** <Calculates remaining time.*/
    int remainingTime = 15-timePassed;

    if(remainingTime <= 5) { /** <If less than five seconds left print red, else blue.*/
        color = "red";
    } else {
        color = "blue";
    }

    sprintf(buf, "<span foreground=\"%s\" font=\"25\">%d</span>", color, remainingTime);

    if(remainingTime == 0) { /** <If time over and wrong answer print red, if right answer print OK! in green.*/
        color = "red";
        sprintf(buf, "<span foreground=\"%s\" font=\"42.5\">%s</span>", color, "X");
    }
    if(remainingTime == -5) {
        color = "green";
        sprintf(buf, "<span foreground=\"%s\" font=\"30\">%s</span>", color, "OK!");
        remainingTime = 0;
    }

    gtk_label_set_markup(GTK_LABEL(*label), buf); /** <Sets timer text.*/
    gtk_widget_show(*label);
}

/**
 * Funtion gboolean timerHandler
 * Time out function that updates the timer every second while active.
 */
gboolean timerHandler(Interface *gui) {
    if(quitApplication || stopTimeOuts[gui->player - 1] ) { /** <If application quit or stop time outs is on, return false to stop time out.*/
        stopTimeOuts[gui->player - 1] = 0;
        return FALSE;
    }

    time_t now; /** <Gets difference between current and start time.*/
    double timePassed;
    now = time(NULL);
    timePassed = difftime(now, gui->startTime);

    if(!gui->waitingForAnswer) { /** <If not waiting for answer anymore set time to 0 or (if answer was correct) -5.*/
        timePassed = 15;
        if(gui->gotCorrectAnswer) {
            timePassed = 20;
        }
    }

    updateTimerLabel(&(gui->timerLabel), timePassed); /** <Update timer.*/

    if(timePassed >= 15) { /** <If time over stop timeouts.*/
        gui->waitingForAnswer = FALSE;
        return FALSE;
    }
    return TRUE;
}

/**
 * Funtion void startTimer
 * Resets the timer to full time and starts it with timeouts every one second to update it.
 */
void startTimer(Interface *gui) {
    if(stopTimeOuts[gui->player - 1] ) { /** <If stop time outs is on but there's no timeout running, set it to false.*/
        stopTimeOuts[gui->player - 1] = 0;
    }
    
    gui->startTime = time(NULL); /** <Sets starting time to current.*/
    
    g_timeout_add(1000, (GSourceFunc) timerHandler, (gpointer) gui); /** <Starts timeout to update timer every second and updates timerLabel to full time.*/
    updateTimerLabel(&(gui->timerLabel), 0);
}

/**
 * Funtion void updateHintLabel
 * Adds a new hint to a hint label in blue.
 */
void updateHintLabel (GtkWidget **label, char *newHint) {
    char buf[50]; /** <Updates hint label in blue to new hint.*/
    sprintf(buf, "<span foreground=\"blue\" font=\"20\">%s</span>", newHint);

    gtk_label_set_markup(GTK_LABEL(*label), buf);
}

/**
 * Funtion void restartHints
 * Erases old hints and shows new first hint for player.
 */
void restartHints (Interface *gui, wordAndHints newWordAndHint) {
    gui->waitingForAnswer = TRUE; /** <Restarts player stats for hints.*/
    gui->gotCorrectAnswer = FALSE;
    gui->wordAndHints = newWordAndHint;
    gui->numberOfHints = 1;

    updateHintLabel(&(gui->hintsLabel[0]), newWordAndHint.hints[0]); /** <Updates first hint to new first and hides other two.*/
    updateHintLabel(&(gui->hintsLabel[1]), "---");
    updateHintLabel(&(gui->hintsLabel[2]), "---");
}

/**
 * Funtion integer newWord
 * Starts a new turn for a player.
 * Shows a new hint for the player in his game window, and grabs focus for his input text box.
 * Also saves hints and the correct word.
 */
int newWord(int player, wordAndHints newWordAndHint) {
    gtk_widget_grab_focus(interfaces[player-1].inputTextBox); /**<Brings player window to front and set focus to text entry box.*/
    gtk_window_present (GTK_WINDOW(interfaces[player-1].window));
    
    gtk_entry_set_text (GTK_ENTRY(interfaces[player-1].inputTextBox), ""); /**<Restarts interface (hint, timer and entry box).*/
    restartHints(&interfaces[player-1], newWordAndHint); 
    startTimer(&interfaces[player-1]);
    restartHints(&interfaces[player-1], newWordAndHint); 
    startTimer(&interfaces[player-1]);
}

/**
 * Funtion integer updateInterface
 * Updates interface.
 * Returns if any player closed their playing window. 
 */
int updateInterface(void) {
    while (!quitApplication && gtk_events_pending ()) { /**<While changes to do and application hasn't been closed update.*/
        gtk_main_iteration ();
    }

    return !quitApplication; /** <Return if application still working*/
}

/**
 * Funtion integer waintingPlayer
 * Returns true if any player still guessing.
 */
int waitingPlayer(void) {
    if(numberOfPlayers == 1) {
        if(interfaces[playerPlaying - 1].waitingForAnswer) {
            return 1;
        }
        return 0;
    }
    int i;
    for(i =0; i < numberOfPlayers; i++) {
        if(interfaces[i].waitingForAnswer) {
            return 1;
        }
    }
    return 0;
}

/**
 * Function integer getPlayerScore
 * Returns -1 if no correct answer, number of used hints otherwise.
 */
int getPlayerScore(int player) {
    if(interfaces[player-1].gotCorrectAnswer) {
        return interfaces[player-1].numberOfHints;
    } else {
        return -1;
    }
}

/**
 * Function integer createInfoWindow
 * Creates info window.
 */
int createInfoWindow(InfoInterface *infoGui) {
    initializeInfoWindow(&(infoGui->window)); /** <Initializes blank info window.*/
    addItemsToInfoWindow(infoGui); /** <Adds items to window.*/
    gtk_widget_show_all(infoGui->window); /** <Shows everything in window.*/
}

/**
 * Function integer initializeInfoWindow
 * Initializes info window.
 */
int initializeInfoWindow(GtkWidget **window) {
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /** <Initialize window.*/

    char buf[50]; /** <Set title.*/
    sprintf(buf, "megasenha - info window");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    gtk_window_set_default_size(GTK_WINDOW(*window), 797, 107); /** <Set size and position and connects close window with destroy function.*/
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 797/2, gdk_screen_height()*1/20);

    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg")); /** <Creates and sets icons for windows and tell windows manager not to put them together.*/
    gtk_window_set_wmclass(GTK_WINDOW (*window), "infoWindow", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

/**
 * Function void addItemsToInfoWindow
 * Add items to info window (buttons, labels, etc..).
 */
void addItemsToInfoWindow(InfoInterface *gui) {
    GtkWidget *parentHbox; /** Creates horizontal box to hold everything.*/
    parentHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentHbox);

    addPlayer(&(gui->playerLabel), parentHbox); /** <Adds timer, hints and input text boxes.*/
    addInfoLabel(gui, parentHbox);
    addQuitButton(gui, parentHbox);
}

/**
 * Function void quitGame
 * Adds info label, which contains information strings to info window.
 */
void addInfoLabel(InfoInterface *gui, GtkWidget *parentVbox) {

    GtkWidget *frame; /** <Creates frame to hold hints.*/
    frame = gtk_frame_new("Info");
    gtk_box_pack_start(GTK_BOX(parentVbox), frame, TRUE, TRUE, 0);

    gui->infoLabel = gtk_label_new ("No info yet"); /** <Writes "no info yet" in labels.*/
    gtk_container_add (GTK_CONTAINER (frame), gui->infoLabel);
}

/**
 * Function void quitGame
 * Adds player label, which contains info on currently playing player to info window.
 */
void addPlayer(GtkWidget **label, GtkWidget *parentHbox) {
    GtkWidget *frame; /** <Creates player who is playing frame.*/
    frame = gtk_frame_new("Player");
    gtk_widget_set_size_request (frame, 100, 100);
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, FALSE, FALSE, 0);

    *label = gtk_label_new ("None"); /** <Initializes it with word "None".*/
    gtk_container_add (GTK_CONTAINER (frame), *label);
}

/**
 * Function void addQuitButton
 * Adds input text box to window.
 */
void addQuitButton(InfoInterface *gui, GtkWidget *parentHbox) {
    GtkWidget *frame; /** <Generates input box frame.*/
    frame = gtk_frame_new ("Surrender");
    gtk_box_pack_start (GTK_BOX (parentHbox), frame, FALSE, FALSE, 0);

    GtkWidget *button; /** <Creates give up button.*/
    button = gtk_button_new_with_label("Give up");
    gtk_container_add (GTK_CONTAINER (frame), button);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(quitGame), (gpointer) gui);
}

/**
 * Function void quitGame
 * Callback related to give up button in info window.
 * If in second round and in give up time, sets player as given up.
 * Else tell player he can't give up in first round or in middle of a round.
 */
void quitGame(GtkWidget *widget, gpointer data)
{
    InfoInterface *gui = (InfoInterface *) data; /** <Simplify notation.*/

    if(waitingPlayer() || !playerPlaying) {
        if(!playerPlaying) {
            g_print ("Player tried to give up, impossible in first round\n", playerPlaying);
            updateInfoLabel("Impossible to give up in first part!", "red");
        } else {
            g_print ("Player %d tried to give up, only possible in time between words\n", playerPlaying);
            updateInfoLabel("Only allowed to give up between words!", "red");
        }
        return;
    }

    updateInfoLabel("Player gave up!", "red"); /** <Show that player gave up.*/
    playerGaveUp = 1;
    g_print ("Player %d gave up\n", playerPlaying);
}

/**
 * Function void updateInfoLabel
 * Updates info label in info window with new string and color.
 */
void updateInfoLabel (char *newInfo, char *color) {
    char buf[150]; /** <Updates hint label in blue to new hint.*/
    sprintf(buf, "<span foreground=\"%s\" font=\"20\">%s</span>", color, newInfo);

    gtk_label_set_markup(GTK_LABEL(infoInterface.infoLabel), buf);
}

/**
 * Function void updatePlayerLabel
 * Updates player label in info window with player currently playing.
 */
void updatePlayerLabel (int newPlayer) {
    char buf[50]; /** <Updates player label in green to new player who is playing.*/
    sprintf(buf, "<span  foreground=\"green\" font=\"40\">%d</span>", newPlayer);

    gtk_label_set_markup(GTK_LABEL(infoInterface.playerLabel), buf);
}

/**
 * Function integer gaveUp
 * Returns 1 if player gave up, 0 otherwise.
 */
int gaveUp() {
    return playerGaveUp;
}

/**
 * Function void startGetNameInterface
 * Creates, startsand shows get name window.
 */
void startGetNameInterface() {
    initializeGetNameWindow(&(getNameInterface.window)); /** <Intializes blank window.*/
    addItemsToGetNameWindow(&getNameInterface); /** <Adds items to window.*/
    gtk_widget_show_all(getNameInterface.window); /** <Shows everything in window.*/
}

/**
 * Function integer initializeGetNameWindow
 * Initializes get name window.
 */
int initializeGetNameWindow(GtkWidget **window) {
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /**<Initialize window.*/

    char buf[50]; /** <Set title.*/
    sprintf(buf, "megasenha - type your name");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    gtk_window_set_default_size(GTK_WINDOW(*window), 397, 107); /** <Set size and position and connects close window with destroy function.*/
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 397/2, gdk_screen_height()*9/20);

    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg")); /** <Sets and creates icons for windows and tell windows manager not to put them together.*/
    gtk_window_set_wmclass(GTK_WINDOW (*window), "infoWindow", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

/**
 * Function void addItemsToGetNameWindow
 * Add items to get name window (buttons, input text box, etc..).
 */
void addItemsToGetNameWindow(GetNameInterface *gui) {
    GtkWidget *parentHbox; /** <Creates horizontal box to hold everything.*/
    parentHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentHbox);

    addGetNameTextBox(gui, parentHbox); /** <Adds input text box.*/
}

/**
 * Function void addGetNameTextBox
 * Adds input text box to get name window.
 */
void addGetNameTextBox(GetNameInterface *gui, GtkWidget *parentHbox) {
    GtkWidget *vbox; /** <Generates vertical box that holds items.*/
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentHbox), vbox, FALSE, FALSE, 0);

    GtkWidget *frame; /** <Generates input box frame.*/
    frame = gtk_frame_new ("Write your name");
    gtk_box_pack_start (GTK_BOX (parentHbox), frame, TRUE, TRUE, 0);

    createGetNameTextBox(gui, frame); /**<Create input box.*/
}

/**
 * Function void createGetNameTextBox
 * Creates an input text box to get a name from user.
 */
void createGetNameTextBox(GetNameInterface *gui, GtkWidget *frame)
{
    GtkWidget *hbox; /** <Creates horizontal box to hold text box and enter button.*/
    hbox = gtk_hbox_new(FALSE, 0);

    gui->inputTextBox = gtk_entry_new(); /** <Creates input box and binds enter key (activate) to sendText function.*/
    gtk_entry_set_text (GTK_ENTRY (gui->inputTextBox), "");
    gtk_box_pack_start (GTK_BOX (hbox), gui->inputTextBox, TRUE, TRUE, 0);
    gtk_signal_connect(GTK_OBJECT(gui->inputTextBox), "activate", GTK_SIGNAL_FUNC(sendName), (gpointer) gui);

    GtkWidget *button; /** <Creates enter button and binds click to sendText function.*/
    button = gtk_button_new_with_label("Enter");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(sendName), (gpointer) gui);

    gtk_container_add(GTK_CONTAINER(frame), hbox);
}

/**
 * Function void sendName
 * Callback function called from get name window when player has finished typing his name (presses enter or clicks the enter button in the get name window).
 */
void sendName(GtkWidget *widget, gpointer data)
{
    GetNameInterface *gui = (GetNameInterface *) data; /** <Simplify notation.*/
    
    gui->name = (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox)); /** <Get name from entry box.*/

    if(strcmp(gui->name, "") != 0) { /** <Checks if name isn't empty.*/
        gui->gotName = 1;
    }

    g_print ("Player sent value \"%s\"\n", (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox))); /** <Print player name.*/
}

/**
 * Function char *getName
 * Returns string with last name typed in get name window.
 * If no name was typed, returns an invalid value.
 */
char *getName()
{
    return getNameInterface.name;
}

/**
 * Function integer updateGetName
 * Updates the interface.
 * Returns 1 if no name was typed in window, or 0 if a name was already gotten.
 */
int updateGetName()
{
    if(getNameInterface.gotName)
        return 0;

    gtk_main_iteration ();
    return 1;
}

/**
 * Function void startMainInterface
 * Starts the program main window, which gives three choices to user:
 * - Play game;
 * - View ranking;
 * - Add new word.
 */
void startMainInterface(int argc, char *argv[]) {
    gtk_init(&argc, &argv); /**<Start gtk.*/

    initializeMainWindow(&(mainInterface.window));/** <Initializes blank window.*/
    addItemsMainWindow(&mainInterface); /** <Adds items to window.*/
    gtk_widget_show_all(mainInterface.window); /** <Shows everything in window.*/
}

/**
 * Function void initializeMainWindow
 * Initializes main window.
 */
int initializeMainWindow(GtkWidget **window) {
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL); /** <Initialize window.*/

    char buf[150]; /** <Set title.*/
    sprintf(buf, "megasenha - menu");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    gtk_window_set_default_size(GTK_WINDOW(*window), 397, 107); /** <Set size and position and connects close window with destroy function.*/
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 397/2, gdk_screen_height()*9/20);
    gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroyMainWindow), NULL); /** <Connects close window with destroyMainWindow function*/

    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg")); /** <Creates and sets icons for windows and tell windows manager not to put them together.*/
    gtk_window_set_wmclass(GTK_WINDOW (*window), "infoWindow", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

void addItemsMainWindow(MainInterface *gui) {
    // creates horizontal box to hold everything
    GtkWidget *parentHbox;
    parentHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentHbox);

    // creates buttons frame
    GtkWidget *frame;
    frame = gtk_frame_new("Choose one mode");
    gtk_widget_set_size_request (frame, 390, 100);
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, FALSE, FALSE, 0);

    // creates horizontal box to hold the three buttons
    GtkWidget *buttonsHbox;
    buttonsHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame), buttonsHbox);

    // adds buttons 
    addButtonsToMain(buttonsHbox);
}

void addButtonsToMain(GtkWidget *buttonsHbox) {
    int *mode1 = (int *) malloc (sizeof(int));
    int *mode2 = (int *) malloc (sizeof(int));
    int *mode3 = (int *) malloc (sizeof(int));
    // creates game button and binds click to setMainProgramMode function
    GtkWidget *gameButton = addButtonToHbox(buttonsHbox, "Game");
    *mode1 = 1;
    gtk_signal_connect(GTK_OBJECT(gameButton), "clicked", GTK_SIGNAL_FUNC(setMainProgramMode), (gpointer) mode1);

    // creates ranking button and binds click to setMainProgramMode function
    GtkWidget *rankingButton = addButtonToHbox(buttonsHbox, "View ranking");
    *mode2 = 2;
    gtk_signal_connect(GTK_OBJECT(rankingButton), "clicked", GTK_SIGNAL_FUNC(setMainProgramMode), (gpointer) mode2);

    // creates add word button and binds click to setMainProgramMode function
    GtkWidget *addWordButton = addButtonToHbox(buttonsHbox, "Add word");
    *mode3 = 3;
    gtk_signal_connect(GTK_OBJECT(addWordButton), "clicked", GTK_SIGNAL_FUNC(setMainProgramMode), (gpointer) mode3);
}

GtkWidget *addButtonToHbox(GtkWidget *buttonsHbox, char *buttonLabel) {
    // creates button and adds it to hbox
    GtkWidget *button;
    button = gtk_button_new_with_label(buttonLabel);
    gtk_widget_set_size_request (button, 130, 100);
    gtk_box_pack_start(GTK_BOX(buttonsHbox), button, FALSE, FALSE, 0);
    
    return button;
}

// sets main functionallity of program
void setMainProgramMode(GtkWidget *widget, gpointer data) {
    int *choice = (int*) data;
    mainInterface.choice = *choice;
}

// if window closed abruptly stop program
void destroyMainWindow(GtkWidget *widget, gpointer data) {
    mainInterface.choice = -1;
}

// closes main window interface
void closeMainWindow() {
    if (mainInterface.choice != -1) {
        gtk_widget_destroy(mainInterface.window);
    }
}

int updateMainInterface()
{
    gtk_main_iteration();
    return mainInterface.choice;
}

/**
 * Function void startRankingInterface
 * Starts the ranking window, which gives the user names and points from 10 best pontuations ever gotten.
 */
void startRankingInterface(int argc, char *argv[]) {
    //start gtk
    gtk_init(&argc, &argv);
    GtkWidget *window;

    // intializes blank window
    initializeRankingWindow(&(window));
    // adds items to window
    addItemsRankingWindow(&window);
    // shows everything in window
    gtk_widget_show_all(window);
}

// initiate get name window
int initializeRankingWindow(GtkWidget **window) {
    // initialize window
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set title
    char buf[150];
    sprintf(buf, "megasenha - ranking");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    // set size and position and connects close window with destroy function
    gtk_window_set_default_size(GTK_WINDOW(*window), 547, 357);
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 547/2, gdk_screen_height()/2 - 357/2);
    gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroyRankingWindow), NULL);

    // sets and creates icons for windows and tell windows manager not to put them together
    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg"));
    gtk_window_set_wmclass(GTK_WINDOW (*window), "alal2Window", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

void addItemsRankingWindow(GtkWidget **window) {
    // creates horizontal box to hold everything
    GtkWidget *parentHbox;
    parentHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (*window), parentHbox);

    // creates buttons frame
    GtkWidget *frame;
    frame = gtk_frame_new("Ranking entries");
    gtk_widget_set_size_request (frame, 547, 350);
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, FALSE, FALSE, 0);

    // creates horizontal box to hold the three buttons
    GtkWidget *rankingVbox;
    rankingVbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frame), rankingVbox);

    // adds ranking item
    Ranking ranking = readRanking();
    int i = 0;
    for( i = 0 ; i < ranking.size ; i++) {
        addRankingEntry(rankingVbox, *(ranking.scores + i) );
    }
}

void addRankingEntry(GtkWidget *parentVbox, Score score) {
    
    char buf[150];
    sprintf(buf, "<span foreground=\"blue\" font=\"20\">%s</span><span foreground=\"black\" font=\"20\">\t-\t</span><span foreground=\"red\" font=\"20\">%d</span>", score.name, score.score);

    // initializes it with name and score from buffer
    GtkWidget *label = gtk_label_new (NULL);
    gtk_label_set_markup (GTK_LABEL (label), buf);
    gtk_box_pack_start(GTK_BOX(parentVbox), label, FALSE, FALSE, 0);
}

// closes main window interface
void destroyRankingWindow() {
    rankingWindowClosed = 1;
}

// updates interface and return if interface was closed
int updateRankingInterface()
{
    gtk_main_iteration();
    return !rankingWindowClosed;
}

/**
 * Function void startAddWordInterface
 * Starts the add word window, which gives the user 4 input text boxes and one scroll down selector item to set the new:
 * - Word;
 * - 3 hints;
 * - Difficulty.
 * To add to game.
 */
void startAddWordInterface() {
    // intializes blank window
    initializeAddWordWindow(&(addWordInterface.window));
    // adds items to window
    addItemsAddWordWindow(&addWordInterface);
    // shows everything in window
    gtk_widget_show_all(addWordInterface.window);
}

// initiate add word window
int initializeAddWordWindow(GtkWidget **window) {
    // initialize window
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set title
    char buf[150];
    sprintf(buf, "megasenha - ranking");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    // set size and position and connects close window with destroy function
    gtk_window_set_default_size(GTK_WINDOW(*window), 597, 107);
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 597/2, gdk_screen_height()/2);
    gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC(destroyAddWordWindow), NULL);

    // sets and creates icons for windows and tell windows manager not to put them together
    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg"));
    gtk_window_set_wmclass(GTK_WINDOW (*window), "alal2Window", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

void addItemsAddWordWindow(AddWordInterface *gui) {
    gui->newItem = 0;
    gui->closed = 0;
    
    // creates horizontal box to hold everything
    GtkWidget *parentVbox;
    parentVbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentVbox);

    // creates word frame
    GtkWidget *frame;
    frame = gtk_frame_new("Write the word to add");
    gtk_widget_set_size_request (frame, 390, 50);
    gtk_box_pack_start(GTK_BOX(parentVbox), frame, FALSE, FALSE, 0);

    // creates word input box
    gui->wordTextBox = gtk_entry_new();
    gtk_entry_set_text (GTK_ENTRY (gui->wordTextBox), "");
    gtk_container_add (GTK_CONTAINER (frame), gui->wordTextBox);

    // creates hints frame
    GtkWidget *frameHints;
    frameHints = gtk_frame_new("Write the hints to add");
    gtk_widget_set_size_request (frameHints, 390, 100);
    gtk_box_pack_start(GTK_BOX(parentVbox), frameHints, FALSE, FALSE, 0);

    // creates vertical box to hold the three hints input boxes 
    GtkWidget *hintsVbox;
    hintsVbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(frameHints), hintsVbox);

    int i = 0;
    for( i = 0 ; i < 3 ; i++ ) {
        // creates hints input box
        gui->hintTextBox[i] = gtk_entry_new();
        gtk_entry_set_text (GTK_ENTRY (gui->hintTextBox[i]), "");
        gtk_box_pack_start (GTK_BOX (hintsVbox), gui->hintTextBox[i], FALSE, FALSE, 0);
    }

    // creates horizontal box to hold button and difficulty text box
    GtkWidget *hbox;
    hbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentVbox), hbox, FALSE, FALSE, 0);

    // creates scroll down box to hold difficulty options
    gui->difficultyComboBox = gtk_combo_box_new_text();
    gtk_box_pack_start(GTK_BOX(hbox), gui->difficultyComboBox, FALSE, FALSE, 0);
    gtk_combo_box_append_text( GTK_COMBO_BOX( gui->difficultyComboBox ), "facil" );
    gtk_combo_box_append_text( GTK_COMBO_BOX( gui->difficultyComboBox ), "medio" );
    gtk_combo_box_append_text( GTK_COMBO_BOX( gui->difficultyComboBox ), "dificil" );

    // creates enter button and binds click to addWordAndHints function
    GtkWidget *button;
    button = gtk_button_new_with_label("Add word and hints");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(addWordAndHints), (gpointer) gui);
}

void addWordAndHints(GtkWidget *widget, gpointer data) {
    // simplify notation
    AddWordInterface *gui = (AddWordInterface *) data;
    int i = 0;
    char difficulties[3] = {'f', 'm', 'd'};
    
    int index = gtk_combo_box_get_active( GTK_COMBO_BOX( gui->difficultyComboBox ) );
    printf("index= %d\n", index);
    if(index == -1) {
        printf("Error, choose a difficulty\n");
        return;
    }
    
    // get word from entry box
    char *word = (char *) gtk_entry_get_text(GTK_ENTRY(gui->wordTextBox));
    if(strcmp(word, "") == 0) {
        printf("Error, all fields are necessary\n");
        return;
    }
    char *hints[3];
    for( i = 0 ; i < 3 ; i++ ) {
        hints[i] = (char *) gtk_entry_get_text(GTK_ENTRY(gui->hintTextBox[i]));
        if(strcmp(hints[i], "") == 0) {
            printf("Error, all fields are necessary\n");
            return;
        }
    }

    wordAndHints wordAndHintsItem;
    wordAndHintsItem.word = (char *) malloc ( 50 * sizeof(char) );
    wordAndHintsItem.dificulty = difficulties[index];
    strcpy (wordAndHintsItem.word, word);
    for( i = 0 ; i < 3 ; i++ ) {
        wordAndHintsItem.hints[i] = (char *) malloc ( 50 * sizeof(char) );
        strcpy (wordAndHintsItem.hints[i], hints[i]);
    }

    gui->newItem = 1;
    gui->newWordAndHints = wordAndHintsItem;

    gtk_entry_set_text (GTK_ENTRY(gui->wordTextBox), "");
    for( i = 0 ; i < 3 ; i++ ) {
        gtk_entry_set_text (GTK_ENTRY(gui->hintTextBox[i]), "");
    }
}

// closes main window interface
void destroyAddWordWindow() {
    addWordInterface.closed = 1;
}

// updates interface and return if interface was closed
int updateAddWordInterface()
{
    gtk_main_iteration();
    return !addWordInterface.closed;
}

int hasNewItemInAddWord() {
    return addWordInterface.newItem;
}

wordAndHints getNewWordAndHints() {
    addWordInterface.newItem = 0;

        printf("word2 = %s \n", (addWordInterface.newWordAndHints).word);
        printf("diif = %c \n", (addWordInterface.newWordAndHints).dificulty);
        printf("dica = %s \n", (addWordInterface.newWordAndHints).hints[0]);
        printf("dica = %s \n", (addWordInterface.newWordAndHints).hints[1]);
        printf("dica = %s \n", (addWordInterface.newWordAndHints).hints[2]);

    return addWordInterface.newWordAndHints;
}

#endif
