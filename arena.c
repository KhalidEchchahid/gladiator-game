
#include "arena.h"

gboolean update_animation(gpointer data) {
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
        if(current_action == 3){
            gladiator_x += 5;
        }
        else if( current_action == 4)
        {
            gladiator_x += 10;
        }
    }

    // Continue updating the animation
    return TRUE;
}

// Callback function to handle key press events
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_a:
            current_action = 0; // Attacking
            break;
        case GDK_KEY_h:
            current_action = 2; // Hurting
            break;
        case GDK_KEY_d:
            current_action = 1; // Dying
            break;
        case GDK_KEY_w:
            current_action = 3; // Walking
            break;
        case GDK_KEY_r:
            current_action = 4; // Running
            break;
        case GDK_KEY_s:
            current_action = 5; // Standing
            break;
        default:
            break;
    }
    // Reset the frame counter
    current_frame = 0;
    return TRUE;
}


void run_game() {
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Load the sprite sheet image
    sprite_sheet = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\spritesheet.png", NULL);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sprite Animation");

    // Set the size of the window based on the arena background image size
    GdkPixbuf *arena_pixbuf = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Arena.png", NULL);
    gint arena_width = gdk_pixbuf_get_width(arena_pixbuf);
    gint arena_height = gdk_pixbuf_get_height(arena_pixbuf);
    gtk_window_set_default_size(GTK_WINDOW(window), arena_width, arena_height);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Connect key press event to the window
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    // Create a fixed container to hold the background image and gladiator image
    GtkWidget *fixed = gtk_fixed_new();

    // Create an image widget for the arena background
    GtkWidget *arena_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Arena.png");
    gtk_widget_set_size_request(arena_image, arena_width, arena_height);

    // Add the arena background image to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), arena_image, 0, 0);

    // Create an image widget to display the sprite animation
    gladiator_image = GTK_IMAGE(gtk_image_new());
    gtk_widget_set_size_request(GTK_WIDGET(gladiator_image), SPRITE_WIDTH, SPRITE_HEIGHT);
    gtk_fixed_put(GTK_FIXED(fixed), GTK_WIDGET(gladiator_image), gladiator_x, 0);


    // Create image widgets for player 1 and player 2 life
    life_image_player1 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\LifeBar.png");
    life_image_player2 = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\LifeBar.png");
    time_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\clock.png");
    table_time_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\table.png");
    // Add the life images to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), life_image_player1, 0, 0); // Adjust position as needed
    gtk_fixed_put(GTK_FIXED(fixed), life_image_player2, arena_width - 375, 0);
    gtk_fixed_put(GTK_FIXED(fixed), table_time_image, arena_width /2 - 160, 20);
    gtk_fixed_put(GTK_FIXED(fixed), time_image, arena_width /2 - 200, 0);
    // Add the fixed container to the window
    gtk_container_add(GTK_CONTAINER(window), fixed);





    // Create a label for the text
    GtkWidget *label = gtk_label_new("01:48");

    // Set the font for the label
    PangoFontDescription *font_desc = pango_font_description_from_string("Ranger Eastwood 24");
    gtk_widget_override_font(label, font_desc);

    // Set the text color to white
    GdkRGBA color;
    gdk_rgba_parse(&color, "white");
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &color);
    // Add the label to the fixed container
    gtk_fixed_put(GTK_FIXED(fixed), label, arena_width /2 - 90, 35);


    // Show the window
    gtk_widget_show_all(window);

    // Start the animation
    g_timeout_add(100, update_animation, fixed);

    // Start the GTK main loop
    gtk_main();

}