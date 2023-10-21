/**
 * Name: Tim Ohlsen
 * UVA ID: 15070301
 * Study: Bsc Informatica
 *
 * This file contains the creature struct and all the functions that are used to
 * manipulate the creature struct. The creature struct is used to store the current
 * creature data, such as the current hp, the current attack and the current coordinates.
 * It also handles all the creature logic, such as updating the hp, getting the symbol
 * and getting the name.
 * Furthermore it also spawns a creature on the map.
 */

#ifndef DEEL2_CREATURE_H
#define DEEL2_CREATURE_H

#include "map.h"

struct attack_data {
    char name[10];
    int damage;
};

typedef struct attack_data attack;

struct creature_data;

typedef struct creature_data creature;

/**
 * Initializes a creature of the given type. Can choose from the following:
 * - Wurmsel
 * - Bat
 * - Pikachu
 *
 * @param name A struct of type creature
 * @return A pointer to the creature
 */
creature *creature_init(creature name);

/**
 * Frees the memory allocated for the creature
 * @param cp
 */
void creature_destruct(creature *cp);

/**
 * Returns the symbol of the creature
 *
 * @param cp The pointer to the creature
 * @return The symbol of the creature
 */
char get_c_symbol(creature *cp);

/**
 * Gets the name of the creature
 * @param cp The pointer to the creature
 * @return The name of the creature
 */
char *get_c_name(creature *cp);

/**
 * Gets the hp of the creature
 * @param cp The pointer to the creature
 * @return The hp of the creature
 */
int get_c_hp(creature *cp);

/**
 * Updates the hp of the creature by a delta value. -n to decrease, n to increase
 *
 * @param cp The pointer to the creature
 * @param d_hp The delta value
 * @return The new hp of the creature
 */
int update_c_hp(creature *cp, int d_hp);

/**
 * Gets the starting hp of the creature
 *
 * @param cp The pointer to the creature
 * @return The starting hp of the creature
 */
int get_c_starting_hp(creature *cp);

/**
 * Gets the starting creature, which is Pikachu
 *
 * @return The starting creature
 */
creature *get_starting_creature();

/**
 * Gets the name of the attack at the given index
 *
 * @param cp The pointer to the creature
 * @param i The index of the attack
 * @return The name of the attack at the given index
 */
char *get_attack_name(creature *cp, int i);

/**
 * Gets the damage of the attack at the given index
 *
 * @param cp The pointer to the creature
 * @param i The index of the attack
 * @return The damage of the attack at the given index
 */
int get_attack_damage(creature *cp, int i);

/**
 * Gets the coordinates of the creature
 *
 * @param cp The pointer to the creature
 * @param x A pointer to an integer to store the x coordinate
 * @param y A pointer to an integer to store the y coordinate
 */
void get_c_coords(creature *cp, int *x, int *y);

/**
 * Choose a random creature to spawn on the map. Check if the
 * location is a valid location to spawn the creature. If not,
 * choose another location. Otherwise spawn the creature.
 *
 * @param mp A pointer to the map
 * @param xp The amount of XP to use as multiplier for the creature
 * @return The pointer to the creature
 */
creature *spawn(map *mp, double xp);

#endif //DEEL2_CREATURE_H
