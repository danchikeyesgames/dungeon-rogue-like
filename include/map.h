#ifndef __MAP_H__
#define __MAP_H__

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "rooms.h"
#include "player.h"
#include "../lib/C11-containers-lib/cvector/cvector.h"
#include "../lib/C11-containers-lib/cstack/cstack.h"

#define HEIGHT 80
#define WIDTH  120
#define HEIGHTVIEW 25
#define WIDTHVIEW  80

#define MIN_LEAF_SIZE 2

typedef struct _Map {
    cvector_t(room_ptr) rooms;
    cvector_t(hall_ptr) halls;
    cvector_t(cvector_t(char)) map;
    player_ptr pl;
} game_map_t;

typedef struct _Leaf {
    int x, y;
    int width, height;

    room_ptr room;
    cvector_t(hall_ptr) halls;

    struct _Leaf* left;
    struct _Leaf* right;
} leaf_t, *leaf_ptr;



void drawmap();
leaf_t* leaf_create(int x, int y, int w, int h);
bool leaf_split(leaf_ptr l);



#endif          // __MAP_H__