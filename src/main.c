#include <ncurses.h>

#include "../include/display.h"

int main(void) {
    screenSetup(DEFAULT);

    getch();

    endwin();
    return 0;
}