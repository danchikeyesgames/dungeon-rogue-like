#include "display.h"
#include "player.h"
#include "position.h"

static void move_cursor(pos_ptr ps);

void screenSetup(uint32_t set) {
    initscr();

    if (set == DEFAULT) {
        printw("dungeon");
        noecho();
        keypad(stdscr, true);
        refresh();
    }
}

void screenDraw(player_ptr pl) {
    BSP_split();
    drawmap();
    //drawplayer(pl);
    //move_cursor(&pl->pos);
    refresh();
}

static void move_cursor(pos_ptr ps) {
    move(ps->y, ps->x);
}