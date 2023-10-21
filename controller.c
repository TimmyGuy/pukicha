#include <stdlib.h>

#include "controller.h"
#include "player.h"
#include "map.h"
#include "creature.h"

#define KEY_ONE 48

struct fight_data {
    int encounter_move;
    int my_move;
};

struct controller_data {
    player *player_ptr;
    map *map_ptr;
    state state;
    creature *enemies[MAX_CREATURES];
    creature *encounter;
    struct fight_data fight;
};

typedef struct controller_data controller;

controller *controller_init(map *mp, player *pp) {
    controller controller_init = {
            .map_ptr = mp,
            .player_ptr = pp,
            .encounter = NULL,
            .enemies = {0},
            .state = START,
            .fight = {
                    .my_move = -1,
                    .encounter_move = -1,
            }
    };

    controller *controller_ptr = malloc(sizeof(controller));
    if (controller_ptr == NULL) {
        free(controller_ptr);
        return NULL;
    }
    *controller_ptr = controller_init;

    int x, y;
    get_coords(pp, &x, &y);

    set_char(mp, get_p_symbol(pp), x, y);
    return controller_ptr;
}

void controller_destruct(controller *cp) {
    free(cp);
}

void set_state(controller *cp, state s) {
    cp->state = s;
}

state get_state(controller *cp) {
    return cp->state;
}

map *get_map(controller *cp) {
    return cp->map_ptr;
}

player *get_player(controller *cp) {
    return cp->player_ptr;
}

int in_chance(int nominator, int denominator) {
    return ((rand() % denominator) + 1) <= nominator;
}

/**
 * Count the amount of enemies in the controller
 *
 * @param cp A pointer to a controller
 * @return The amount of enemies in the controller
 */
int enemy_count(controller *cp) {
    int count = 0;
    for (int i = 0; i < MAX_CREATURES; i++) {
        if (cp->enemies[i] != 0) {
            count++;
        }
    }
    return count;
}

/**
 * Find an open slot in the enemies array
 *
 * @param cp A pointer to a controller
 * @return The index of the first open slot in the enemies array
 */
int enemy_open_slot(controller *cp) {
    for (int i = 0; i < MAX_CREATURES; i++) {
        if (cp->enemies[i] == 0) {
            return i;
        }
    }
    return -1;
}

creature *get_encounter(controller *cp) {
    return cp->encounter;
}

creature *get_enemy(controller *cp, int i) {
    return cp->enemies[i];
}

void side_effect(controller *cp) {
    if (in_chance(1, 7) && enemy_count(cp) < MAX_CREATURES) {
        cp->enemies[enemy_open_slot(cp)] = spawn(cp->map_ptr, get_xp(cp->player_ptr));
    }
}

/**
 * Encounter checks which creature is on the given (x,y) coordinate
 * and sets the encounter to that creature. Then it will update the game state
 * to ENCOUNTER.
 *
 * @param cp The pointer to the controller
 * @param x The X coordinate
 * @param y The Y coordinate
 */
void encounter(controller *cp, int x, int y) {
    for (int i = 0; i < MAX_CREATURES; i++) {
        if (cp->enemies[i] == 0) continue;
        int cx, cy;
        get_c_coords(cp->enemies[i], &cx, &cy);
        if (cx == x && cy == y) {
            cp->encounter = cp->enemies[i];
            set_state(cp, ENCOUNTER);
            break;
        }
    }
}

void fight(controller *cp, int key) {
    if (key - KEY_ONE < 1 || key - KEY_ONE > 4) return;
    cp->fight.my_move = key - 49;

    if (cp->fight.encounter_move != 3) {
        update_c_hp(cp->encounter, -get_attack_damage(get_pet(cp->player_ptr), cp->fight.my_move));
    }

    cp->fight.encounter_move = (rand() % 4) - 1;

    if (cp->fight.my_move != 3) {
        update_c_hp(get_pet(cp->player_ptr), -get_attack_damage(cp->encounter, cp->fight.encounter_move));
    }
}

int move_player(controller *cp, int dx, int dy) {
    int x, y;
    get_coords(cp->player_ptr, &x, &y);
    if (in_area(cp->map_ptr, x + dx, y + dy)) {
        if (is_move_okay(cp->map_ptr, x + dx, y + dy)) {
            set_char(cp->map_ptr, ' ', x, y);
            set_char(cp->map_ptr, get_p_symbol(cp->player_ptr), x + dx, y + dy);
            set_coords(cp->player_ptr, x + dx, y + dy);
        } else if (is_move_encounter(cp->map_ptr, x + dx, y + dy)) {
            encounter(cp, x + dx, y + dy);
        }
    }

    return 0;
}

int get_encounter_move(controller *cp) {
    return cp->fight.encounter_move;
}

int get_my_move(controller *cp) {
    return cp->fight.my_move;
}

void handle_win(controller *cp) {
    creature *pet = get_pet(cp->player_ptr);
    update_xp(cp->player_ptr, get_c_starting_hp(cp->encounter));
    cp->fight.encounter_move = -1;
    cp->fight.my_move = -1;

    // Reset HP and update it to new max HP
    update_c_hp(pet, -99999999);
    double multiplier = 1.0 + ((get_xp(cp->player_ptr) + get_c_hp(pet)) / 100);
    update_c_hp(get_pet(cp->player_ptr),
                (int) (get_c_starting_hp(pet) * multiplier)
    );

    // Clear out old encounter
    for (int i = 0; i < MAX_CREATURES; i++) {
        if (cp->enemies[i] != 0 && !get_c_hp(cp->enemies[i])) {
            creature *c = cp->enemies[i];
            int cx, cy;
            get_c_coords(c, &cx, &cy);
            set_char(cp->map_ptr, ' ', cx, cy);
            creature_destruct(c);
            cp->enemies[i] = 0;
        }
    }

    set_state(cp, PLAYING);
}

void reset(controller *cp) {
    int px, py;
    get_coords(cp->player_ptr, &px, &py);
    set_char(cp->map_ptr, ' ', px, py);

    for (int i = 0; i < MAX_CREATURES; i++) {
        if (cp->enemies[i] != 0) {
            int cx, cy;
            get_c_coords(cp->enemies[i], &cx, &cy);
            set_char(cp->map_ptr, ' ', cx, cy);
        }
    }
}
