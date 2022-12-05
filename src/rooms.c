#include "../include/rooms.h"
#include "../include/map.h"

room_ptr room_create(pos_ptr pos, pos_ptr sz) {
    room_t* newRoom = (room_ptr) malloc(sizeof(room_t));

    newRoom->x = pos->x;
    newRoom->y = pos->y;
    newRoom->w = sz->x;
    newRoom->h = sz->y;

    return newRoom;
}