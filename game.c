/**
 * Name: Tim Ohlsen
 * UVA ID: 15070301
 * Study: Bsc Informatica
 *
 * This file contains the main function of the game. It will initialize the game,
 * and start the game loop. It will also display the correct screens based on the
 * current state of the game.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include "map.h"
#include "controller.h"
#include "printer.h"

#define MAP "assets/map.txt"

#define PLAYER_PAIR 1
#define EMPTY_PAIR 2
#define CREATURE_PAIR 3
#define MOUNTAIN_PAIR 4
#define WATER_PAIR 5

/**
 * Display the map on the screen.
 *
 * @param mp A pointer to the map to display
 */
void display_map(map *mp) {
    int width = get_cols(mp) + 1;
    int height = get_rows(mp);
    clear();
    for (int i = 1; i < width * height; i++) {
        if (i % width == 0) {
            addch('\n');
        } else {
            int x = (i % width) - 1;
            int y = i / width;
            char pixel = get_position(mp, x, y);
            switch (pixel) {
                case '#':
                    attron(COLOR_PAIR(MOUNTAIN_PAIR));
                    break;
                case ' ':
                    attron(COLOR_PAIR(EMPTY_PAIR));
                    break;
                case '*':
                    attron(COLOR_PAIR(PLAYER_PAIR));
                    break;
                case '~':
                case '^':
                case '&':
                    attron(COLOR_PAIR(CREATURE_PAIR));
                    break;
                default:
                    break;
            }
            addch(get_position(mp, x, y));
            switch (pixel) {
                case '#':
                    attroff(COLOR_PAIR(MOUNTAIN_PAIR));
                    break;
                case ' ':
                    attroff(COLOR_PAIR(EMPTY_PAIR));
                    break;
                case '*':
                    attroff(COLOR_PAIR(PLAYER_PAIR));
                    break;
                case '~':
                case '^':
                case '&':
                    attroff(COLOR_PAIR(CREATURE_PAIR));
                    break;
                default:
                    break;
            }
        }
    }
    refresh();
}

/**
 * Display the start screen.
 *
 * @param mp A pointer to the map to display, so the borders can be calculated
 */
void display_start(map *mp) {
    int width = get_cols(mp);
    int height = get_rows(mp);

    clear();
    mvhline(height, 0, '-', width);
    mvhline(0, 0, '-', width);
    mvvline(0, width, '|', height + 1);
    mvvline(0, 0, '|', height + 1);
    print_attr_middle(3, width, "Welcome to Pukicha!", A_BOLD);
    print_middle(5, width, "Please make sure the box is square");
    print_middle(6, width, "and you can at least see all border-lines");
    print_middle(7, width, "before starting the game");
    print_attr_middle(9, width, "Don't forget to read the handleiding.txt", A_ITALIC);
    print_attr_middle(13, width, "(Press any key to continue)", A_BLINK | A_DIM);
    refresh();
}

/**
 * Display the encounter screen.
 *
 * @param cp A pointer to the controller, so the encounter can be retrieved
 */
void display_encounter(controller *cp) {
    creature *encounter = get_encounter(cp);
    clear();
    int width = COLS;
    mvhline(0, 0, '#', width);
    mvhline(1, 0, '#', width);
    print_attr_middle(1, width, " !! Encounter !! ", A_BLINK);
    mvhline(2, 0, '#', width);
    print_middle_bordered(3, width, "");
    print_middle_bordered(4, width, "You have encountered a wild:");
    print_attr_middle(5, width, get_c_name(encounter), COLOR_PAIR(CREATURE_PAIR));
    print_middle_bordered(6, width, "");
    mvhline(7, 0, '#', width);
    print_middle_bordered(8, width, "");
    print_middle_bordered(9, width, "What do you want to do?");
    print_middle_bordered(10, width, "r: run away");
    print_middle_bordered(11, width, "f: fight");
    print_middle_bordered(12, width, "");
    mvhline(13, 0, '#', width);
    refresh();
}

/**
 * Display the fight screen.
 *
 * @param cp A pointer to the controller, so the encounter and the player can be retrieved
 */
