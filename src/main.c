#include <ncurses.h>

#include "../include/display.h"

int main(void) {
    pos_t coords;
    int ch;
    savePos(7, 4, &coords);
    player_t* Person = create_player(&coords, '@', 100);

    screenSetup(DEFAULT);
    while (ch != 'q') {
        screenDraw(Person);
        ch = getch();
        control_player(Person, ch);
    }

    endwin();
    return 0;
}