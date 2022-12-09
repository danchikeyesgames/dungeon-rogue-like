#ifndef __ROOMS_H__
#define __ROOMS_H__

#include <stdlib.h>

#include "position.h"

typedef struct _Room {
    int x, y;
    int w, h;
} room_t, *room_ptr;

typedef struct _Tunnel {
    int x, y;
    int w, h;
} hall_t, *hall_ptr;

room_ptr    room_create(pos_ptr pos, pos_ptr sz);
hall_ptr    hall_create(pos_ptr pos, pos_ptr sz);

#endif      // __ROOMS_H__