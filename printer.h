/**
 * Name: Tim Ohlsen
 * UVA ID: 15070301
 * Study: Bsc Informatica
 *
 * This file just prints a string in the middle of a line.
 */

#ifndef DEEL2_PRINTER_H
#define DEEL2_PRINTER_H

/**
 * Prints a string in the middle of a line, with a border on the left and right.
 *
 * @param y The line to print on
 * @param width The width of the line
 * @param str The string to print
 */
void print_middle_bordered(int y, int width, char *str);

/**
 * Prints a string in the middle of a line.
 *
 * @param y The line to print on
 * @param width The width of the line
 * @param str The string to print
 */
void print_middle(int y, int width, char *str);

/**
 * Prints a string in the middle of a line, with ncurses attributes.
 * Multiple attributes can be combined with the bitwise OR operator.
 *
 * @param y The line to print on
 * @param width The width of the line
 * @param str The string to print
 * @param attr The ncurses attribute(s) to use
 */
void print_attr_middle(int y, int width, char *str, int attr);

#endif //DEEL2_PRINTER_H
