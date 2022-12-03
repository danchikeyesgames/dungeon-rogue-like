#ifndef __POSITION_H__
#define __POSITION_H__

typedef struct Position {
    int x;
    int y;
} pos_t, *pos_ptr;

void savePos(int x, int y, pos_ptr ps);

#endif      // __POSITION_H__