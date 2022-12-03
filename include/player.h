#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stddef.h>
#include <stdlib.h>

#include "position.h"

typedef struct Player {
    pos_t pos;
    char sym;
    size_t health;
} player_t, *player_ptr; 

player_ptr create_player(pos_ptr ps, char c, size_t hp);


#endif      // __PLAYER_H__