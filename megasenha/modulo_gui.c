#include <gtk-2.0/gtk/gtk.h>
#include "interface_palavra_e_dicas.h"
#include <time.h>

// structured used to be able to modify timer and hints and get player information at anytime
typedef struct InterfaceStruct {
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

typedef struct InfoInterfaceStruct {
    int player;
    GtkWidget *window;
    GtkWidget *buttonAndPlayerHbox;
    GtkWidget *playerLabel;
    GtkWidget *infoLabel;
} InfoInterface;

typedef struct GetNameInterfaceStruct {
    GtkWidget *window;
    GtkWidget *inputTextBox;

    int gotName;
    char *name;
} GetNameInterface;

#define GUI_OWN
    #include "interface_gui.h"
#undef GUI_OWN

// vector that holds information about open GUIs
static Interface interfaces[2];
static int numberOfPlayers;
static int playerPlaying = 0;
static InfoInterface infoInterface;
static GetNameInterface getNameInterface;

// closing program control variables
static quitApplication = 0;
static stopTimeOuts[2] = {0, 0};
static int playerGaveUp = 0;

// if window closed abruptly print that player surrendered and quit program
void destroy(GtkWidget *widget, gpointer data) {
    // if application closed abruptly
    if(!quitApplication) {
        g_print ("Player %s surrendered (closed application)\n", (char *) data);
        quitApplication = 1;
    }
    stopTimeOuts[0] = 1;
    stopTimeOuts[1] = 1;
}

int startInterface(int argc, char *argv[], int nPlayers, int playerToPlay) {
    //start gtk
    gtk_init(&argc, &argv);

    // creates windows for all players
    if(nPlayers == 2) {
        createInfoWindow(&infoInterface);

        sleep(1);
        createWindow(&interfaces[0], 1);
        createWindow(&interfaces[1], 2);
    } else {
        // if only one window, set correct one
        createWindow(&interfaces[playerToPlay-1], playerToPlay);
        playerPlaying = playerToPlay;
    }

    // saves number of players
    numberOfPlayers = nPlayers;

    return 1;
}

void closeInterface() {
    quitApplication = 1;
     // if window hasn't been closed, close it
    if (interfaces[0].window != NULL && GTK_IS_WIDGET(interfaces[0].window)) {
        gtk_widget_destroy(interfaces[0].window);
    }
    if (interfaces[1].window != NULL && GTK_IS_WIDGET(interfaces[1].window)) {
        gtk_widget_destroy(interfaces[1].window);
    }

    // allow application to be restarted
    quitApplication = 0;
    stopTimeOuts[0] = 1;
    stopTimeOuts[1] = 1;
    numberOfPlayers = 0;
}

int createWindow(Interface *gui, int player) {
    // initializes player conditions
    gui->player = player;
    gui->waitingForAnswer = FALSE;
    gui->gotCorrectAnswer = FALSE;

    // intializes blank window
    initializeWindow(&(gui->window), player);
    // adds items to window
    addItemsToWindow(gui);
    // shows everything in window
    gtk_widget_show_all(gui->window);
}

// initiate player's window
int initializeWindow(GtkWidget **window, int player) {
    // if not valid player, raise error
    if (player != 1 && player != 2) {
        printf("Error, invalid player number window opened\n");
        return 0;
    }

    // initialize window
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set title
    char buf[50];
    sprintf(buf, "megasenha - player %d", player);
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    // set size and position and connects close window with destroy function
    gtk_window_set_default_size(GTK_WINDOW(*window), 597, 177);
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    if(player == 1) {
        gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()*1/10, gdk_screen_height()/2 - 150);
        gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroy), (gpointer) "1");
    } else {
        gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()*9/10 - 500, gdk_screen_height()/2 - 150);
        gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroy), (gpointer) "2");
    }

    // sets and creates icons for windows and tell windows manager not to put them together
    sprintf(buf, "p%d.png", player);
    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf(buf));
    sprintf(buf, "player %d", player);
    gtk_window_set_wmclass(GTK_WINDOW (*window), buf, "megasenha"); 

    return 1;
}

