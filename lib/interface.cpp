#include <iostream>
#include "../include/enemy.h"
#include "../include/interface.h"
#include "../include/hero.h"

#include "../include/conio.h"

using namespace std;

void showInfo (struct hero *hero) {
    cout << "\033[s";
    cout << "\033[1;26H" << "User info:";
    cout << "\033[3;26H" << "HP: " << hero -> HP;
    cout << "\033[4;26H" << "X: " << hero -> x << " Y: " << hero -> y;
    cout << "\033[5;26H" << "Cell under hero: " << hero -> lastCell;
    cout << "\033[u";
}

void drawMap (enum cells map[][20], int mapSize, struct hero *hero,
              struct enemy enemies[], int enemiesSize) {

    const string defaultColor = "\033[0m";
    const string yellowColor = "\033[0;33m";
    const string cyanColor = "\033[0;36m";
    const string greenColor = "\033[0;32m";
    const string redColor = "\033[0;31m";

    int startCoordsY = ((hero -> y - 5) < 0) ? 0 : ((hero -> y + 5) >= mapSize) ? mapSize - 11 : hero -> y - 5;
    int startCoordsX = ((hero -> x - 5) < 0) ? 0 : ((hero -> x + 5) >= mapSize) ? mapSize - 11 : hero -> x - 5;

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            cells currentCell = map[startCoordsY + i][startCoordsX + j];

            switch (currentCell) {
                case Wall: cout << yellowColor << "#"; break;
                case Floor: cout << "."; break;
                case Player: cout << cyanColor << "@"; break;
                case Trap: cout << redColor << "."; break;

                // items
                case Potion:
                case Poison: cout << greenColor << "."; break;
            }

            cout << " ";
            cout << defaultColor;
        }
        
        cout << defaultColor << " |" << '\n';
    }

    cout << defaultColor;
}

void showInventory (struct hero *hero, struct item itemList[], int itemListSize,
		    int inventoryMode, int inventoryCursorPosition) {
    for (int i = 0; i < 24; i++)
        cout << "\033[" << i << ";44H" << "|\n";


    cout << "\033[s";
    cout << "\033[0;47H" << "Инвентарь:";
    for (int i = 0; i <= hero -> clearInventorySlot; i++) {
        int itemId = hero -> inventory[i];
        string itemName;
        string itemDesc;

        for (int i = 0; i < itemListSize; i++) {
            if (itemId == itemList[i].id) {
                itemName = itemList[i].name;
                itemDesc = itemList[i].description;
            }
        }

        cout << "\033[" << i + 2 << ";47H" << itemName;
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


void drawBorder (int x, int y, int stringSize) {

    cout << "\033[" << y << ";" << x << "H";
    for (int i = 0; i < 10; i++) {
        cout << "━";
    }

    cout << "\033[" << y << ";" << (x - 1) << "H" << "┏";
    cout << "\033[" << (y + 1) << ";" << (x - 1) << "H" << "┃";
    cout << "\033[" << (y + 2) << ";" << (x - 1) << "H" << "┗";

    cout << "\033[" << (y + 2) << ";" << x << "H";
    for (int i = 0; i < 10; i++) {
        cout << "━";
    }

    cout << "\033[" << y << ";" << (x + 10)  << "H" << "┓";
    cout << "\033[" << (y + 1) << ";" << (x + 10) << "H" << "┃";
    cout << "\033[" << (y + 2) << ";" << (x + 10) << "H" << "┛";

}

// 48 chars for map window

void showBattleScreen (struct hero *hero, struct enemy *battler, int battleAction, string log[]) {
    // enemy name and HP bar
    cout << "\033[0;0H" << battler -> name << " [";
    for (int i = 0; i < (39 - battler -> name.size()); i++) {
        cout << "█";
    }
    cout << "]";

    // user actions in battle
    cout << "\033[4;19H" << "Attack";
    drawBorder(17, 3, 6);    

    cout << "\033[7;5H" << "Spells";
    drawBorder(3, 6, 5);    

    cout << "\033[7;35H" << "Item";
    drawBorder(32, 6, 4);    

    cout << "\033[10;19H" << "Escape";
    drawBorder(17, 9, 7);    

    switch (battleAction) {
        case 0: cout << "\033[6;21H" << "▲▲"; break;
        case 1: cout << "\033[7;15H" << "◀"; break;
        case 2: cout << "\033[7;29H" << "▶"; break;
        case 3: cout << "\033[8;21H" << "▼▼"; break;
    }

}

void reload (enum cells map[][20], int mapSize, struct hero *hero,
             string log[], struct item itemList[], int itemListSize,
             int inventoryMode, int inventoryCursorPosition,
             struct enemy enemies[], int enemiesSize,
             int battleMode, struct enemy *battler, int battleAction) {

    if (battleMode) {
        showBattleScreen (hero, battler, battleAction, log);
        showLog(log);
        showInventory(
            hero, itemList, itemListSize,
            inventoryMode, inventoryCursorPosition
        );
    } else {
        drawMap(map, mapSize, hero, enemies, enemiesSize);
        showInfo(hero);
        showLog(log);
        showInventory(
            hero, itemList, itemListSize,
            inventoryMode, inventoryCursorPosition
        );
    }

}
