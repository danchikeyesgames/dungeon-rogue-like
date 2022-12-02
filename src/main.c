#include <ncurses.h>

#include "../include/display.h"

int main(void) {
    screenSetup(DEFAULT);

    screenDraw();
    getch();

    endwin();
    return 0;
}