#include <gtk/gtk.h>
#include "arena.h"
#include "gtk_utils.h"


//'a' key: Attacking
//'h' key: Hurting
//'d' key: Dying
//'w' key: Walking
//'r' key: Running
//'s' key: Standing



#define SPRITE_WIDTH (256)
#define SPRITE_HEIGHT (2560/10)
#define NUM_STANDING_FRAMES 6
#define NUM_WALKING_FRAMES 8
#define NUM_RUNNING_FRAMES 8
#define NUM_ATTACKING1_FRAMES 4
#define NUM_ATTACKING2_FRAMES 5
#define NUM_ATTACKING3_FRAMES 4
#define NUM_DEFENDING_FRAMES 2
#define NUM_JUMPING_FRAMES 8
#define NUM_HURTING_FRAMES 3
#define NUM_DYING_FRAMES 6

GtkImage *gladiator_image;
GdkPixbuf *sprite_sheet;
int current_frame = 0;
int current_action = 0;
int action_frames[] = {NUM_STANDING_FRAMES, NUM_WALKING_FRAMES, NUM_RUNNING_FRAMES, NUM_ATTACKING1_FRAMES, NUM_ATTACKING2_FRAMES,NUM_ATTACKING3_FRAMES ,NUM_DEFENDING_FRAMES,NUM_JUMPING_FRAMES,NUM_HURTING_FRAMES,NUM_DYING_FRAMES};
int gladiator_x = 0; // Initial position of the gladiator

GtkWidget *life_image_player1; // Image widget for player 1 life
GtkWidget *life_image_player2; // Image widget for player 2 life
GtkWidget *time_image;
GtkWidget *table_time_image;



GtkWidget *button_start;
GtkWidget *button_create;
GtkWidget *button_exit;



// Global variable to store the selected player
Player *selected_player = NULL;

//---------------------------------------------------





// Callback for button click events
void on_select_button_clicked(GtkWidget *button, gpointer data) {
    Player *player = (Player *)data;
    selected_player = player;
    g_print("Selected player: %s\n", player->name);  // Print the selected player name for verification
}

void on_button_clicked(GtkWidget *button, gpointer data) {
    const char *button_label = gtk_button_get_label(GTK_BUTTON(button));
    if (g_strcmp0(button_label, "Start") == 0) {
        if (selected_player) {
            g_print("Starting the game with %s\n", selected_player->name);
            run_game(selected_player);  // Call run_game with the selected player
        } else {
            g_print("No player selected!\n");
        }
    } else if (g_strcmp0(button_label, "CREATE GLADIATOR") == 0) {
        g_print("Create Gladiator clicked\n");
        // Code to create a new gladiator
    } else if (g_strcmp0(button_label, "EXIT") == 0) {
        g_print("Exit clicked\n");
        gtk_main_quit();
    }
}

