#ifndef __ROOMS_H__
#define __ROOMS_H__

typedef struct _Room {
    int x, y;
    int w, h;
} room_t, *room_ptr;

typedef struct _Tunnel {
    int x, y;
    int w, h;
} hall_t, *hall_ptr;

#endif      // __ROOMS_H__