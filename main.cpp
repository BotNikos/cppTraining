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
        
        cout << defaultColor << " |" << '\n';
    }

    cout << defaultColor;
}

void showInfo (int *heroX, int *heroY, int *HP, char *lastCell) {
    cout << "\033[s";
    cout << "\033[1;26H" << "HP: " << *HP;
    cout << "\033[2;26H" << "X: " << *heroX << " Y: " << *heroY;
    cout << "\033[3;26H" << "Cell under hero: " << *lastCell;
    cout << "\033[u";
}

void showMessage (string message) {
    cout << "\033[s";
    cout << "\033[5;26H" << "\033[3m" << message << "\033[0m" ;
    cout << "\033[u";
}

void moveHero(char map[][20], int *heroX, int *heroY, char *lastCell, int *HP) {
    enum dirctions {up = 65, down, right, left};

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


int main (void) {
    int heroX = 1;
    int heroY = 1;
    int HP = 100;
    char lastCell = '.';

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
        showInfo(&heroX, &heroY, &HP, &lastCell);
        drawMap(map, heroY, heroX, 20);
        moveHero(map, &heroX, &heroY, &lastCell, &HP);
    }

    return 0;
}
