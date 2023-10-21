/**
 * Name: Tim Ohlsen
 * UVA ID: 15070301
 * Study: Bsc Informatica
 *
 * This file contains the controller struct and all the functions that are used to
 * manipulate the controller struct. The controller struct is used to store the current
 * controller data, such as the current map, the current player and the current state.
 * It also handles all the game logic, such as moving the player, fighting and side effects.
 * It also handles the enemy list and the encounter.
 */

#include "map.h"
#include "player.h"
#include "creature.h"

#ifndef DEEL2_CONTROLLER_H
#define DEEL2_CONTROLLER_H

#define MAX_CREATURES 7

typedef enum {
    START, PLAYING, ENCOUNTER, IN_FIGHT, GAME_OVER, WINNER
} state;

struct controller_data;

typedef struct controller_data controller;

/**
 * Initialise a new controller based on a map pointer and a player pointer.
 * The controller will make all decisions and actions in the game.
 *
 * @param mp A pointer to a map
 * @param pp A pointer to a player
 * @return A pointer to a controller struct
 */
controller *controller_init(map *mp, player *pp);

/**
 * Destruct the controller by freeing the allocated memory
 *
 * @param cp A pointer to a controller
 */
void controller_destruct(controller *cp);

/**
 * Set the game-state for the game. Controller uses this to keep
 * track of what is going on.
 *
 * @param cp A pointer to a controller
 * @param s The state the game should get
 */
void set_state(controller *cp, state s);

/**
 * Get the game-state for the game. Use this to display different
 * screens within the game.
 *
 * @param cp A pointer to a controller
 * @return The state the game currently has
 */
state get_state(controller *cp);

/**
 * Move a player by a delta value. Check if the player can be moved,
 * then update the (x,y) on the player pointer and move the character
 * on the map
 *
 * @param cp A pointer to a controller
 * @param dx Delta X value
 * @param dy Delta Y value
 * @return Boolean if the player has successfully been moved
 */
int move_player(controller *cp, int dx, int dy);

/**
 * Calculate a N on D chance something will happen. Take a 1 on 1 chance, which
 * will always happen, but a 1 on 2 chance will only happen 50% of the time.
 * Use this to calculate randomness in the game.
 *
 * @param nominator How big the chance is
 * @param denominator Out of how much the chance is
 * @return Boolean if it the chance has hit or not
 */
int in_chance(int nominator, int denominator);

/**
 * Get the current encountering creatures struct from the controller
 *
 * @param cp A pointer to a controller
 * @return The creature being encountered
 */
creature *get_encounter(controller *cp);

/**
 * Get the map which is being played on
 *
 * @param cp A pointer to a controller
 * @return The map
 */
map *get_map(controller *cp);

/**
 * Get the player which is playing
 *
 * @param cp A pointer to a controller
 * @return The player
 */
player *get_player(controller *cp);

/**
 * Handle all fighting functionality in the game. Will check the current attack
 * from the player and damage the encounter. Then it will let the encounter make a move
 * and damage the player accordingly.
 *
 * @param cp A pointer to the controller
 * @param key The keystroke the player pressed
 */
void fight(controller *cp, int key);

/**
 * The side effect that will happen every round while in state PLAYING.
 * Might be enemies spawning or any other actions happening during a refresh.
 *
 * @param cp The pointer to a controller
 */
void side_effect(controller *cp);

/**
 * Get an enemy in the existing enemy list from the controller
 *
 * @param cp A pointer to the controller
 * @param i The index of the enemies array
 * @return The enemy on index I
 */
creature *get_enemy(controller *cp, int i);

/**
 * Reset the game to its starting values. Remove the player and the enemies
 * from the map
 *
 * @param cp A pointer to the controller
 */
void reset(controller *cp);

/**
 * Get the attack the encounter made. This is decided in fight()
 *
 * @param cp The pointer to a controller
 * @return The index of the attack the encounter has made
 */
int get_encounter_move(controller *cp);

/**
 * Get the attack you made. This is decided in fight()
 *
 * @param cp The pointer to a controller
 * @return The index of the attack you have made
 */
int get_my_move(controller *cp);

/**
 * When a fight is over, reset the state to playing and destroy the enemy's pointer.
 * Then cl
 *
 * @param cp A pointer to the controller
 */
void handle_win(controller *cp);

#endif //DEEL2_CONTROLLER_H
