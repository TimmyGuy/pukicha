#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "map.h"

#define MAX_MAP_SIZE 1500
#define EOL '\n'


struct map_data {
    char grid[MAX_MAP_SIZE];
    int cols;
    int rows;
};

typedef struct map_data map;

/**
 * Transform a (x,y) coordinate to a 2d array index
 *
 * @param m A pointer to the map to get the columns
 * @param x The X coordinate
 * @param y The Y coordinate
 * @return The 2d arrays index
 */
int get_index(map *m, int x, int y) {
    return x + y * (get_cols(m) + 1);
}

/**
 * Find the first index of a character in a character array
 *
 * @param str the string in which should be searched
 * @param c the character of which the first index should be found
 * @return the index of the character, or -1 if not found
 */
int str_pos(const char str[], char c) {
    char *e = strchr(str, c);
    if (e == NULL) {
        return -1;
    }
    return (int) (e - str);
}

/**
 * Find amount of times a character is counted in a string
 *
 * @param str the string in which the needle has to be counted
 * @param needle the character to be counted
 * @return the amount of times the needle is counted in the string
 */
int char_count(char *str, char needle) {
    int count = 0;
    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] == needle) count++;
    }
    return count;
}

map *map_init(FILE *fh) {
    if (fh == NULL || !fh) return NULL;

    char temp_map[MAX_MAP_SIZE];
    size_t map_size = fread(temp_map, 1, MAX_MAP_SIZE, fh);

    if (map_size < 1) return NULL;
    temp_map[map_size] = '\0';

    map new_map = {0};

    strcpy(new_map.grid, temp_map);
    new_map.cols = str_pos(new_map.grid, EOL);
    new_map.rows = char_count(new_map.grid, EOL);

    map *map_pointer = malloc(sizeof(map));
    if (map_pointer == NULL) {
        free(map_pointer);
        return NULL;
    }

    *map_pointer = new_map;
    return map_pointer;
}

void map_destruct(map *mp) {
    free(mp);
}

int get_cols(map *mp) {
    return mp->cols;
}

int get_rows(map *mp) {
    return mp->rows;
}

int in_area(map *mp, int x, int y) {
    return (0 <= x && x < get_cols(mp)) && (0 <= y && y < get_rows(mp));
}

char get_position(map *mp, int x, int y) {
    if (!in_area(mp, x, y)) {
        return '\0';
    }

    return mp->grid[get_index(mp, x, y)];
}

int is_move_okay(map *mp, int x, int y) {
    char testch = get_position(mp, x, y);
    return (testch & A_CHARTEXT) == ' ';
}

int is_move_encounter(map *mp, int x, int y) {
    char testch = get_position(mp, x, y);

    return ((testch & A_CHARTEXT) != ' ' && (testch & A_CHARTEXT) != '#');
}

int set_char(map *mp, char c, int x, int y) {
    if (!in_area(mp, x, y)) {
        return 0;
    }

    mp->grid[get_index(mp, x, y)] = c;
    return 1;
}
