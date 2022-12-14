#include "map.h"

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

cvector_t(leaf_ptr) leaf_rooms = NULL;
leaf_ptr leaf_root = NULL;

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
    
    if (l->left != NULL || l->right != NULL) {
        return false;
    }

    splitH = rand() % 2;
    if (l->height >= 1.25 * l->width)
        splitH = true;
    else if (l->width >= 1.25 * l->height)
        splitH = false;

    max = (splitH ? l->height : l->width) - MIN_LEAF_SIZE;
    if (max < MIN_LEAF_SIZE)
        return false;

    plc_split = MIN_LEAF_SIZE + rand() % (max - MIN_LEAF_SIZE + 1);     // random numbet between (MIN_LEAF_SIZE, max)
    if (splitH) {
        l->left = leaf_create(l->x, l->y, l->width, plc_split);
        l->right = leaf_create(l->x, l->y + plc_split, l->width, l->height - plc_split);
    } else {
        l->left = leaf_create(l->x, l->y, plc_split, l->height);
        l->right = leaf_create(l->x + plc_split, l->y, l->width - plc_split, l->height);
    }

    return true;
}

void BSP_split(void) {
    bool check_split = true;

    leaf_root = leaf_create(0, 0, WIDTH, HEIGHT);
    cvector_push_back(leaf_rooms, leaf_root);
    srand(time(NULL));

    while (check_split) {
        size_t sizevec = cvector_get_size(leaf_rooms);
        int rndnum;

        check_split = false;
        
        for (size_t i = 0; i < sizevec; ++i) {
            if (leaf_rooms[i]->left == NULL && leaf_rooms[i]->right == NULL) {
                rndnum = 1 + rand() % 100;
                if (leaf_rooms[i]->width > MAX_LEAF_SIZE || leaf_rooms[i]->height > MAX_LEAF_SIZE || rndnum < 75) {

                    if (leaf_split(leaf_rooms[i])) {
                        cvector_push_back(leaf_rooms, leaf_rooms[i]->left);
                        cvector_push_back(leaf_rooms, leaf_rooms[i]->right);
                        check_split = true;
                    }
                }
            }
        }
    }

    init_rooms(leaf_root);
}

void drawmap(void) {
    size_t sizevec = cvector_get_size(leaf_rooms);
    size_t sizehall = 0;

    // for (size_t i = 0; i < sizevec; ++i) {
    //     if (lvec[i]->left == NULL && lvec[i]->right == NULL) {
    //         for (size_t j = 0; j < lvec[i]->width; j++)
    //             mvprintw(lvec[i]->y, lvec[i]->x + j, "#");

    //         for (size_t j = 0; j < lvec[i]->height; j++)
    //             mvprintw(lvec[i]->y + j, lvec[i]->x, "#");

    //         for (size_t j = 0; j < lvec[i]->height; j++)
    //             mvprintw(lvec[i]->y + j, lvec[i]->x + lvec[i]->width, "#");

    //         for (size_t j = 0; j <= lvec[i]->width; j++)
    //             mvprintw(lvec[i]->y + lvec[i]->height, lvec[i]->x + j, "#");
    //     }

    // }

    // draw rooms
    for (size_t i = 0; i < sizevec; ++i) {
        if (leaf_rooms[i]->left == NULL && leaf_rooms[i]->right == NULL) {
            for (size_t j = 0; j <= leaf_rooms[i]->room->w; j++)
                mvprintw(leaf_rooms[i]->room->y, leaf_rooms[i]->room->x + j, "-");

            for (size_t j = 1; j < leaf_rooms[i]->room->h; j++)
                mvprintw(leaf_rooms[i]->room->y + j, leaf_rooms[i]->room->x, "|");

            for (size_t j = 1; j < leaf_rooms[i]->room->h; j++)
                mvprintw(leaf_rooms[i]->room->y + j, leaf_rooms[i]->room->x + leaf_rooms[i]->room->w, "|");

            for (size_t j = 0; j <= leaf_rooms[i]->room->w; j++)
                mvprintw(leaf_rooms[i]->room->y + leaf_rooms[i]->room->h, leaf_rooms[i]->room->x + j, "-");
        }
    }

    // draw halls
    for (size_t i = 0; i < sizevec; ++i) {
        if (leaf_rooms[i]->left != NULL && leaf_rooms[i]->right != NULL) {
            if (leaf_rooms[i]->halls != NULL) {
                sizehall = cvector_get_size(leaf_rooms[i]->halls);
                for (size_t j = 0; j < sizehall; ++j) {
                    if (leaf_rooms[i]->halls[j]->h == 1) {
                        for (int k = 0; k <= leaf_rooms[i]->halls[j]->w; ++k)
                            mvprintw(leaf_rooms[i]->halls[j]->y, leaf_rooms[i]->halls[j]->x + k, "*");
                    } else {
                        for (int k = 0; k <= leaf_rooms[i]->halls[j]->h; ++k)
                            mvprintw(leaf_rooms[i]->halls[j]->y + k, leaf_rooms[i]->halls[j]->x, "*");
                    }
                }
            }
        }
    }

}

