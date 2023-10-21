/**
 * Name: Tim Ohlsen
 * UVA ID: 15070301
 * Study: Bsc Informatica
 *
 * This file contains the player struct and all the functions that are used to
 * manipulate the player struct. The player struct is used to store the current
 * player data, such as the current coordinates, the current XP and the current pet.
 */

#ifndef DEEL2_PLAYER_H
#define DEEL2_PLAYER_H

#include "creature.h"

struct player_data;

typedef struct player_data player;

/**
 * Initialize a new player with default values
 *
 * @return a new player struct filled with player_data
 */
player *player_init();

/**
 * Destruct the player pointer, by free-ing the allocated memory
 *
 * @param pp The pointer to the player
 */
void player_destruct(player *pp);

/**
 * Get the X and Y coordinates of the player and put them in the x and y variables
 *
 * @param pp The pointer to the player
 * @param x A pointer to an integer variable to store the X value
 * @param y A pointer to an integer variable to store the Y value
 */
void get_coords(player *pp, int *x, int *y);

/**
 * Return the symbol allocated to the player. Default will be "*", but makes the player icon dynamic,
 * allowing you to choose anything to symbolise the player
 *
 * @param pp The pointer to the player
 * @return The players symbol as a char
 */
char get_p_symbol(player *pp);

/**
 * Set the coordinates of a player. This way the player struct
 * always knows the current location of the player. This way the player
 * can be controlled in an easier way.
 *
 * @param pp The pointer to the player
 * @param x The X coordinate the player has to move to
 * @param y The Y coordinate the player has to move to
 */
void set_coords(player *pp, int x, int y);

/**
 * Update the XP of the player. This way the player struct
 * always knows the current XP of the player.
 *
 * @param pp The pointer to the player
 * @param xp The amount of XP the player has to gain
 */
void update_xp(player *pp, double xp);

/**
 * Get the XP of the player. This way the player struct
 * always knows the current XP of the player.
 *
 * @param pp The pointer to the player
 * @return The amount of XP the player has
 */
double get_xp(player *pp);

/**
 * Set the pet of the player. This way the player struct
 * always knows the current pet of the player.
 *
 * @param pp The pointer to the player
 * @param pet The creature struct of the pet
 */
void set_pet(player *pp, creature *pet);

/**
 * Returns the current pet from the player. Used to display stats
 * or for any encounters and fights.
 *
 * @param pp The pointer to the player
 * @return A creature struct with the creature currently selected as pet
 */
creature *get_pet(player *pp);

#endif //DEEL2_PLAYER_H
