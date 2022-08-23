#include <iostream>
using namespace std;

void showInfo (int *heroX, int *heroY, int *HP, char *lastCell) {
    cout << "\033[s";
    cout << "\033[1;26H" << "User info:";
    cout << "\033[3;26H" << "HP: " << *HP;
    cout << "\033[4;26H" << "X: " << *heroX << " Y: " << *heroY;
    cout << "\033[5;26H" << "Cell under hero: " << *lastCell;
    cout << "\033[u";
}

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

void showLog (string log[]) {
    cout << "-------------------------------------------" << '\n';
    for (int i = 0; i < 10; i++) {
        cout << log[i] << '\n';
    }
    cout << "-------------------------------------------" << '\n';
}

void logMessage (string message, string log[]) {
    for (int i = 1; i < 10; i++) {
        log[i - 1] = log[i];
    }

    log[9] = message;
}

void reload (char map[][20], int *heroY, int *heroX, int mapSize, int *HP, char *lastCell, string log[]) {
    drawMap(map, *heroY, *heroX, mapSize);
    showInfo(heroX, heroY, HP, lastCell);
    showLog(log);
}
