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

cvector_t(leaf_ptr) lvec;
leaf_ptr leaf_root;

leaf_t* leaf_create(int x, int y, int w, int h) {
    leaf_ptr newLeaf = (leaf_ptr) malloc(sizeof(leaf_t));

    newLeaf->x = x;
    newLeaf->y = y;
    newLeaf->width = w;
    newLeaf->height = h;
    newLeaf->left = NULL;
    newLeaf->right = NULL;
    newLeaf->room = NULL;

    return newLeaf;
}

bool leaf_split(leaf_ptr l) {
    int max;
    int plc_split;
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

    srand(time(NULL));
    plc_split = MIN_LEAF_SIZE + rand() % (max - 1);     // random numbet between (MIN_LEAF_SIZE, max)
    if (splitH) {
        l->left = leaf_create(l->x, l->y, l->width, plc_split);
        l->right = leaf_create(l->x, l->y, l->width, l->height - plc_split);
    } else {
        l->left = leaf_create(l->x, l->y, plc_split, l->height);
        l->right = leaf_create(l->x, l->y, l->width - plc_split, l->height);
    }

    return true;
}

void BSP_split(void) {
    bool check_split = true;

    cvector_push_back(lvec, leaf_root);
    leaf_root = leaf_create(0, 0, WIDTH, HEIGHT);

    while (check_split) {
        size_t sizevec = cvector_get_size(lvec);
        int rndnum;

        check_split = false;
        
        for (size_t i = 0; i < sizevec; ++i) {
            if (lvec[i]->left == NULL && lvec[i]->right == NULL) {
                srand(time(NULL));
                rndnum = 1 + rand() % 100;
                if (lvec[i]->width > MAX_LEAF_SIZE || lvec[i]->height > MAX_LEAF_SIZE || rndnum < 75) {
                    check_split = leaf_split(lvec[i]);

                    if (check_split) {
                        cvector_push_back(lvec, lvec[i]->left);
                        cvector_push_back(lvec, lvec[i]->right);
                    }
                }
            }
        }
    }
}