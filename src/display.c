#include "../include/display.h"

void screenSetup(uint32_t set) {
    initscr();

    if (set == DEFAULT) {
        printw("dungeon");
        noecho();
        refresh();
    }
}

void screenDraw() {
    drawmap();
    refresh();
}