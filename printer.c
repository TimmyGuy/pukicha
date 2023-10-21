#include <string.h>
#include "printer.h"
#include "ncurses.h"

/**
 * Returns the x coordinate of the leftmost character of a string
 * that is centered in a given width.
 *
 * @param width The width of the area to center the string in
 * @param str The string to center
 * @return The x coordinate of the leftmost character of the centered string
 */
int get_center(int width, char *str) {
    return (width - (int) strlen(str)) / 2;
}

void print_middle_bordered(int y, int width, char *str) {
    mvaddch(y, 0, '#');
    mvaddch(y, width - 1, '#');
    mvaddstr(y, get_center(width, str), str);
}

void print_middle(int y, int width, char *str) {
    mvaddstr(y, get_center(width, str), str);
}

void print_attr_middle(int y, int width, char *str, int attr) {
    attron(attr);
    mvaddstr(y, get_center(width, str), str);
    attroff(attr);
}