void display_fight(controller *cp) {
    creature *encounter = get_encounter(cp);
    creature *pet = get_pet(get_player(cp));
    clear();

    char *wurmsel[5] = {"   (~* *)",
                        "  (~~~~)",
                        " (~~~~)#",
                        "##(~~~~)#",
                        " #######"};
    char *pikachu[5] = {"   ^ ^",
                        "  (* *)",
                        " ~@- -@#",
                        "###^ ^###",
                        " #######"};
    char *bat[5] = {"   ^ ^",
                    "  (* *)",
                    "<<<- ->>>",
                    "###^ ^###",
                    " #######"};
    char *display_encounter[5] = {0};
    char *display_pet[5] = {0};

    switch (get_c_symbol(encounter)) {
        case '&':
            memcpy(display_encounter, pikachu, sizeof pikachu);
            break;
        case '^':
            memcpy(display_encounter, bat, sizeof bat);
            break;
        case '~':
            memcpy(display_encounter, wurmsel, sizeof wurmsel);
            break;
    }

    switch (get_c_symbol(pet)) {
        case '&':
            memcpy(display_pet, pikachu, sizeof pikachu);
            break;
        case '^':
            memcpy(display_pet, bat, sizeof bat);
            break;
        case '~':
            memcpy(display_pet, wurmsel, sizeof wurmsel);
            break;
    }

    int width = COLS;
    int height = LINES;
    clear();
    mvhline(0, 0, '#', width);
    mvhline(height - 1, 0, '#', COLS);
    for (int i = 0; i < LINES; i++) {
        mvaddch(i, 0, '#');
        mvaddch(i, COLS - 1, '#');
    }

    char e_att_str[30] = "";

    if (get_encounter_move(cp) != -1) {
        strcat(e_att_str, "Enemy used ");
        strcat(e_att_str, get_attack_name(encounter, get_encounter_move(cp)));
    }

    print_middle_bordered(1, width, e_att_str);
    for (int i = 0; i < 5; i++) {
        attron(COLOR_PAIR(CREATURE_PAIR));
        mvaddstr(2 + i, COLS / 3 - 2, display_encounter[i]);
        attroff(COLOR_PAIR(CREATURE_PAIR));
    }
    char e_stat_str[20] = "HP: %d";
    int hp = get_c_hp(encounter);
    sprintf(e_stat_str, e_stat_str, hp);
    mvaddstr(7, COLS / 3, e_stat_str);
    for (int i = 0; i < 5; i++) {
        attron(COLOR_PAIR(PLAYER_PAIR));
        mvaddstr(6 + i, COLS / 3 * 2, display_pet[i]);
        attroff(COLOR_PAIR(PLAYER_PAIR));
    }
    char p_stat_str[20] = "HP: %d";
    sprintf(p_stat_str, p_stat_str, get_c_hp(pet));
    mvaddstr(11, width / 3 * 2 + 2, p_stat_str);
    char p_att_str[30] = "";

    if (get_my_move(cp) != -1) {
        strcat(p_att_str, "You used ");
        strcat(p_att_str, get_attack_name(pet, get_my_move(cp)));
    }
    print_middle_bordered(12, width, p_att_str);
    mvhline(13, 0, '#', COLS);

    if (get_c_hp(encounter) == 0 || get_c_hp(pet) == 0) {
        print_middle_bordered(15, width, "Attack over.. ");
        if (get_c_hp(encounter) == 0) {
            print_attr_middle(16, width, "YOU WON!", A_BOLD);
        } else {
            print_attr_middle(16, width, "YOU LOST..", A_BOLD);
            set_state(cp, GAME_OVER);
            getch();
            refresh();
            return;
        }

        print_attr_middle(17, width, "(press any key to continue)", A_BLINK | A_DIM);
        getch();
        refresh();
        set_state(cp, WINNER);
        return;
    }

    print_middle_bordered(15, width, "Choose an attack!");
    char att_line_one[40] = "1: ";
    strcat(att_line_one, get_attack_name(pet, 0));
    strcat(att_line_one, " 2: ");
    strcat(att_line_one, get_attack_name(pet, 1));
    print_middle_bordered(16, width, att_line_one);
    char att_line_two[40] = "3: ";
    strcat(att_line_two, get_attack_name(pet, 2));
    strcat(att_line_two, " 4: ");
    strcat(att_line_two, get_attack_name(pet, 3));
    print_middle_bordered(17, width, att_line_two);
    refresh();
}

