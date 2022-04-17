#include <iostream>

#include "conio.h"

using namespace std;

void drawMap (char map[][20], int heroY, int heroX, int mapSize) {

    const string defaultColor = "\033[0m";
    const string yellowColor = "\033[0;33m";
    const string greenColor = "\033[0;36m";
    const string redColor = "\033[0;31m";


    int startCoordsY = ((heroY - 5) < 0) ? 0 : ((heroY + 5) >= mapSize) ? mapSize - 11 : heroY - 5;
    int startCoordsX = ((heroX - 5) < 0) ? 0 : ((heroX + 5) >= mapSize) ? mapSize - 11 : heroX - 5;

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            char currentCell = map[startCoordsY + i][startCoordsX + j];

            if (currentCell == '#') 
                cout << yellowColor;
            else if (currentCell == '@')
                cout << greenColor;
            else if (currentCell == 'T') {
                cout << redColor << ". ";
            }
            else 
                cout << defaultColor;

            if (currentCell != 'T')
                cout << currentCell << " ";
        }
        
        cout << '\n';
    }

    cout << defaultColor;
}

void moveHero(char map[][20], int *heroX, int *heroY) {
    enum dirctions {up = 65, down, right, left};

    int userDirection = getch();

    int lastY = *heroY;
    int lastX = *heroX;

    map[*heroY][*heroX] = '.';
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

    if (map[*heroY][*heroX] != '#')
        map[*heroY][*heroX] = '@';
    else {
        *heroX = lastX;
        *heroY = lastY;
        map[lastY][lastX] = '@';
    }


}
int main (void) {
    int heroX = 1;
    int heroY = 1;
    int HP = 100;

    char map[20][20] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '@', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', 'T', '#', '.', '#', '.', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '.', '#', '#', '.', '#', '#', '#', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '#', '#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#', '.', '#', '#', '#', '#', '#', '#', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '.', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '#', '#', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '.', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };


    while (1 == 1) {
        system("clear");
        cout << "X: " << heroX << " Y: " << heroY << " HP: " << HP << '\n';
        drawMap(map, heroY, heroX, 20);
        moveHero(map, &heroX, &heroY);
    }

    return 0;
}
