#include <gtk/gtk.h>
#include "arena.h"
#include "window.h"
#include "label.h"


//'a' key: Attacking
//'h' key: Hurting
//'d' key: Dying
//'w' key: Walking
//'r' key: Running
//'s' key: Standing



#define SPRITE_WIDTH (3072/10)
#define SPRITE_HEIGHT (1026/6)
#define NUM_STANDING_FRAMES 10
#define NUM_RUNNING_FRAMES 10
#define NUM_WALKING_FRAMES 10
#define NUM_ATTACKING_FRAMES 10
#define NUM_HURTING_FRAMES 10
#define NUM_DYING_FRAMES 10

GtkImage *gladiator_image;
GdkPixbuf *sprite_sheet;
int current_frame = 0;
int current_action = 5;
int action_frames[] = {NUM_ATTACKING_FRAMES, NUM_DYING_FRAMES, NUM_HURTING_FRAMES, NUM_WALKING_FRAMES, NUM_RUNNING_FRAMES, NUM_STANDING_FRAMES};
int gladiator_x = 0; // Initial position of the gladiator

GtkWidget *life_image_player1; // Image widget for player 1 life
GtkWidget *life_image_player2; // Image widget for player 2 life
GtkWidget *time_image;
GtkWidget *table_time_image;


GtkWidget *card_player1; // Image widget for player 1 life
GtkWidget *card_player2; // Image widget for player 2 life
GtkWidget *card_player3;

GtkWidget *player1; // Image widget for player 1 life
GtkWidget *player2; // Image widget for player 2 life
GtkWidget *player3;

GtkWidget *button_select_player1; // Image widget for player 1 life
GtkWidget *button_select_player2; // Image widget for player 2 life
GtkWidget *button_select_player3;

GtkWidget *button_start;
GtkWidget *button_create;
GtkWidget *button_exit;

int game_started = 0 ;
// Structure to hold player data
typedef struct {
    int id;
    const char *name;
    const char *imageURL;
    int PV;
    int Attack;
    int Defense;
    const char *specialCapacity;
} Player;

GtkWidget *create_fixed()
{
    GtkFixed *fixed = GTK_FIXED(gtk_fixed_new());
    return ((GtkWidget*)fixed);
}


void on_button_clicked(GtkWidget *widget, gpointer data) {
    if (widget == button_start) {
        g_print("Continuer jeux\n");
        game_started = 1 ;
        // Add your code for continuing the game here
    } else if (widget == button_create) {
        g_print("Nouvelle session\n");
        // Add your code for starting a new game session here
    } else if (widget == button_exit) {
        g_print("Quitter jeux\n");
        gtk_main_quit();
    }
}


