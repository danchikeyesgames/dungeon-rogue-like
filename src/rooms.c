#include "rooms.h"
#include "map.h"

room_ptr room_create(pos_ptr pos, pos_ptr sz) {
    room_t* newRoom = (room_ptr) malloc(sizeof(room_t));

    newRoom->x = pos->x;
    newRoom->y = pos->y;
    newRoom->w = sz->x;
    newRoom->h = sz->y;

    return newRoom;
}

hall_ptr hall_create(pos_ptr pos, pos_ptr sz) {
    hall_t* newHall = (hall_ptr) malloc(sizeof(hall_t));

    newHall->x = pos->x;
    newHall->y = pos->y;
    newHall->w = sz->x;
    newHall->h = sz->y;

    return newHall;
}