// generates icon image used by window for task bar
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

void addItemsToWindow(Interface *gui) {
    // creates vertical box to hold everything
    GtkWidget *parentVbox;
    parentVbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentVbox);

    // creates horizontal box to hold timer and hints
    GtkWidget *timerHintsHbox;
    timerHintsHbox = gtk_hbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentVbox), timerHintsHbox, FALSE, FALSE, 0);

    // adds timer, hints and input text boxes
    addTimer(&(gui->timerLabel), timerHintsHbox);
    addHints(gui, timerHintsHbox);
    addTextBox(gui, parentVbox);
}

void addTimer(GtkWidget **label, GtkWidget *parentHbox) {
    // creates timer frame
    GtkWidget *frame;
    frame = gtk_frame_new("Timer");
    gtk_widget_set_size_request (frame, 100, 100);
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, FALSE, FALSE, 0);

    // initializes it with word "Stopped"
    *label = gtk_label_new ("Stopped");
    gtk_container_add (GTK_CONTAINER (frame), *label);
}

void addHints(Interface *gui, GtkWidget *parentHbox) {
    //creates frame to hold hints
    GtkWidget *frame;
    frame = gtk_frame_new("Hints");
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, TRUE, TRUE, 0);

    // creates vertical box to align three hints
    GtkWidget *vbox;
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (frame), vbox);

    // writes "no hints yet" in three labels
    int i;
    for(i=0; i<3; i++) {
        gui->hintsLabel[i] = gtk_label_new ("No hints yet");
        gtk_box_pack_start(GTK_BOX(vbox), gui->hintsLabel[i], TRUE, TRUE, 0);
    }
}

// adds input text box to window
void addTextBox(Interface *gui, GtkWidget *parentVbox) {
    // generates vertical box that holds items
    GtkWidget *vbox;
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentVbox), vbox, FALSE, FALSE, 0);

    //generates input box frame
    GtkWidget *frame;
    frame = gtk_frame_new ("Write word");
    gtk_box_pack_start (GTK_BOX (vbox), frame, FALSE, FALSE, 0);

    //create input box
    createTextBox(gui, frame);
}

void sendText(GtkWidget *widget, gpointer data)
{
    // simplify notation
    Interface *gui = (Interface *) data;
    int numberOfHints = gui->numberOfHints;
    // if already 3 hints over or time done do nothing
    if(numberOfHints > 3 || !gui->waitingForAnswer) {
        return;
    }

    // get answer from entry box
    char *answer = (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox));

    // checks if right answer
    if(strcmp(answer, gui->wordAndHints.word) != 0) { 
        // show new hint if less than three so far or set to not waiting player anymore
        if(numberOfHints < 3) {
            updateHintLabel(&(gui->hintsLabel[numberOfHints]), gui->wordAndHints.hints[numberOfHints]);
        } else {
            gui->waitingForAnswer = FALSE;
        }
        // if wrong increase number of hints used
        gui->numberOfHints++;
    // if correct set player to no more waitingand got correct answer
    } else {
        gui->waitingForAnswer = FALSE;
        gui->gotCorrectAnswer = TRUE;
    }

    // empty entry box
    g_print ("Player sent value \"%s\"\n", (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox)));
    gtk_entry_set_text (GTK_ENTRY(gui->inputTextBox), "");
}

void createTextBox(Interface *gui, GtkWidget *frame)
{
    // creates horizontal box to hold text box and enter button
    GtkWidget *hbox;
    hbox = gtk_hbox_new(FALSE, 0);

    // creates input box and binds enter key (activate) to sendText function
    gui->inputTextBox = gtk_entry_new();
    gtk_entry_set_text (GTK_ENTRY (gui->inputTextBox), "");
    gtk_box_pack_start (GTK_BOX (hbox), gui->inputTextBox, TRUE, TRUE, 0);
    gtk_signal_connect(GTK_OBJECT(gui->inputTextBox), "activate", GTK_SIGNAL_FUNC(sendText), (gpointer) gui);

    // creates enter button and binds click to sendText function
    GtkWidget *button;
    button = gtk_button_new_with_label("Enter");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(sendText), (gpointer) gui);

    gtk_container_add(GTK_CONTAINER(frame), hbox);
}

