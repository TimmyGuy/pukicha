#include <stdlib.h>
#include "creature.h"
#include "map.h"

#define CREATURE_LIST {wurmsel, bat, pikachu}

struct attack_data;

typedef struct attack_data attack;

struct creature_data {
    int hp;
    int starting_hp;
    char name[10];
    attack att[4];
    char symbol;
    int pos_x;
    int pos_y;
};

typedef struct creature_data creature;

creature wurmsel = {
        .hp = 5,
        .starting_hp = 5,
        .symbol = '~',
        .name = "Wurmsel",
        .att = {
                {
                        .name = "Squiqqle",
                        .damage = 2
                },
                {
                        .name = "Sqreek",
                        .damage = 1
                },
                {
                        .name = "Hellwater",
                        .damage = 3
                },
                {
                        .name = "Shield",
                        .damage = 0
                }
        },
};

creature bat = {
        .hp = 7,
        .starting_hp = 7,
        .symbol = '^',
        .name = "Bat",
        .att = {
                {
                        .name = "Echo",
                        .damage = 2
                },
                {
                        .name = "Rush",
                        .damage = 1
                },
                {
                        .name = "Covid",
                        .damage = 3
                },
                {
                        .name = "Shield",
                        .damage = 0
                }
        },
};

creature pikachu = {
        .hp = 9,
        .starting_hp = 9,
        .symbol = '&',
        .name = "Pikachu",
        .att = {
                {
                        .name = "Charm",
                        .damage = 2
                },
                {
                        .name = "Badjazzl",
                        .damage = 1
                },
                {
                        .name = "Electro",
                        .damage = 3
                },
                {
                        .name = "Shield",
                        .damage = 0
                }
        },
};

creature *creature_init(creature name) {
    creature *creature_ptr = malloc(sizeof(creature));
    if (creature_ptr == NULL) {
        free(creature_ptr);
        exit(1);
    }
    *creature_ptr = name;
    return creature_ptr;
}

creature *spawn(map *mp, double xp) {
    creature creature_list[] = CREATURE_LIST;
    int creature_to_spawn = rand() % 3;
    creature *cp = creature_init(creature_list[creature_to_spawn]);

    // Increase game difficulty
    double multiplier = 1.0 + ((xp - 1.0) / 100);
    cp->hp = (int) (cp->starting_hp * multiplier);
    cp->att[0].damage = (int) (cp->att[0].damage * multiplier);
    cp->att[1].damage = (int) (cp->att[1].damage * multiplier);
    cp->att[2].damage = (int) (cp->att[2].damage * multiplier);

    int map_length = get_cols(mp) * get_rows(mp);
    int x, y;

    do {
        int spawn_location = rand() % map_length;
        x = spawn_location % get_cols(mp);
        y = spawn_location / get_cols(mp);
    } while (!is_spawn_okay(mp, x, y, cp->symbol) || !is_move_okay(mp, x, y));

    cp->pos_y = y;
    cp->pos_x = x;

    set_char(mp, cp->symbol, x, y);

    return cp;
}

creature *get_starting_creature() {
    return creature_init(pikachu);
}

char get_c_symbol(creature *cp) {
    return cp->symbol;
}

char *get_c_name(creature *cp) {
    return cp->name;
}

int get_c_hp(creature *cp) {
    return cp->hp;
}

int update_c_hp(creature *cp, int d_hp) {
    cp->hp += d_hp;
    if (cp->hp < 0) {
        cp->hp = 0;
    }
    return cp->hp;
}

void get_c_coords(creature *cp, int *x, int *y) {
    *x = cp->pos_x;
    *y = cp->pos_y;
}

char *get_attack_name(creature *cp, int i) {
    return cp->att[i].name;
}

int get_attack_damage(creature *cp, int i) {
    return cp->att[i].damage;
}

int get_c_starting_hp(creature *cp) {
    return cp->starting_hp;
}

void creature_destruct(creature *cp) {
    free(cp);
}