void init_rooms(leaf_ptr l) {
    int x, y, w, h;
    room_ptr tmp_left;
    room_ptr tmp_right;

    if (l->left != NULL || l->right != NULL) {
        if (l->left != NULL)
            init_rooms(l->left);
        
        if (l->right != NULL)
            init_rooms(l->right);

        if (l->right != NULL && l->left != NULL) {
            tmp_left = room_get(l->left);
            tmp_right = room_get(l->right);
            init_halls(tmp_left, tmp_right, l);
        }
    } else {
        pos_t point_pos;
        pos_t point_sz;

        w = 3 + rand() % (l->width - 4);
        h = 3 + rand() % (l->height - 4);
        savePos(w, h, &point_sz);

        x = 1 + rand() % (l->width - w - 1);
        y = 1 + rand() % (l->height - h - 1);
        savePos(l->x + x, l->y + y, &point_pos);

        l->room = room_create(&point_pos, &point_sz);
    }
}

room_ptr room_get(leaf_ptr l) {
    if (l->room != NULL) {
        return l->room;
    } else {
        room_ptr lroom;
        room_ptr rroom;

        if (l->left != NULL) {
            lroom = room_get(l->left);
        }

        if (l->right != NULL) {
            rroom = room_get(l->right);
        }

        if (rroom == NULL && lroom == NULL)
            return NULL;

        if (rroom == NULL)
            return lroom;

        else if (lroom == NULL)
            return rroom;

        else {
            int rndnum = 1 + rand() % 100; 
            if (rndnum <= 50)
                return lroom;
            else
                return rroom;
        }
    }
}

void init_halls(room_ptr lr, room_ptr rr, leaf_ptr leaf) {
    pos_t p1, p2, sz, point;
    hall_ptr newHall;
    int rn = 0;

    srand(time(NULL));
    savePos(lr->x + 1 + rand() % (lr->w - 1), lr->y + 1 + rand() % (lr->h - 1), &p1);
    savePos(rr->x + 1 + rand() % (rr->w - 1), rr->y + 1 + rand() % (rr->h - 1), &p2);

    leaf->halls = cvector_init(hall_ptr, 2);

    int w = p2.x - p1.x;
    int h = p2.y - p1.y;

    if (w < 0) {
		if (h < 0) {
			rn = rand() % 2;
            if (rn == 1) {
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&p2, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p1.x, p2.y, &point);
                savePos(1, abs(h), &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            } else {
                savePos(1, abs(h), &sz);
                newHall = hall_create(&p2, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p2.x, abs(h) + p2.y, &point);
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            }
		} else if (h > 0) {
            rn = rand() % 2;
            if (rn == 1) {
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&p2, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p1.x, p1.y, &point);
                savePos(1, abs(h), &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            } else {
                savePos(1, abs(h), &sz);
                savePos(p2.x, p1.y, &point);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p2.x, p1.y, &point);
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            }
		} else {
			savePos(abs(w), 1, &sz);
            newHall = hall_create(&p2, &sz);
            cvector_push_back(leaf->halls, newHall);
		}
	} else if (w > 0) {
		if (h < 0) {
            rn = rand() % 2;
            if (rn == 1) {
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&p1, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p2.x, p2.y, &point);
                savePos(1, abs(h), &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            } else {
                savePos(p1.x, p2.y, &point);
                savePos(1, abs(h), &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            }
		} else if (h > 0) {
            rn = rand() % 2;
            if (rn == 1) {
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&p1, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p2.x, p1.y, &point);
                savePos(1, abs(h), &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            } else {
                savePos(1, abs(h), &sz);
                newHall = hall_create(&p1, &sz);
                cvector_push_back(leaf->halls, newHall);

                savePos(p1.x, abs(h) + p1.y, &point);
                savePos(abs(w), 1, &sz);
                newHall = hall_create(&point, &sz);
                cvector_push_back(leaf->halls, newHall);
            }
		} else {
			savePos(abs(w), 1, &sz);
            newHall = hall_create(&p1, &sz);
            cvector_push_back(leaf->halls, newHall);
		}
	} else {
        if (h > 0) {
            savePos(1, h, &sz);
            newHall = hall_create(&p1, &sz);
            cvector_push_back(leaf->halls, newHall);
        } else if (h < 0) {
            savePos(1, abs(h), &sz);
            newHall = hall_create(&p2, &sz);
            cvector_push_back(leaf->halls, newHall);
        }
	}
}