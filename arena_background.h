#ifndef TEST_GTK_ARENA_BACKGROUND_H
#define TEST_GTK_ARENA_BACKGROUND_H
#include <gtk/gtk.h>
#include "menuarena.h"

void on_images_start_button_clickedd(GtkWidget *widget, gpointer data);

gchar* selected_arena="E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\Arena.png";

void on_images_start_button_click(GtkWidget *button, gpointer data) {
    selected_arena = (gchar *)data; // Update the selected_arena variable with the new path
    g_print("Selected arena path: %s\n", selected_arena);
}

// Fonction principale
void create_images_window() {

    GdkScreen *screen = gdk_screen_get_default();
    gint screen_width = 1600;
    gint screen_height = 800;

    // Utilisez une taille l�g�rement inf�rieure � celle de l'�cran pour la fen�tre
    gint window_width = screen_width ;
    gint window_height = screen_height ;

    Fenetre *images_window = initialiser_win("Images Window", NULL, "Images_Window", NULL, window_width, window_height, 2, 0, 0, 1, TRUE);
    create_window_n(images_window);

    GtkWidget *fixed = gtk_fixed_new();
    add_child(images_window->window, fixed);

    // Add background image
    GtkWidget *background_image = gtk_image_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\bggg1.png");
    GdkPixbuf *bg_pixbuf = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\bggg1.png", NULL);
    GdkPixbuf *resized_t_pixbuf = gdk_pixbuf_scale_simple(bg_pixbuf, window_width, window_height, GDK_INTERP_BILINEAR);

    GtkWidget *t_image = gtk_image_new_from_pixbuf(resized_t_pixbuf);
    g_object_unref(bg_pixbuf); // Lib�re la m�moire du pixbuf original
    gtk_fixed_put(GTK_FIXED(fixed), background_image, 0, 0);

    // Load and resize table image
    GdkPixbuf *table_pixbuf = gdk_pixbuf_new_from_file("E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\table4.png", NULL);
    GdkPixbuf *resized_table_pixbuf = gdk_pixbuf_scale_simple(table_pixbuf, 870, 600, GDK_INTERP_BILINEAR);
    GtkWidget *table_image = gtk_image_new_from_pixbuf(resized_table_pixbuf);
    g_object_unref(table_pixbuf); // Lib�re la m�moire du pixbuf original
    gtk_fixed_put(GTK_FIXED(fixed), table_image, window_width * 0.05, window_height * 0.05); // Ajustez la position si n�cessaire

    // Ajoutez les quatre images au conteneur fixe
    add_image(fixed, 1, "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena7.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.2, window_height * 0.2);
    add_image(fixed, 1, "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena5.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.4, window_height * 0.2);
    add_image(fixed, 1, "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena6.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.2, window_height * 0.4);
    add_image(fixed, 1, "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena8.png", GTK_ICON_SIZE_BUTTON, 100, 100, window_width * 0.4, window_height * 0.4);

    // Ajoutez des boutons avec des noms pour le style CSS
    GtkWidget *button1 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button1, "custom-but");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_images_start_button_click), "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena7.png");
    gtk_fixed_put(GTK_FIXED(fixed), button1, window_width * 0.2, window_height * 0.3);

    GtkWidget *button2 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button2, "custom-but");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_images_start_button_click), "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena5.png");
    gtk_fixed_put(GTK_FIXED(fixed), button2, window_width * 0.4, window_height * 0.3);

    GtkWidget *button3 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button3, "custom-but");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_images_start_button_click), "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena6.png");
    gtk_fixed_put(GTK_FIXED(fixed), button3, window_width * 0.2, window_height * 0.5);

    GtkWidget *button4 = gtk_button_new_with_label("Select");
    gtk_widget_set_name(button4, "custom-but");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_images_start_button_click), "E:\\ILISI_s1\\GTK\\Gladiator\\resourses\\arena8.png");
    gtk_fixed_put(GTK_FIXED(fixed), button4, window_width * 0.4, window_height * 0.5);

    // Ajoutez le bouton "Start"
    GtkWidget *button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(on_images_start_button_clickedd), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button_start, 1000, 520);

    // Ajoutez le bouton "Exit"
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_fixed_put(GTK_FIXED(fixed), button_exit, 1000,600);

    show_window(images_window);
}


#endif //TEST_GTK_ARENA_BACKGROUND_H
