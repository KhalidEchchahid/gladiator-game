
#ifndef TEST_GTK_CREATECHARACTER_H
#define TEST_GTK_CREATECHARACTER_H



#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "windowboxscroll.h"
#include "Gridheader.h"
#include "label.h"
#include "ButtonSimpleheader.h"
#include "EntryHeader.h"
#include "imageHeader.h"


#define TOTAL_POINTS 200
#define NUM_PlayerISTICS 4
// Create player data

Box *photo_area ;// D�claration de la variable globale
GtkWidget *current_photo_widget = NULL;
GtkWidget *main_box = NULL;

typedef struct {
    GtkWidget *sliders[NUM_PlayerISTICS];
    GtkWidget *remaining_points_label;
    int remaining_points;
} PlayerOptions;

// Structure to hold player data

Actor *player = NULL;
//Machine *machine = NULL;
typedef struct {
    GtkWidget *entry;
    Window *window;
} CallbackData;

typedef struct {
    const gchar *name;
    int value;
} Playeristic;

typedef struct {
    gchar* grp;
    gchar* name;
} infos;

GList *button_groups = NULL;

typedef struct {
    const gchar *ancienNom;
    gchar *nouveauNom;
} Noms;

Noms *noms = NULL;

void apply_label_style(GtkWidget *label) {
    PangoAttrList* attrList = pango_attr_list_new();
    PangoAttribute* attr;

    attr = pango_attr_family_new("arial");
    pango_attr_list_insert(attrList, attr);

    attr = pango_attr_size_new(16 * PANGO_SCALE);
    pango_attr_list_insert(attrList, attr);

    GdkRGBA color;
    gdk_rgba_parse(&color, "#ffd55c");
    attr = pango_attr_foreground_new(color.red * 65535, color.green * 65535, color.blue * 65535);
    pango_attr_list_insert(attrList, attr);

    gtk_label_set_attributes(GTK_LABEL(label), attrList);
    pango_attr_list_unref(attrList);
}
void modifier(GtkButton *button, gpointer data) {
    GtkWidget *label = GTK_WIDGET(data);
    const gchar *ancienNom = gtk_label_get_text(GTK_LABEL(label));

    GtkWidget *dialog = gtk_dialog_new_with_buttons("Modifier le nom",
                                                    GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                    GTK_DIALOG_MODAL,
                                                    "OK",
                                                    GTK_RESPONSE_OK,
                                                    "Annuler",
                                                    GTK_RESPONSE_CANCEL,
                                                    NULL);

    // Appliquer un ID au dialog pour le styliser
    gtk_widget_set_name(dialog, "dialog");

    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), ancienNom);
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    // Appliquer un ID au entry pour le styliser
    gtk_widget_set_name(entry, "dialog-entry");

    // Montrer tous les widgets
    gtk_widget_show_all(dialog);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_OK) {
        const gchar *nouveauNom = gtk_entry_get_text(GTK_ENTRY(entry));
        gtk_label_set_text(GTK_LABEL(label), nouveauNom);
        player->name = strdup(nouveauNom);
    }

    gtk_widget_destroy(dialog);
}


void update_remaining_points_label(PlayerOptions *options) {
    gchar label_text[64];
    g_snprintf(label_text, sizeof(label_text), "Remaining Points: %d", options->remaining_points);
    gtk_label_set_text(GTK_LABEL(options->remaining_points_label), label_text);
}

