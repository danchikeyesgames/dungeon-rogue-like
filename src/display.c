#include "../include/display.h"
#include "../include/player.h"
#include "../include/position.h"

static void move_cursor(pos_ptr ps);

void screenSetup(uint32_t set) {
    initscr();

    if (set == DEFAULT) {
        printw("dungeon");
        noecho();
        refresh();
    }
}

void screenDraw(player_ptr pl) {
    drawmap();
    drawplayer(pl);
    move_cursor(&pl->pos);
    refresh();
}

static void move_cursor(pos_ptr ps) {
    move(ps->y, ps->x);
}