void play_audio(const char *file_path) {
    // Open the audio file
    if (PlaySound(file_path, NULL, SND_FILENAME | SND_ASYNC) == 0) {
        // Error handling if the audio file fails to play
        printf("Error playing audio: %d\n", GetLastError());
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the character selection window
    GtkWidget *window = create_window("Character Selection", 800, 600);

    // Create a fixed container
    GtkWidget *fixed = create_fixed();
    GtkWidget *background_image = NULL;
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Set the initial background image
    update_background_image(fixed, &background_image, "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Menu.jpg");



    // Get the width and height of the background image
    GdkPixbuf *background_image_pixbuf = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Menu.jpg", NULL);
    gint background_image_width = gdk_pixbuf_get_width(background_image_pixbuf);
    gint background_image_height = gdk_pixbuf_get_height(background_image_pixbuf);

    // Create player data
    Player players[3] = {
            {1, "Samuri", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\vector1.png", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Samurai_Spritelist.png",100, 50, 30, "Special 1"},
            {2, "Fire vizard", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\vector2.png", NULL,120, 40, 40, "Special 2"},
            {3, "Knight", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\vector3.png", NULL,80, 60, 20, "Special 3"}
    };

    // Create the player selection UI
    GtkWidget *list_cards = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\list_card.png");
    gtk_fixed_put(GTK_FIXED(fixed), list_cards, 0, background_image_height / 10);


    GtkWidget *player1 = gtk_image_new_from_file(players[0].imageURL);
    GtkWidget *player2 = gtk_image_new_from_file(players[1].imageURL);
    GtkWidget *player3 = gtk_image_new_from_file(players[2].imageURL);

    gtk_fixed_put(GTK_FIXED(fixed), player1, 140, background_image_height / 3);
    gtk_fixed_put(GTK_FIXED(fixed), player2, background_image_width / 6 + 140, background_image_height / 3 );
    gtk_fixed_put(GTK_FIXED(fixed), player3, background_image_width / 3 + 140, background_image_height / 3 );



    GtkWidget *card_player1 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Civilian_card.png");
    GtkWidget *card_player2 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Civilian_card.png");
    GtkWidget *card_player3 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Civilian_card.png");

    gtk_fixed_put(GTK_FIXED(fixed), card_player1, 100, background_image_height / 3 - 20);
    gtk_fixed_put(GTK_FIXED(fixed), card_player2, background_image_width / 6 + 100, background_image_height / 3 - 20);
    gtk_fixed_put(GTK_FIXED(fixed), card_player3, background_image_width / 3 + 100, background_image_height / 3 - 20);

    GtkWidget *player1_message = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\message.png");
    GtkWidget *player2_message = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\message.png");
    GtkWidget *player3_message = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\message.png");

    gtk_fixed_put(GTK_FIXED(fixed), player1_message, 80, background_image_height / 4);
    gtk_fixed_put(GTK_FIXED(fixed), player2_message, background_image_width / 6 + 60, background_image_height / 4);
    gtk_fixed_put(GTK_FIXED(fixed), player3_message, background_image_width / 3 + 50, background_image_height / 4);


    GtkWidget *button_select_player1 = create_button("select", "custom-button-player1");
    GtkWidget *button_select_player2 = create_button("select", "custom-button-player2");
    GtkWidget *button_select_player3 = create_button("select", "custom-button-player3");

    gtk_fixed_put(GTK_FIXED(fixed), button_select_player1, 150, background_image_height - 280);
    gtk_fixed_put(GTK_FIXED(fixed), button_select_player2, background_image_width / 6 + 150, background_image_height - 280);
    gtk_fixed_put(GTK_FIXED(fixed), button_select_player3, background_image_width / 3 + 150, background_image_height - 280);

    g_signal_connect(button_select_player1, "clicked", G_CALLBACK(on_select_button_clicked), &players[0]);
    g_signal_connect(button_select_player2, "clicked", G_CALLBACK(on_select_button_clicked), &players[1]);
    g_signal_connect(button_select_player3, "clicked", G_CALLBACK(on_select_button_clicked), &players[2]);


    GtkWidget *message_player1 = create_label("Our destiny \n awaits us", "DRAGON HUNTER 12", "black");
    GtkWidget *message_player2 = create_label("Courage will \n guide us.", "DRAGON HUNTER 12", "black");
    GtkWidget *message_player3 = create_label("Faith leads \n the way.", "DRAGON HUNTER 12", "black");

    gtk_fixed_put(GTK_FIXED(fixed), message_player1, 100, background_image_height / 4 + 50);
    gtk_fixed_put(GTK_FIXED(fixed), message_player2, background_image_width / 6 + 90, background_image_height / 4 + 50);
    gtk_fixed_put(GTK_FIXED(fixed), message_player3, background_image_width / 3 + 80, background_image_height / 4 + 50);

    GtkWidget *label_player1 = create_label("Nom: Samuri\nPV: 100\nAttaque: 50\nDefense: 30\nSpecial Capacity: ", "DRAGON HUNTER 12", "black");
    GtkWidget *label_player2 = create_label("Nom: Fire vizard\nPV: 120\nAttaque: 40\nDefense: 40\nSpecial Capacity: ", "DRAGON HUNTER 12", "black");
    GtkWidget *label_player3 = create_label("Nom: Knight\nPV: 80\nAttaque: 60\nDefense: 20\nSpecial Capacity: ", "DRAGON HUNTER 12", "black");

    gtk_fixed_put(GTK_FIXED(fixed), label_player1, 150, background_image_height / 3 + 270);
    gtk_fixed_put(GTK_FIXED(fixed), label_player2, background_image_width / 6 + 150, background_image_height / 3 + 270);
    gtk_fixed_put(GTK_FIXED(fixed), label_player3, background_image_width / 3 + 150, background_image_height / 3 + 270);

    button_start = create_button("Start", NULL);
    button_create = create_button("CREATE GLADIATOR", NULL);
    button_exit = create_button("EXIT", NULL);

    gtk_fixed_put(GTK_FIXED(fixed), button_start, background_image_width - 350, background_image_height - 350);
    gtk_fixed_put(GTK_FIXED(fixed), button_create, background_image_width - 350, background_image_height - 275);
    gtk_fixed_put(GTK_FIXED(fixed), button_exit, background_image_width - 350, background_image_height - 200);

    g_signal_connect(button_start, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button_create, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button_exit, "clicked", G_CALLBACK(on_button_clicked), NULL);

    GtkWidget *label = create_label("Select your Vector", "Ranger Eastwood 48", "black");
    gtk_fixed_put(GTK_FIXED(fixed), label, background_image_width / 7, background_image_height / 5);

    set_css_styles();
    gtk_widget_show_all(window);

    play_sound("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\GameMusic.wav");
    gtk_main();

    return 0;
}

































//    // Create buttons for different actions
//    GtkWidget *button_standing = gtk_button_new_with_label("Standing");
//    GtkWidget *button_running = gtk_button_new_with_label("Running");
//    GtkWidget *button_attacking = gtk_button_new_with_label("Attacking");
//    GtkWidget *button_hurting = gtk_button_new_with_label("Hurting");
//    GtkWidget *button_dying = gtk_button_new_with_label("Dying");
//    GtkWidget *button_walking = gtk_button_new_with_label("Walking");
//
//    // Connect button signals to the button_clicked function
//    g_signal_connect(button_standing, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(5));
//    g_signal_connect(button_running, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(4));
//    g_signal_connect(button_attacking, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(0));
//    g_signal_connect(button_hurting, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(2));
//    g_signal_connect(button_dying, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(1));
//    g_signal_connect(button_walking, "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(3));

// Create a horizontal box to hold the buttons
//    GtkWidget *button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);

//    // Add the buttons to the button box
//    gtk_container_add(GTK_CONTAINER(button_box), button_standing);
//    gtk_container_add(GTK_CONTAINER(button_box), button_running);
//    gtk_container_add(GTK_CONTAINER(button_box), button_attacking);
//    gtk_container_add(GTK_CONTAINER(button_box), button_hurting);
//    gtk_container_add(GTK_CONTAINER(button_box), button_dying);
//    gtk_container_add(GTK_CONTAINER(button_box), button_walking);
// Add the main box to the window