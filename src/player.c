#include <ncurses.h>

#include "../include/player.h"

player_ptr create_player(pos_ptr ps, char c, size_t hp) {
    player_ptr person = (player_ptr) malloc(sizeof(player_t));

    person->pos.x = ps->x;
    person->pos.y = ps->y;
    person->health = hp;
    person->sym = c;

    return person;
}

void move_player(pos_ptr ps, player_ptr pl) {
    pl->pos.x = ps->x;
    pl->pos.y = ps->y;
}

void drawplayer(player_ptr pl) {
    mvprintw(pl->pos.y, pl->pos.x, &pl->sym);
}

void control_player(player_ptr pl, int key) {
    pos_t ps;

    ps.x = pl->pos.x;
    ps.y = pl->pos.y;
    
    switch(key) {
        case KEY_UP:
            ps.y += -1;
            break;
        case KEY_DOWN:
            ps.y += 1;
            break;
        case KEY_LEFT:
            ps.x += -1;
            break;
        case KEY_RIGHT:
            ps.x += 1;
            break;
    }

    move_player(&ps, pl);
}