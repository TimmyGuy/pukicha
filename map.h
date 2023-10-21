/**
 * Name: Tim Ohlsen
 * UVA ID: 15070301
 * Study: Bsc Informatica
 *
 * This file contains the map struct and all the functions that are used to
 * manipulate the map struct. The map struct is used to store the current
 * map data, such as the current map grid, the current amount of rows and
 * the current amount of columns. It also checks if positions are in bounds
 * and if a position is an empty space.
 */

#ifndef DEEL2_MAP_H
#define DEEL2_MAP_H

#include <stdio.h>

struct map_data;

typedef struct  map_data map;

/**
 * Initialise the map struct based on a given file handler. Using the file
 * handler allows you to use any handmade map for the game.
 *
 * @param fh The file handler to a .txt map file
 * @return A map struct
 */
map *map_init(FILE *fh);

/**
 * Get the amount of columns the map has
 *
 * @param mp A pointer to the map
 * @return The number of columns
 */
int get_cols(map *mp);

/**
 * Get the amount of rows the map has
 *
 * @param mp A pointer to the map
 * @return The number of rows
 */
int get_rows(map *mp);

/**
 * Check if a given (x,y) coordinate is in map bounds, between
 * 0 < x < cols and 0 < y < rows
 *
 * @param mp A pointer to the map
 * @param x The X coordinate to be checked
 * @param y The Y coordinate to be checked
 * @return A boolean, 1 if in bounds, 0 if out of bounds
 */
int in_area(map *mp, int x, int y);

/**
 * Get the character placed on a given (x,y) coordinate
 *
 * @param mp A pointer to the map
 * @param x The X coordinate
 * @param y The Y coordinate
 * @return The character currently on the (x,y) coordinate
 */
char get_position(map *mp, int x, int y);

/**
 * Check if the given (x,y) coordinate is an empty space and
 * a player or creature can safely spawn or move there.
 *
 * @param mp A pointer to the map
 * @param x The X coordinate to be checked
 * @param y The Y coordinate to be checked
 * @return A boolean, 1 if space is empty, 0 if space is not empty
 */
int is_move_okay(map *mp, int x, int y);

/**
 * Replaces the current character on (x,y) on the map with the new given character
 *
 * @param mp A pointer to the map
 * @param c The character to be placed
 * @param x The X coordinate
 * @param y The Y coordinate
 * @return Boolean if character could be placed
 */
int set_char(map *mp, char c, int x, int y);

/**
 * Check if the (x,y) coordinate is not an empty space or a wall, then
 * you can assume the character on the map is an encounter
 *
 * @param mp A pointer to the map
 * @param x The X coordinate to be checked
 * @param y The Y coordinate to be checked
 * @return Boolean, 1 if encounter, 0 if not
 */
int is_move_encounter(map *mp, int x, int y);

/**
 * Destruct the map by freeing the allocated memory
 *
 * @param mp A pointer to the map
 */
void map_destruct(map *mp);

#endif //DEEL2_MAP_H
