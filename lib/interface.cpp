#include <iostream>
#include "../include/enemy.h"
#include "../include/hero.h"

using namespace std;

void showInfo (struct hero *hero) {
    cout << "\033[s";
    cout << "\033[1;26H" << "User info:";
    cout << "\033[3;26H" << "HP: " << hero -> HP;
    cout << "\033[4;26H" << "X: " << hero -> x << " Y: " << hero -> y;
    cout << "\033[5;26H" << "Cell under hero: " << hero -> lastCell;
    cout << "\033[u";
}

void drawMap (char map[][20], int mapSize, struct hero *hero,
              struct enemy enemies[], int enemiesSize) {

    const string defaultColor = "\033[0m";
    const string yellowColor = "\033[0;33m";
    const string cyanColor = "\033[0;36m";
    const string greenColor = "\033[0;32m";
    const string redColor = "\033[0;31m";

    int startCoordsY = ((hero -> y - 5) < 0) ? 0 : ((hero -> y + 5) >= mapSize) ? mapSize - 11 : hero -> y - 5;
    int startCoordsX = ((hero -> x - 5) < 0) ? 0 : ((hero -> x + 5) >= mapSize) ? mapSize - 11 : hero -> x - 5;

    for (int i = 0; i < enemiesSize; i++) {
        map[enemies[i].y][enemies[i].x] = 'E';
    }

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            char currentCell = map[startCoordsY + i][startCoordsX + j];

            if (currentCell == '#') 
                cout << yellowColor;
            else if (currentCell == '@')
                cout << cyanColor;
            else if (currentCell == 'T') 
                cout << redColor << ". ";
            else if (currentCell == 'I')
                cout << greenColor << ". ";
            else if (currentCell == '^')
                cout << greenColor;
            else if (currentCell == 'E') {
                for (int e = 0; e < 2; e++) {
                    if (enemies[e].x == (startCoordsX + j) && enemies[e].y == (startCoordsY + i))
                        cout << redColor << enemies[e].symb << " ";
                }
            } else 
                cout << defaultColor;

            if (currentCell != 'T' && currentCell != 'I' && currentCell != 'E')
                cout << currentCell << " ";
        }
        
        cout << defaultColor << " |" << '\n';
    }

    cout << defaultColor;
}

void showInventory (struct hero *hero, string itemList[][2],
		    int inventoryMode, int inventoryCursorPosition) {
    for (int i = 0; i < 24; i++)
        cout << "\033[" << i << ";44H" << "|\n";


    cout << "\033[s";
    cout << "\033[0;47H" << "Инвентарь:";
    for (int i = 1; i <= hero -> clearInventorySlot; i++) {
        int itemId = hero -> inventory[i - 1];
        string itemName = itemList[itemId][0];
        string itemDesc = itemList[itemId][1];
        cout << "\033[" << i + 1 << ";47H" << itemName;
    }

    if (inventoryMode)
	cout << "\033[" << inventoryCursorPosition << ";45H" << ">";

    cout << "\033[u";
}

void showLog (string log[]) {
    cout << "\033[12;0H";
    cout << "-------------------------------------------" << '\n';
    for (int i = 0; i < 10; i++) {
        cout << "\033[2K" << log[i] << '\n';
    }
    cout << "-------------------------------------------" << '\n';
}

void logMessage (string message, string log[]) {
    for (int i = 1; i < 10; i++) {
        log[i - 1] = log[i];
    }

    log[9] = message;
}

//void showBattleScreen (int *HP, struct enemy *battler) {
    
//}

void reload (char map[][20], int mapSize, struct hero *hero,
             string log[], string itemList[][2], int inventoryMode,
	     int inventoryCursorPosition,
             struct enemy enemies[], int enemiesSize,
             int battleMode, struct enemy *battler) {

    if (battleMode) {
        showLog(log);
        logMessage("Вы деретесь против " + battler -> name, log);
    } else {
        drawMap(map, mapSize, hero, enemies, enemiesSize);
        showInfo(hero);
        showLog(log);
        showInventory(
            hero, itemList,
            inventoryMode, inventoryCursorPosition
        );
    }

}
