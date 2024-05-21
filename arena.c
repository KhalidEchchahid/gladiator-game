
#include "arena.h"
#include "player.h"
#include "gtk_utils.h" // Include the utility functions header


gboolean is_paused = FALSE;

// Global variable for the label widget
GtkWidget *time_label;



void toggle_pause(GtkWidget *widget, gpointer data) {
    is_paused = !is_paused;

    if (is_paused) {
        gtk_button_set_label(GTK_BUTTON(widget), "Play");
    } else {
        gtk_button_set_label(GTK_BUTTON(widget), "Pause");
    }
}


gboolean update_animation(gpointer data) {
    if (is_paused) {
        return TRUE;
    }
    // Calculate the coordinates of the current frame in the sprite sheet
    int x = (current_frame % action_frames[current_action]) * SPRITE_WIDTH;
    int y = current_action * SPRITE_HEIGHT;

    // Crop the sprite sheet to display only the current frame
    GdkPixbuf *frame = gdk_pixbuf_new_subpixbuf(sprite_sheet, x, y, SPRITE_WIDTH, SPRITE_HEIGHT);

    // Update the image widget with the current frame
    gtk_image_set_from_pixbuf(gladiator_image, frame);
    gtk_fixed_move(GTK_FIXED(data), gladiator_image, gladiator_x, 450);

    // Increment the frame counter and loop back to the beginning if necessary
    current_frame++;
    if (current_frame >= action_frames[current_action]) {
        current_frame = 0;
    }



    // If the gladiator reaches the right edge of the arena, reset its position to the left
    if (!(gladiator_x >= 1900 - SPRITE_WIDTH)) {
        // Move the gladiator to the right
        if(current_action == 1){
            gladiator_x += 5;
        }
        else if( current_action == 2)
        {
            gladiator_x += 10;
        }
        else if( current_action == 7)
        {
            gladiator_x += 7;
        }
    }

    // Continue updating the animation
    return TRUE;
}

// Callback function to handle key press events
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_s:
            current_action = 0; // Standing
            break;
        case GDK_KEY_w:
            current_action = 1; // Walking
            break;
        case GDK_KEY_r:
            current_action = 2; // Running
            break;
        case GDK_KEY_a:
            current_action = 3; // Attacking 1
            break;
        case GDK_KEY_f:
            current_action = 4; // Attacking 2
            break;
        case GDK_KEY_g:
            current_action = 5; // Attacking 3
            break;
        case GDK_KEY_d:
            current_action = 6; // Defending
            break;
        case GDK_KEY_j:
            current_action = 7; // Jumping
            break;
        case GDK_KEY_h:
            current_action = 8; // Hurting
            break;
        case GDK_KEY_x:
            current_action = 9; // Dying
            break;
        default:
            return FALSE; // No action matched, do not reset the frame counter
    }
    // Reset the frame counter
    current_frame = 0;
    return TRUE;
}



// Function to update the time label
gboolean update_time_label(gpointer user_data) {
    if (is_paused) {
        return TRUE;
    }
    static int seconds = 0;

    // Calculate minutes and seconds
    int minutes = seconds / 60;
    int display_seconds = seconds % 60;

    // Create the time string
    char time_str[6];
    snprintf(time_str, sizeof(time_str), "%02d:%02d", minutes, display_seconds);

    // Update the label text
    gtk_label_set_text(GTK_LABEL(time_label), time_str);

    // Increment the seconds
    seconds++;

    // Return TRUE to keep the timeout running
    return TRUE;
}

void run_game(Player *player) {
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Load the sprite sheet image
    sprite_sheet = gdk_pixbuf_new_from_file(player->spriteSheet, NULL);


    // Create the main window
    GdkPixbuf *arena_pixbuf = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Arena.png", NULL);
    gint arena_width = gdk_pixbuf_get_width(arena_pixbuf);
    gint arena_height = gdk_pixbuf_get_height(arena_pixbuf);
    GtkWidget *window = create_window("Sprite Animation", arena_width, arena_height);

    // Connect key press event to the window
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create a fixed container to hold the background image and gladiator image
    GtkWidget *fixed = create_fixed();

    // Update the background image
    GtkWidget *arena_image = NULL;
    update_background_image(fixed, &arena_image, "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Arena.png");

    // Create an image widget to display the sprite animation
    gladiator_image = GTK_IMAGE(gtk_image_new());
    gtk_widget_set_size_request(GTK_WIDGET(gladiator_image), SPRITE_WIDTH, SPRITE_HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(gladiator_image), gladiator_x+10, 0);

    // Create image widgets for player 1 and player 2 life
    life_image_player1 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\LifeBar.png");
    life_image_player2 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\LifeBar.png");


    time_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\clock.png");
    table_time_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\table.png");


    // Add the life images to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), life_image_player1, 0, 0); // Adjust position as needed
    gtk_fixed_put(GTK_FIXED(fixed), life_image_player2, arena_width - 375, 0);
    gtk_fixed_put(GTK_FIXED(fixed), table_time_image, arena_width / 2 - 160, 20);
    gtk_fixed_put(GTK_FIXED(fixed), time_image, arena_width / 2 - 200, 0);

    // Create a label for the text
    time_label = create_label("00:00", "Ranger Eastwood 24", "white");
    gtk_fixed_put(GTK_FIXED(fixed), time_label, arena_width / 2 - 90, 35);

    // Add the pause button
    GtkWidget *pause_button = create_button("Pause","pause_button");
    gtk_fixed_put(GTK_FIXED(fixed), pause_button, arena_width / 3 -10, 10);


    g_signal_connect(pause_button, "clicked", G_CALLBACK(toggle_pause), NULL);
    // Add the fixed container to the window
    gtk_container_add(GTK_CONTAINER(window), fixed);

    // Show the window
    gtk_widget_show_all(window);

    // Start the animation
    g_timeout_add(100, update_animation, fixed);

    // Start the time label update every second
    g_timeout_add_seconds(1, update_time_label, NULL);

    // Start playing the background music
//    play_sound("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\prepare_yourself.wav");
//    Sleep(2000);
    play_sound("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\GameMusic.wav");
    // Start the GTK main loop
    gtk_main();

}