#include <ncurses.h>

#include "../include/display.h"

int main(void) {
    pos_t coords;
    savePos(7, 4, &coords);
    player_t* Person = create_player(&coords, '@', 100);

    screenSetup(DEFAULT);

    screenDraw(Person);
    getch();

    endwin();
    return 0;
}