void updateTimerLabel (GtkWidget **label, double timePassed) {
    //calculates remaining time
    char buf[50], *color;
    int remainingTime = 15-timePassed;

    // if less than five seconds left print red, else blue
    if(remainingTime <= 5) {
        color = "red";
    } else {
        color = "blue";
    }

    sprintf(buf, "<span foreground=\"%s\" font=\"25\">%d</span>", color, remainingTime);

    // if time over and wrong answer print red, if right answer print OK! in green
    if(remainingTime == 0) {
        color = "red";
        sprintf(buf, "<span foreground=\"%s\" font=\"42.5\">%s</span>", color, "X");
    }
    if(remainingTime == -5) {
        color = "green";
        sprintf(buf, "<span foreground=\"%s\" font=\"30\">%s</span>", color, "OK!");
        remainingTime = 0;
    }

    // sets timer text
    gtk_label_set_markup(GTK_LABEL(*label), buf);
    gtk_widget_show(*label);
}

gboolean timerHandler(Interface *gui) {
    // if application quit or stop time outs is on, return false to stop time out
    if(quitApplication || stopTimeOuts[gui->player - 1] ) {
        stopTimeOuts[gui->player - 1] = 0;
        return FALSE;
    }

    // gets difference between current and start time
    time_t now;
    double timePassed;
    now = time(NULL);
    timePassed = difftime(now, gui->startTime);

    // if not waiting for answer anymore set time to 0 or (if answer was correct) -5
    if(!gui->waitingForAnswer) {
        timePassed = 15;
        if(gui->gotCorrectAnswer) {
            timePassed = 20;
        }
    }

    // update timer
    updateTimerLabel(&(gui->timerLabel), timePassed);

    // if time over stop timeouts
    if(timePassed >= 15) {
        gui->waitingForAnswer = FALSE;
        return FALSE;
    }
    return TRUE;
}

void startTimer(Interface *gui) {
    // if stop time outs is on but there's no timeout running, set it to false
    if(stopTimeOuts[gui->player - 1] ) {
        stopTimeOuts[gui->player - 1] = 0;
    }
    // sets starting time to current
    gui->startTime = time(NULL);
    
    // starts timeout to update timer every second and updates timerLabel to full time
    g_timeout_add(1000, (GSourceFunc) timerHandler, (gpointer) gui);
    updateTimerLabel(&(gui->timerLabel), 0);
}

void updateHintLabel (GtkWidget **label, char *newHint) {
    // updates hint label in blue to new hint
    char buf[50];
    sprintf(buf, "<span foreground=\"blue\" font=\"20\">%s</span>", newHint);

    gtk_label_set_markup(GTK_LABEL(*label), buf);
}

void restartHints (Interface *gui, wordAndHints newWordAndHint) {
    // restarts player stats for hints
    gui->waitingForAnswer = TRUE;
    gui->gotCorrectAnswer = FALSE;
    gui->wordAndHints = newWordAndHint;
    gui->numberOfHints = 1;

    // updates first hint to new first and hides other two
    updateHintLabel(&(gui->hintsLabel[0]), newWordAndHint.hints[0]);
    updateHintLabel(&(gui->hintsLabel[1]), "---");
    updateHintLabel(&(gui->hintsLabel[2]), "---");
}

int newWord(int player, wordAndHints newWordAndHint) {
    // brings player window to front and set focus to text entry box
    gtk_widget_grab_focus(interfaces[player-1].inputTextBox);
    gtk_window_present (GTK_WINDOW(interfaces[player-1].window));
    // restarts interface (hint, timer and entry box)
    gtk_entry_set_text (GTK_ENTRY(interfaces[player-1].inputTextBox), "");
    restartHints(&interfaces[player-1], newWordAndHint); 
    startTimer(&interfaces[player-1]);
    restartHints(&interfaces[player-1], newWordAndHint); 
    startTimer(&interfaces[player-1]);
}

