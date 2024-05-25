#ifndef MENUARENA_H_INCLUDED
#define MENUARENA_H_INCLUDED


#include <gtk/gtk.h>
#include "window.h"
#include "image.h"

// Forward declarations

GtkWidget *button_start;

GtkWidget *button_exit;
void on_start_button_clicked(GtkWidget *widget, gpointer data);
void create_main_window();
void create_images_window();
void show_large_image(const char *filename);
void on_images_start_button_clicked(GtkWidget *widget, gpointer data);
void add_child(GtkWidget *container, GtkWidget *child) {
    gtk_container_add(GTK_CONTAINER(container), child);
}
// Fonction pour afficher une fen�tre GTK
void show_window(Fenetre *window) {
    gtk_widget_show_all(window->window);
}


// Create the main window with the start button
void create_main_window() {
    Fenetre *main_window = initialiser_win("Main Window", NULL, "Main_Window", NULL, 200, 300, 2, 0, 0, 1, TRUE);
    create_window_n(main_window);

    GtkWidget *button = gtk_button_new_with_label("Start");
    g_signal_connect(button, "clicked", G_CALLBACK(on_start_button_clicked), NULL);

    add_child(main_window->window, button);
    show_window(main_window);
}

// Callback for the start button click
void on_start_button_clicked(GtkWidget *widget, gpointer data) {
    create_images_window();
}

// Callback for image click
void on_image_clicked(GtkWidget *widget, gpointer data) {
    const char *filename = (const char *)data;
    show_large_image(filename);
}

// Show the clicked image in a large window
void show_large_image(const char *filename) {
    Fenetre *large_image_window = initialiser_win("Large Image", NULL, "Large_Image", NULL, 600, 800, 2, 0, 0, 1, TRUE);
    create_window_n(large_image_window);

    GtkWidget *image = gtk_image_new_from_file(filename);
    add_child(large_image_window->window, image);

    show_window(large_image_window);
}

// Callback for the start button in the images window
void on_images_start_button_clicked(GtkWidget *widget, gpointer data) {
    // Add the logic you want to execute when the start button in the images window is clicked
    g_print("Start button in images window clicked\n");
}

#endif // MENUARENA_H_INCLUDED
