#include "player.h"
#include "creature.h"

#include <stdio.h>
#include <stdlib.h>

struct player_data {
    char symbol;
    int pos_x;
    int pos_y;
    double xp;
    creature *pet;
};

typedef struct player_data player;

player *player_init() {
    player p = {
        .symbol = '*',
        .pos_x = 49,
        .pos_y = 13,
        .xp = 1.0,
        .pet = get_starting_creature()
    };

    player *player_pointer = malloc(sizeof(player));
    if (player_pointer == NULL) {
        free(player_pointer);
        return NULL;
    }
    *player_pointer = p;
    return player_pointer;
}

void player_destruct(player *pp) {
    free(pp);
}

void get_coords(player *pp, int *x, int *y) {
    *x = pp->pos_x;
    *y = pp->pos_y;
}

void set_coords(player *pp, int x, int y) {
    pp->pos_x = x;
    pp->pos_y = y;
}

creature *get_pet(player *pp) {
    return pp->pet;
}

void update_xp(player *pp, double xp) {
    pp->xp += xp;
}

double get_xp(player *pp) {
    return pp->xp;
}

void set_pet(player *pp, creature *pet) {
    pp->pet = pet;
}

char get_p_symbol(player *pp) {
    return pp->symbol;
}
