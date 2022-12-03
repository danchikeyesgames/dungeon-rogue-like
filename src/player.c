#include "../include/player.h"

player_ptr create_player(pos_ptr ps, char c, size_t hp) {
    player_ptr person = (player_ptr) malloc(sizeof(player_t));

    person->pos.x = ps->x;
    person->pos.y = ps->y;
    person->health = hp;
    person->sym = c;

    return person;
}
