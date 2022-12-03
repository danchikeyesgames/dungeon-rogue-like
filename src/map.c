#include "../include/map.h"

char map_room[20][20] = {
    {"-------------------"},
    {"|.................|"},
    {"|.................|"},
    {"|.................|"},
    {"|.................|"},
    {"|.................|"},
    {"|.................|"},
    {"-------------------"}
};

void drawmap() {
    mvprintw(2, 1, map_room[0]);
    mvprintw(3, 1, map_room[1]);
    mvprintw(4, 1, map_room[2]);
    mvprintw(5, 1, map_room[3]);
    mvprintw(6, 1, map_room[4]);
    mvprintw(7, 1, map_room[5]);
    mvprintw(8, 1, map_room[6]);
    mvprintw(9, 1, map_room[7]);
}