//int main(int argc, char *argv[]) {
//    // Initialize GTK
//    gtk_init(NULL, NULL);
//    GtkCssProvider *provider;
//    GdkScreen *screen;
//    GdkDisplay *display;
//
//
//    // Create the character selection window
//    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//    gtk_window_set_title(GTK_WINDOW(window), "Character Selection");
//    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
//    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
//
//    // Create a fixed container to hold the background image
//    GtkWidget *fixed = gtk_fixed_new();
//
//    // Create an image widget for the character selection background
//    GtkWidget *background_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Menu.jpg");
//    gtk_widget_set_size_request(background_image, 800, 600);
//    gtk_fixed_put(GTK_FIXED(fixed), background_image, 0, 0);
//
//    GdkPixbuf *background_image_pixbuf = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Menu.jpg", NULL);
//    gint background_image_width = gdk_pixbuf_get_width(background_image_pixbuf);
//    gint background_image_height = gdk_pixbuf_get_height(background_image_pixbuf);
//
//    Player players[3] = {
//            {1, "Player 1", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\1_knight.png", 100, 50, 30, "Special 1"},
//            {2, "Player 2", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\2_knight.png", 120, 40, 40, "Special 2"},
//            {3, "Player 3", "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\3_knight.png", 80, 60, 20, "Special 3"}
//    };
//    // Add the fixed container to the window
//    gtk_container_add(GTK_CONTAINER(window), fixed);
//
//    GtkWidget *list_cards = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\list_card.png");
//    gtk_fixed_put(GTK_FIXED(fixed), list_cards, 0, background_image_height / 10);
//
//    // Create image widgets for player cards
//    card_player1 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\card.png");
//    card_player2 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\card.png");
//    card_player3 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\card.png");
//
//    // Add the player cards to the fixed container
//    gtk_fixed_put(GTK_FIXED(fixed), card_player1, 100, background_image_height / 3);
//    gtk_fixed_put(GTK_FIXED(fixed), card_player2, background_image_width / 6 + 100, background_image_height / 3);
//    gtk_fixed_put(GTK_FIXED(fixed), card_player3, background_image_width / 3 + 100, background_image_height / 3);
//
//    // select me buttons
//
//    // my buttons
//    button_select_player1 = gtk_button_new_with_label("select");
//    button_select_player2 = gtk_button_new_with_label("select");
//    button_select_player3 = gtk_button_new_with_label("select");
//
//    // Assign custom CSS classes to the buttons
//    gtk_widget_set_name(button_select_player1, "custom-button-player1");
//    gtk_widget_set_name(button_select_player2, "custom-button-player2");
//    gtk_widget_set_name(button_select_player3, "custom-button-player3");
//
//    gtk_fixed_put(GTK_FIXED(fixed), button_select_player1, 150, background_image_height - 280);
//    gtk_fixed_put(GTK_FIXED(fixed), button_select_player2, background_image_width / 6 + 150, background_image_height -280);
//    gtk_fixed_put(GTK_FIXED(fixed), button_select_player3, background_image_width / 3 + 150, background_image_height -280);
//
//
//    // Create image widgets for players
//    player1 = gtk_image_new_from_file(players[0].imageURL);
//    player2 = gtk_image_new_from_file(players[1].imageURL);
//    player3 = gtk_image_new_from_file(players[2].imageURL);
//
//    // Add the players to the fixed container
//    gtk_fixed_put(GTK_FIXED(fixed), player1, 150, background_image_height / 3);
//    gtk_fixed_put(GTK_FIXED(fixed), player2, background_image_width / 6 + 140, background_image_height / 3 + 30);
//    gtk_fixed_put(GTK_FIXED(fixed), player3, background_image_width / 3 + 130, background_image_height / 3 + 30);
//
//    // each player thinking
//    GtkWidget *player1_message = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\message.png");
//    GtkWidget *player2_message = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\message.png");
//    GtkWidget *player3_message = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\message.png");
//
//    // Add the players to the fixed container
//    gtk_fixed_put(GTK_FIXED(fixed), player1_message, 50, background_image_height / 4);
//    gtk_fixed_put(GTK_FIXED(fixed), player2_message, background_image_width / 6 + 40, background_image_height / 4 );
//    gtk_fixed_put(GTK_FIXED(fixed), player3_message, background_image_width / 3 + 30, background_image_height / 4 );
//
//    // labels for the messages
//    // Create labels for player characteristics
//    GtkWidget *message_player1 = gtk_label_new(" Our destiny \n awaits us");
//    GtkWidget *message_player2 = gtk_label_new("Courage will \n guide us. ");
//    GtkWidget *message_player3 = gtk_label_new(" Faith leads \n the way. ");
//
//    // Set the font for the labels
//    PangoFontDescription *font_desc = pango_font_description_from_string("DRAGON HUNTER 12");
//    gtk_widget_override_font(message_player1, font_desc);
//    gtk_widget_override_font(message_player2, font_desc);
//    gtk_widget_override_font(message_player3, font_desc);
//
//    // Set the text color to white
//    GdkRGBA color;
//    gdk_rgba_parse(&color, "black");
//    gtk_widget_override_color(message_player1, GTK_STATE_FLAG_NORMAL, &color);
//    gtk_widget_override_color(message_player2, GTK_STATE_FLAG_NORMAL, &color);
//    gtk_widget_override_color(message_player3, GTK_STATE_FLAG_NORMAL, &color);
//
//    // Add the labels to the fixed container
//    gtk_fixed_put(GTK_FIXED(fixed), message_player1, 70, background_image_height / 4 +50);
//    gtk_fixed_put(GTK_FIXED(fixed), message_player2, background_image_width / 6 + 70, background_image_height / 4 +50);
//    gtk_fixed_put(GTK_FIXED(fixed), message_player3, background_image_width / 3 + 60, background_image_height / 4 +50);
//
//    // Create labels for player characteristics
//    GtkWidget *label_player1 = gtk_label_new(" Nom: Player 1\n PV: 100\n Attaque: 50\n Defense: 30\n special Capacity: ");
//    GtkWidget *label_player2 = gtk_label_new(" Nom: Player 2\n PV: 120\n Attaque: 40\n Defense: 40\n special Capacity: ");
//    GtkWidget *label_player3 = gtk_label_new(" Nom: Player 3\n PV: 80\n Attaque: 60\n Defense: 20\n special Capacity: ");
//
//    // Set the font for the labels
//    font_desc = pango_font_description_from_string("DRAGON HUNTER 12");
//    gtk_widget_override_font(label_player1, font_desc);
//    gtk_widget_override_font(label_player2, font_desc);
//    gtk_widget_override_font(label_player3, font_desc);
//
//    // Set the text color to white
//
//    gdk_rgba_parse(&color, "white");
//    gtk_widget_override_color(label_player1, GTK_STATE_FLAG_NORMAL, &color);
//    gtk_widget_override_color(label_player2, GTK_STATE_FLAG_NORMAL, &color);
//    gtk_widget_override_color(label_player3, GTK_STATE_FLAG_NORMAL, &color);
//
//    // Add the labels to the fixed container
//    gtk_fixed_put(GTK_FIXED(fixed), label_player1, 130, background_image_height / 3 + 280);
//    gtk_fixed_put(GTK_FIXED(fixed), label_player2, background_image_width / 6 + 130, background_image_height / 3 + 280);
//    gtk_fixed_put(GTK_FIXED(fixed), label_player3, background_image_width / 3 + 130, background_image_height / 3 + 280);
//
//
//    // my buttons
//    button_start = gtk_button_new_with_label("Start");
//    button_create = gtk_button_new_with_label("CREATE GLADIATOR");
//    button_exit = gtk_button_new_with_label("EXITE");
//
//
//    gtk_fixed_put(GTK_FIXED(fixed), button_start, background_image_width  - 350, background_image_height -350);
//    gtk_fixed_put(GTK_FIXED(fixed), button_create, background_image_width  - 350, background_image_height -275);
//    gtk_fixed_put(GTK_FIXED(fixed), button_exit, background_image_width  - 350, background_image_height -200 );
//
//    // Connect button signals
//    g_signal_connect(button_start, "clicked", G_CALLBACK(on_button_clicked), NULL);
//    g_signal_connect(button_create, "clicked", G_CALLBACK(on_button_clicked), NULL);
//    g_signal_connect(button_exit, "clicked", G_CALLBACK(on_button_clicked), NULL);
//
//    // Create a label for the text
//    GtkWidget *label = gtk_label_new("Select your Vector");
//
//    // Set the font for the label
//    PangoFontDescription *font_desc_label = pango_font_description_from_string("Ranger Eastwood 48");
//    gtk_widget_override_font(label, font_desc_label);
//
//    // Set the text color to white
//    GdkRGBA color_label;
//    gdk_rgba_parse(&color_label, "black");
//    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &color_label);
//
//
//    provider = gtk_css_provider_new ();
//    display = gdk_display_get_default ();
//    screen = gdk_display_get_default_screen (display);
//
//    gtk_css_provider_load_from_data(provider,
//                                    " button {"
//                                    "   border: 1px solid #7c7c7c;"
//                                    "   border-radius: 15px;"
//                                    "   font: Ranger Eastwood 36;"
//                                    "   color: #543c1c;"
//                                    "   background-color: #e4d3aa;"
//                                    "   background-image: none;"
//                                    "   min-width: 280px;"
//                                    "   text-align: center;"
//                                    "   padding: 10px 20px;"
//                                    "}"
//                                    " button:hover {"
//                                    "   background-color: #fff7d7;"
//                                    "   color: #ffffff;"
//                                    "}"
//                                    " button:hover:active {"
//                                    "   background-color: #e8a154;"
//                                    "   color: #ffffff;"
//                                    "}"
//                                    /* Additional styles for specific buttons */
//                                    " button#custom-button-player1 {"
//                                    "   border-color: #00ff00;"
//                                    "   min-width: 150px;"
//                                    "   padding: 5px 10px;"
//                                    "}"
//                                    " button#custom-button-player2 {"
//                                    "   border-color: #00ff00;"
//                                    "   min-width: 150px;"
//                                    "   padding: 5px 10px;"
//                                    "}"
//                                    " button#custom-button-player3 {"
//                                    "   border-color: #00ff00;"
//                                    "   min-width: 150px;"
//                                    "   padding: 5px 10px;"
//                                    "}"
//                                   ,
//                                    -1,
//                                    NULL);
//    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);
//    g_object_unref (provider);
//
//    // Add the label to the fixed container
//    gtk_fixed_put(GTK_FIXED(fixed), label, background_image_width / 7, background_image_height / 5);
//
//
//
//
//    // Show the window
//    gtk_widget_show_all(window);
//
//
//    // Start the GTK main loop
//    gtk_main();
//
//    return 0;
//}











int main(int argc, char *argv[]) {
    run_game();
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