#include <iostream>
#include "../include/conio.h"
#include "../include/interface.h"

using namespace std;

void moveHero(char map[][20], int *heroX, int *heroY, char *lastCell, int *HP) {
    enum dirctions {up = 65, down, right, left};

    char trash1 = getch();
    char trash2 = getch();
    int userDirection = getch();

    int lastY = *heroY;
    int lastX = *heroX;

    map[*heroY][*heroX] = *lastCell;
    switch (userDirection) {
        case up:
            (*heroY)--; break;
        case down:
            (*heroY)++; break;
        case left:
            (*heroX)--; break;
        case right:
            (*heroX)++; break;
    }

    if (map[*heroY][*heroX] == 'T') {
        *HP -= 40; 
        *lastCell = map[*heroY][*heroX];
        map[*heroY][*heroX] = '@';

        showMessage("You step on the trap, HP - 40");
    } else if (map[*heroY][*heroX] != '#') {
        *lastCell = map[*heroY][*heroX];
        map[*heroY][*heroX] = '@';
    } else {
        *heroX = lastX;
        *heroY = lastY;
        map[lastY][lastX] = '@';
    }
}
