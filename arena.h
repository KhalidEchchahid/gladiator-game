
#ifndef TEST_GTK_ARENA_H
#define TEST_GTK_ARENA_H
#include <gtk/gtk.h>
#include "player.h"


extern GtkWidget *life_image_player1;
extern GtkWidget *life_image_player2;
extern GtkWidget *time_image;
extern GtkWidget *table_time_image;

typedef struct {
    int standing;
    int walking;
    int running;
    int attacking1;
    int attacking2;
    int attacking3;
    int defending;
    int jumping;
    int hurting;
    int dying;
} ActionFrames;

typedef struct Actor{
    const char *name;
    GdkPixbuf *sprite_sheet;
    GtkImage *image;
    int current_frame;
    int current_action;
    ActionFrames action_frames;
    int x_position;
    int y_position;
    double sprite_width;
    double sprite_height;
    int health;
    int Attack_P;
    int Defense_d;
    int speed ;
    void (*attack)(struct Actor *self, struct Machine *opponent);
} Actor;


typedef struct Machine{
    GdkPixbuf *sprite_sheet;
    GtkImage *image;
    int current_frame;
    int current_action;
    struct {
        int standing;
        int walking;
        int attacking1;
        int hurting;
        int dying;
    } action_frames;
    int x_position;
    int y_position;
    double sprite_width;
    double sprite_height;
    int health;
    int attack_p ;
    int add_health ;
    int speed ;
    void (*attack)(struct Machine *self, struct Actor *opponent);
} Machine;




extern Actor gladiator;
extern Machine machine;

extern gchar* selected_arena;

gboolean update_animation(gpointer data);
gboolean update_machine_animation(gpointer data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);
void run_game(Actor *player , Machine *machine , int isSmart );
void gladiator_attack(Actor *self, Machine *opponent);
void machine_attack(Machine *self, Actor *opponent);
void update_health_label(int health ,GtkWidget *health_label);

#endif //TEST_GTK_ARENA_H