void on_slider_value_changed(GtkRange *range, gpointer user_data) {
    PlayerOptions *options = (PlayerOptions *)user_data;
    int total_allocated = 0;
    printf("\nEntered on_slider_value_changed");

    // Calculate the total allocated points
    for (int i = 0; i < NUM_PlayerISTICS; ++i) {
        total_allocated += (int)gtk_range_get_value(GTK_RANGE(options->sliders[i]));
    }
    printf("\nTotal allocated points: %d", total_allocated);

    // Update remaining points
    options->remaining_points = TOTAL_POINTS - total_allocated;
    printf("\nRemaining points: %d", options->remaining_points);
    update_remaining_points_label(options);

    // Adjust sliders based on remaining points
    int adjustment = options->remaining_points < 0 ? -options->remaining_points : 0;
    if (adjustment != 0) {
        printf("\nAdjusting sliders by: %d", adjustment);
    }

    for (int i = 0; i < NUM_PlayerISTICS; ++i) {
        double value = gtk_range_get_value(GTK_RANGE(options->sliders[i])) - adjustment;
        gtk_range_set_value(GTK_RANGE(options->sliders[i]), value);
    }
    printf("\nSliders adjusted");

    // Ensure player is allocated before updating
    if (player == NULL) {
        fprintf(stderr, "\nError: player is NULL. Allocating memory now.");
        player = (Actor *)malloc(sizeof(Actor));
        if (player == NULL) {
            fprintf(stderr, "\nFailed to allocate memory for player");
            exit(1);
        }
        // Optionally initialize player fields to default values
        player->health = 0;
        player->Attack_P = 0;
        player->Defense_d = 0;
//        player->speed = 0;
    }

    // Mettre � jour les caract�ristiques du joueur � partir des curseurs
    player->health = (int)gtk_range_get_value(GTK_RANGE(options->sliders[2]));
    player->Attack_P = (int)gtk_range_get_value(GTK_RANGE(options->sliders[1]));
    player->Defense_d = (int)gtk_range_get_value(GTK_RANGE(options->sliders[0]));
//    player->speed = (int)gtk_range_get_value(GTK_RANGE(options->sliders[3]));
    printf("\nPlayer stats updated: name:%s PV=%d, Attack=%d, Defense=%d",
           player->name,player->health, player->Attack_P, player->Defense_d);

    // example_function(); // Uncomment if needed
}
// Exemple d'utilisation des valeurs de la structure Player
void example_function() {
    // Utilisez les valeurs du joueur comme vous le souhaitez
    printf("PV du joueur : %d\n", player->name);
    printf("PV du joueur : %d\n", player->health);
    printf("Attaque du joueur : %d\n", player->Attack_P);
    printf("D�fense du joueur : %d\n", player->Defense_d);
//    printf("Vitesse du joueur : %d\n", player->speed);
}
GtkWidget* create_slider(PlayerOptions *options) {
    GtkWidget *slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, TOTAL_POINTS, 1);
    g_signal_connect(slider, "value-changed", G_CALLBACK(on_slider_value_changed), options);
    return slider;
}

void load_css2() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    GError *error = NULL;

    if (!gtk_css_provider_load_from_path(provider, "E:\\ILISI_s1\\GTK\\Gladiator\\style.css", &error)) {
        g_warning("Failed to load CSS file: %s", error->message);
        g_error_free(error);
        return;
    }
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
}

// Fonction pour charger la grande photo du personnage s�lectionn�
void load_Player_photo(const gchar *photo_path) {
    // Charger la nouvelle photo dans le widget existant
    gtk_image_set_from_file(GTK_IMAGE(current_photo_widget), photo_path);
}
void Player_thumbnail_clicked(GtkWidget *widget, gpointer data) {
    Actor *player_selected = (Actor *)data;
    player->image = player_selected->image;
    player->sprite_sheet  = player_selected->sprite_sheet;
    //player->name=player_selected->name;
    // Utilisez les donn�es du joueur comme vous le souhaitez
    printf("Nom: %s\n", player->name);
    printf("Chemin d'image: %s\n", player->image);
    // Utilisez les valeurs du joueur comme vous le souhaitez
    printf("PV du joueur : %d\n", player->health);
    printf("Attaque du joueur : %d\n", player->Attack_P);
    printf("D�fense du joueur : %d\n", player->Defense_d);
//    printf("Vitesse du joueur : %d\n", player->speed);

    load_Player_photo(player->image);

    // Pas besoin de lib�rer la m�moire allou�e pour les donn�es du joueur
    // g_free((gpointer)data);
}

GtkWidget* create_Player_thumbnails(Player players[], int num_Players) {
    // Cr�er un conteneur pour les miniatures
    GtkWidget *thumbnails_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Ajouter des boutons de miniature pour chaque personnage
    for (int i = 0; i < num_Players; i++) {
        // Cr�er un bouton avec une �tiquette pour le nom du personnage
        GtkWidget *button = gtk_button_new();
        GtkWidget *label = gtk_label_new(players[i].name);
        gtk_container_add(GTK_CONTAINER(button), label);

        // Connecter le signal "clicked" du bouton � la fonction de rappel Player_thumbnail_clicked
        g_signal_connect(button, "clicked", G_CALLBACK(Player_thumbnail_clicked), &players[i]);

        // Ajouter une marge en bas de chaque miniature
        gtk_widget_set_margin_bottom(button, 5);

        // Ajouter le bouton � la liste des miniatures
        gtk_box_pack_start(GTK_BOX(thumbnails_container), button, FALSE, FALSE, 0);
    }

    return thumbnails_container;
}


// Fonction pour cr�er ou mettre � jour le widget de la photo du personnage
GtkWidget *create_or_update_photo_widget(const gchar *photo_path) {
    // V�rifiez si le widget de photo existe d�j�
    if (current_photo_widget != NULL) {
        // Si le widget existe, mettez � jour son chemin d'image
        gtk_image_set_from_file(GTK_IMAGE(current_photo_widget), photo_path);
    } else {
        // Si le widget n'existe pas, cr�ez-le et chargez l'image
        current_photo_widget = gtk_image_new_from_file(photo_path);
    }
    // Retournez le widget de photo
    return current_photo_widget;
}



#endif //TEST_GTK_CREATECHARACTER_H