int updateInterface(void) {
    //while changes to do and application hasn't been closed update
    while (!quitApplication && gtk_events_pending ()) {
        gtk_main_iteration ();
    }

    // return if application still working
    return !quitApplication;
}

// returns true if any player still guessing
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

// -1 if no correct answer, number of used hints otherwise
int getPlayerScore(int player) {
    if(interfaces[player-1].gotCorrectAnswer) {
        return interfaces[player-1].numberOfHints;
    } else {
        return -1;
    }
}

// creates info window
int createInfoWindow(InfoInterface *infoGui) {
    // initializes blank info window
    initializeInfoWindow(&(infoGui->window));
    // adds items to window
    addItemsToInfoWindow(infoGui);
    // shows everything in window
    gtk_widget_show_all(infoGui->window);
}

// initiate info window
int initializeInfoWindow(GtkWidget **window) {
    // initialize window
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set title
    char buf[50];
    sprintf(buf, "megasenha - info window");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    // set size and position and connects close window with destroy function
    gtk_window_set_default_size(GTK_WINDOW(*window), 797, 107);
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 797/2, gdk_screen_height()*1/20);
//    gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroy), (gpointer) "1");

    // sets and creates icons for windows and tell windows manager not to put them together
    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg"));
    gtk_window_set_wmclass(GTK_WINDOW (*window), "infoWindow", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

void addItemsToInfoWindow(InfoInterface *gui) {
    // creates horizontal box to hold everything
    GtkWidget *parentHbox;
    parentHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentHbox);

    // adds timer, hints and input text boxes
    addPlayer(&(gui->playerLabel), parentHbox);
    addInfoLabel(gui, parentHbox);
    addQuitButton(gui, parentHbox);
}

void addInfoLabel(InfoInterface *gui, GtkWidget *parentVbox) {

    //creates frame to hold hints
    GtkWidget *frame;
    frame = gtk_frame_new("Info");
    gtk_box_pack_start(GTK_BOX(parentVbox), frame, TRUE, TRUE, 0);

    // writes "no info yet" in labels
    gui->infoLabel = gtk_label_new ("No info yet");
    gtk_container_add (GTK_CONTAINER (frame), gui->infoLabel);
}

void addPlayer(GtkWidget **label, GtkWidget *parentHbox) {
    // creates timer frame
    GtkWidget *frame;
    frame = gtk_frame_new("Player");
    gtk_widget_set_size_request (frame, 100, 100);
    gtk_box_pack_start(GTK_BOX(parentHbox), frame, FALSE, FALSE, 0);

    // initializes it with word "Stopped"
    *label = gtk_label_new ("None");
    gtk_container_add (GTK_CONTAINER (frame), *label);
}

// adds input text box to window
void addQuitButton(InfoInterface *gui, GtkWidget *parentHbox) {
    //generates input box frame
    GtkWidget *frame;
    frame = gtk_frame_new ("Surrender");
    gtk_box_pack_start (GTK_BOX (parentHbox), frame, FALSE, FALSE, 0);

    // creates give up button
    GtkWidget *button;
    button = gtk_button_new_with_label("Give up");
    gtk_container_add (GTK_CONTAINER (frame), button);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(quitGame), (gpointer) gui);
}

void quitGame(GtkWidget *widget, gpointer data)
{
    // simplify notation
    InfoInterface *gui = (InfoInterface *) data;

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

    // show that player gave up
    updateInfoLabel("Player gave up!", "red");
    playerGaveUp = 1;
    g_print ("Player %d gave up\n", playerPlaying);
}

void updateInfoLabel (char *newInfo, char *color) {
    // updates hint label in blue to new hint
    char buf[150];
    sprintf(buf, "<span foreground=\"%s\" font=\"20\">%s</span>", color, newInfo);

    gtk_label_set_markup(GTK_LABEL(infoInterface.infoLabel), buf);
}

void updatePlayerLabel (int newPlayer) {
    // updates hint label in blue to new hint
    char buf[50];
    sprintf(buf, "<span foreground=\"green\" font=\"40\">%d</span>", newPlayer);

    gtk_label_set_markup(GTK_LABEL(infoInterface.playerLabel), buf);
}

