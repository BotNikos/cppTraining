#include <iostream>
#include "../include/enemy.h"
#include "../include/interface.h"


void move (char map[][20], struct hero *hero,
           struct enemy enemies[], int enemiesSize) {

    for (int i = 0; i < enemiesSize; i++) {
        int lastX = enemies[i].x;
        int lastY = enemies[i].y;

        map[enemies[i].y][enemies[i].x] = enemies[i].lastCell;
        //enemies[i].y++;
        enemies[i].lastCell = map[enemies[i].y][enemies[i].x];

        if (enemies[i].lastCell == '#') {
            enemies[i].x = lastX;
            enemies[i].y = lastY;
        }
    }
}

void clearEnemies(struct enemy enemies[], int *enemiesSize) {
    for (int i = 0; i < *enemiesSize; i++) {
        enemies[i] = {};
    }

    *enemiesSize = 0;
}

void enemyAction (char map[][20], struct hero *hero,
                  struct enemy enemies[], int *enemiesSize) {

    move (map, hero, enemies, *enemiesSize);
}