/**
 * While the terminal is busy with the game, this function is called to
 * handle all states within the game. It will display the correct screen
 * based on the state of the game, and handle the input accordingly.
 * It will also handle the side effects of the game, like the encounter,
 * spawns and fights.
 *
 * @param cp The controller to handle
 */
void play(controller *cp) {
    start:
    while (get_state(cp) == START) {
        display_start(get_map(cp));
        if (getch() != KEY_RESIZE) {
            set_state(cp, PLAYING);
        }
    }
    playing:
    while (get_state(cp) == PLAYING) {
        display_map(get_map(cp));
        side_effect(cp);
        int key = getch();
        switch (key) {
            case KEY_LEFT:
                move_player(cp, -1, 0);
                break;
            case KEY_RIGHT:
                move_player(cp, 1, 0);
                break;
            case KEY_UP:
                move_player(cp, 0, -1);
                break;
            case KEY_DOWN:
                move_player(cp, 0, 1);
                break;
            default:
                break;
        }
    }
    encounter:
    while (get_state(cp) == ENCOUNTER) {
        display_encounter(cp);
        int key = getch();
        switch (key) {
            case 'r':
                set_state(cp, PLAYING);
                goto playing;
            case 'f':
                set_state(cp, IN_FIGHT);
                goto fight;
            default:
                break;
        }
    }
    fight:
    while (get_state(cp) == IN_FIGHT) {
        display_fight(cp);
        fight(cp, getch());
    }
    game_over:
    while (get_state(cp) == GAME_OVER) {
        clear();
        print_middle(2, COLS, "Press any key to restart");
        refresh();
        getch();
        set_state(cp, START);
        reset(cp);

        player *pp = player_init();
        cp = controller_init(get_map(cp), pp);

        goto start;
    }
    winner:
    while (get_state(cp) == WINNER) {
        handle_win(cp);
        goto playing;
    }
}

/**
 * When the game is over, this function is called to clean up all the
 * memory that was allocated during the game.
 *
 * @param cp controller to clean up
 */
void clear_game(controller *cp) {
    map_destruct(get_map(cp));
    player_destruct(get_player(cp));
    creature_destruct(get_encounter(cp));
    for (int i = 0; i < MAX_CREATURES; i++) {
        creature_destruct(get_enemy(cp, i));
    }
    controller_destruct(cp);
}

/**
 * The main function of the game. It will initialize the game, and
 * start the game loop.
 *
 * @return 0 if the game ended successfully
 */
int main(void) {
    srand(time(NULL));

    FILE *fh = fopen(MAP, "r");
    if (fh == NULL) {
        perror("Can not open file\n");
        exit(1);
    }

    map *mp = map_init(fh);
    fclose(fh);
    player *pp = player_init();

    controller *cp = controller_init(mp, pp);

    if (mp == NULL) {
        perror("Failed to initialize the map");
        exit(1);
    }

    // Initialize ncurses
    initscr();
    cbreak();             // break using ctrl + c
    keypad(stdscr, TRUE); // listen to chars like arrows
    noecho();             // dont print characters you type
    curs_set(0);

    // Check if the terminal supports colors
    if (!has_colors()) {
        endwin();
        printf("Terminal doesn't support colours\n");
        exit(1);
    }

    // Use colors for a better experience
    start_color();
    init_pair(PLAYER_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(EMPTY_PAIR, COLOR_BLACK, COLOR_BLACK);
    init_pair(CREATURE_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(WATER_PAIR, COLOR_BLUE, COLOR_CYAN);
    init_pair(MOUNTAIN_PAIR, COLOR_BLACK, COLOR_WHITE);

    // Play the game
    play(cp);

    // Finish up
    clear_game(cp);
    endwin();

    return 0;
}
