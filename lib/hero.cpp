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

void examine (char map[][20], int *heroX, int *heroY, string log[], string itemList[][2], int itemMap[][3], int itemMapSize) {
    enum dirctions {up = 65, down, right, left};

    logMessage("", log);
    logMessage("Выберете направление клетки, которую вы", log);
    logMessage("хотите изучить", log);

    getch();
    getch();
    int direction = getch();

    int examineX = *heroX;
    int examineY = *heroY;
    switch (direction) {
        case up:
            examineY--; break;
        case down:
            examineY++; break;
        case left:
            examineX--; break;
        case right:
            examineX++; break;
    }

    logMessage("", log);
    switch (map[examineY][examineX]) {
        case '.':
            logMessage("Вы смотрите на холодный пол, и не можете", log); 
            logMessage("найти ничего примечательного", log); 
            break;
        case 'T':
            logMessage("Перед вами ловушка, которая может сделать", log); 
            logMessage("довольно больно", log); 
            break;
        case '#':
            logMessage("Ваше внимание привлекла стена, и", log); 
            logMessage("поразглядывав ее пару минут, вы поняли, что", log); 
            logMessage("тратите время впустую", log); 
            break;
        case  'I':
            string examineItem[2];
            for (int i = 0; i < itemMapSize; i++) {
                if (examineY == itemMap[i][1] && examineX == itemMap[i][2]) {
                    examineItem[0] = itemList[itemMap[i][0]][0];
                    examineItem[1] = itemList[itemMap[i][0]][1];
                }
            }

            logMessage("Перед вами лежит предмет: " + examineItem[0], log);
            logMessage("он " + examineItem[1], log);

            break;
    }
}

void heroAction (char map[][20], int *heroX, int *heroY, char *lastCell, int *HP, string log[], string itemList[][2], int itemMap[][3], int itemMapSize) {
    char userAction = getch();

    if ((int)userAction == 27)
        moveHero(map, heroX, heroY, lastCell, HP, log);
    else if (userAction == 'e') 
        examine(map, heroX, heroY, log, itemList, itemMap, itemMapSize);
}