int gaveUp() {
    return playerGaveUp;
}

void startGetNameInterface() {
    // intializes blank window
    initializeGetNameWindow(&(getNameInterface.window));
    // adds items to window
    addItemsToGetNameWindow(&getNameInterface);
    // shows everything in window
    gtk_widget_show_all(getNameInterface.window);
}

// initiate get name window
int initializeGetNameWindow(GtkWidget **window) {
    // initialize window
    *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // set title
    char buf[50];
    sprintf(buf, "megasenha - type your name");
    gtk_window_set_title(GTK_WINDOW(*window), buf);

    // set size and position and connects close window with destroy function
    gtk_window_set_default_size(GTK_WINDOW(*window), 397, 107);
    gtk_container_set_border_width (GTK_CONTAINER (*window), 10);
    gtk_window_move(GTK_WINDOW(*window), gdk_screen_width()/2 - 397/2, gdk_screen_height()*9/20);
//    gtk_signal_connect (GTK_OBJECT(*window), "destroy", GTK_SIGNAL_FUNC (destroy), (gpointer) "1");

    // sets and creates icons for windows and tell windows manager not to put them together
    gtk_window_set_icon(GTK_WINDOW(*window), createPixbuf("info.jpg"));
    gtk_window_set_wmclass(GTK_WINDOW (*window), "infoWindow", "megasenha"); 

    gtk_widget_show_all(*window);

    return 1;
}

void addItemsToGetNameWindow(GetNameInterface *gui) {
    // creates horizontal box to hold everything
    GtkWidget *parentHbox;
    parentHbox = gtk_hbox_new(FALSE, 0);
    gtk_container_add (GTK_CONTAINER (gui->window), parentHbox);

    // adds timer, hints and input text boxes
    addGetNameTextBox(gui, parentHbox);
}

// adds input text box to get name window
void addGetNameTextBox(GetNameInterface *gui, GtkWidget *parentHbox) {
    // generates vertical box that holds items
    GtkWidget *vbox;
    vbox = gtk_vbox_new(FALSE, 0);
    gtk_box_pack_start(GTK_BOX(parentHbox), vbox, FALSE, FALSE, 0);

    //generates input box frame
    GtkWidget *frame;
    frame = gtk_frame_new ("Write your name");
    gtk_box_pack_start (GTK_BOX (parentHbox), frame, TRUE, TRUE, 0);

    //create input box
    createGetNameTextBox(gui, frame);
}

void createGetNameTextBox(GetNameInterface *gui, GtkWidget *frame)
{
    // creates horizontal box to hold text box and enter button
    GtkWidget *hbox;
    hbox = gtk_hbox_new(FALSE, 0);

    // creates input box and binds enter key (activate) to sendText function
    gui->inputTextBox = gtk_entry_new();
    gtk_entry_set_text (GTK_ENTRY (gui->inputTextBox), "");
    gtk_box_pack_start (GTK_BOX (hbox), gui->inputTextBox, TRUE, TRUE, 0);
    gtk_signal_connect(GTK_OBJECT(gui->inputTextBox), "activate", GTK_SIGNAL_FUNC(sendName), (gpointer) gui);

    // creates enter button and binds click to sendText function
    GtkWidget *button;
    button = gtk_button_new_with_label("Enter");
    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);
    gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(sendName), (gpointer) gui);

    gtk_container_add(GTK_CONTAINER(frame), hbox);
}

void sendName(GtkWidget *widget, gpointer data)
{
    // simplify notation
    GetNameInterface *gui = (GetNameInterface *) data;
    
    // get name from entry box
    gui->name = (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox));

    // checks if right answer and if yes, sets player name as received
    if(strcmp(gui->name, "") != 0) { 
        gui->gotName = 1;
    }

    // print player name
    g_print ("Player sent value \"%s\"\n", (char *) gtk_entry_get_text(GTK_ENTRY(gui->inputTextBox)));
}

char *getName()
{
    return getNameInterface.name;
}

int updateGetName()
{
    if(getNameInterface.gotName)
        return 0;

    gtk_main_iteration ();
    return 1;
}
