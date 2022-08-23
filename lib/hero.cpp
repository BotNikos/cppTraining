#include <chrono>
#include <thread>
#include <iostream>
#include "../include/conio.h"
#include "../include/interface.h"

using namespace std;

void moveHero(char map[][20], int *heroX, int *heroY, char *lastCell, int *HP, string log[]) {
    enum dirctions {up = 65, down, right, left};

    char trash = getch();
    int userDirection = getch();

    int lastY = *heroY;
    int lastX = *heroX;

    map[*heroY][*heroX] = *lastCell;
    string message;
    switch (userDirection) {
        case up:
            (*heroY)--;
            message = "Вы пошли вверх";
            break;
        case down:
            (*heroY)++; 
            message = "Вы пошли вниз";
            break;
        case left:
            (*heroX)--; 
            message = "Вы пошли налево";
            break;
        case right:
            (*heroX)++; 
            message = "Вы пошли направо";
            break;
    }

    logMessage(message, log);

    if (map[*heroY][*heroX] == 'T') {
        *HP -= 40; 
        *lastCell = map[*heroY][*heroX];
        map[*heroY][*heroX] = '@';

        logMessage("Вы наступили на ловушку, HP - 40", log);
    } else if (map[*heroY][*heroX] != '#') {
        *lastCell = map[*heroY][*heroX];
        map[*heroY][*heroX] = '@';
    } else {
        *heroX = lastX;
        *heroY = lastY;
        map[lastY][lastX] = '@';
    }
}

void heroAction (char map[][20], int *heroX, int *heroY, char *lastCell, int *HP, string log[]) {
    char userAction = getch();

    if ((int)userAction == 27)
        moveHero(map, heroX, heroY, lastCell, HP, log);
}

