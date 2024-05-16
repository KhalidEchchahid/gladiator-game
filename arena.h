
#ifndef TEST_GTK_ARENA_H
#define TEST_GTK_ARENA_H
#include <gtk/gtk.h>

#define SPRITE_WIDTH (3072/10)
#define SPRITE_HEIGHT (1026/6)
#define NUM_STANDING_FRAMES 10
#define NUM_RUNNING_FRAMES 10
#define NUM_WALKING_FRAMES 10
#define NUM_ATTACKING_FRAMES 10
#define NUM_HURTING_FRAMES 10
#define NUM_DYING_FRAMES 10

extern GtkImage *gladiator_image;
extern GdkPixbuf *sprite_sheet;
extern int current_frame;
extern int current_action;
extern int action_frames[];
extern int gladiator_x;
extern GtkWidget *life_image_player1;
extern GtkWidget *life_image_player2;
extern GtkWidget *time_image;
extern GtkWidget *table_time_image;

gboolean update_animation(gpointer data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);
void run_game();

#endif //TEST_GTK_ARENA_H
