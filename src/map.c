#include "../include/map.h"

// char map_room[20][20] = {
//     {"-------------------"},
//     {"|.................|"},
//     {"|.................|"},
//     {"|.................|"},
//     {"|.................|"},
//     {"|.................|"},
//     {"|.................|"},
//     {"-------------------"}
// };

// void drawmap() {
//     mvprintw(2, 1, map_room[0]);
//     mvprintw(3, 1, map_room[1]);
//     mvprintw(4, 1, map_room[2]);
//     mvprintw(5, 1, map_room[3]);
//     mvprintw(6, 1, map_room[4]);
//     mvprintw(7, 1, map_room[5]);
//     mvprintw(8, 1, map_room[6]);
//     mvprintw(9, 1, map_room[7]);
// }

leaf_t* leaf_create(int x, int y, int w, int h) {
    leaf_ptr newLeaf = (leaf_ptr) malloc(sizeof(leaf_t));

    newLeaf->x = x;
    newLeaf->x = y;
    newLeaf->x = w;
    newLeaf->x = h;

    return newLeaf;
}

bool leaf_split(leaf_ptr l) {
    int max;
    bool splitH;
    
    if (l->left != NULL && l->right != NULL) {
        return false;
    }

    srand(time(NULL));
    splitH = rand() % 2;
    if (l->height >= 1.25 * l->width)
        splitH = true;
    else if (l->width >= 1.25 * l->height)
        splitH = false;

    max = splitH ? l->height : l->width - MIN_LEAF_SIZE;
    if (max < MIN_LEAF_SIZE)
        return false;

    if (splitH) {

    }
}