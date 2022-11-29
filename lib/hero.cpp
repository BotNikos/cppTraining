#include <chrono>
#include <thread>
#include <iostream>

#include "../include/conio.h"
#include "../include/interface.h"
#include "../include/enemy.h"
#include "../include/hero.h"

using namespace std;

int findItem (enum cells items[], int itemsSize, enum cells target) {
    for (int i = 0; i < itemsSize; i++) {
        if (items[i] == target)
            return 1;
    }

    return 0;
}

void moveHero(enum cells map[][20], struct hero *hero, string log[],
              struct item itemList[], int itemListSize,
              int *currentLevel, int *newLevel) {

    enum dirctions {up = 65, down, right, left};

    char trash = getch();
    int userDirection = getch();

    int lastY = hero -> y;
    int lastX = hero -> x;

    map[hero -> y][hero -> x] = hero -> lastCell;
    string message;
    switch (userDirection) {
        case up:
            hero -> y--;
            message = "Вы пошли вверх";
            break;
        case down:
            hero -> y++;
            message = "Вы пошли вниз";
            break;
        case left:
            hero -> x--;
            message = "Вы пошли налево";
            break;
        case right:
            hero -> x++;
            message = "Вы пошли направо";
            break;
    }

    logMessage(message, log);

    enum cells currentCell = map[hero -> y][hero -> x];

    enum cells items[] = {Potion}; // Potion = 6 because is have enum cells data structure

    if (currentCell == Trap) {
        hero -> HP -= 40;
        hero -> lastCell = map[hero -> y][hero -> x];
        map[hero -> y][hero -> x] = Player;

        logMessage("Вы наступили на ловушку, HP - 40", log);
    }  else if (findItem(items, sizeof(items), currentCell)) {

        hero -> inventory[hero -> clearInventorySlot] = currentCell;
        hero -> clearInventorySlot++;
        hero -> lastCell = Floor;
        for (int i = 0; i < itemListSize; i++) {
            if (itemList[i].id == currentCell)
                logMessage("Вы подобрали: " + itemList[i].name, log);
        }
        map[hero -> y][hero -> x] = Player;

    } else if (currentCell == Up) {
        *newLevel = 1;
        *currentLevel++;
    } else if (currentCell != Wall) {
        hero -> lastCell = map[hero -> y][hero -> x];
        map[hero -> y][hero -> x] = Player;
    } else {
        hero -> x = lastX;
        hero -> y = lastY;
        map[lastY][lastX] = Player;
    }
}

void examine (enum cells map[][20], struct hero *hero, 
              string log[], struct item itemList[],
              int itemListSize) {

    enum dirctions {up = 65, down, right, left};

    // logMessage("", log);
    // logMessage("Выберете направление клетки, которую вы", log);
    // logMessage("хотите изучить", log);

    getch();
    getch();
    int direction = getch();

    int examineX = hero -> x;
    int examineY = hero -> y;

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
        case Floor:
            logMessage("Вы смотрите на холодный пол, и не можете", log); 
            logMessage("найти ничего примечательного", log); 
            break;
        case Trap:
            logMessage("Перед вами ловушка, которая может сделать", log); 
            logMessage("довольно больно", log); 
            break;
        case Wall:
            logMessage("Ваше внимание привлекла стена, и", log); 
            logMessage("поразглядывав ее пару минут, вы поняли, что", log); 
            logMessage("тратите время впустую", log); 
            break;
        case Potion:
            string itemName;
            string itemDesc;

            for (int i = 0; i < itemListSize; i++) {
                if (map[examineY][examineX] == itemList[i].id) {
                    itemName = itemList[i].name;
                    itemDesc = itemList[i].description;
                }
            }

            logMessage("Перед вами лежит предмет: " + itemName, log);
            logMessage("он " + itemDesc, log);
            break;
    }
}

void moveItemCursor (int *inventoryCursorPosition) {
    enum dirctions {up = 65, down};

    getch();
    int direction = getch();

    if (direction == up && *inventoryCursorPosition > 2)
	(*inventoryCursorPosition)--;
    else if (direction == down && *inventoryCursorPosition < 20)
	(*inventoryCursorPosition)++;
}

void useItem (struct hero *hero, string itemList[][2],
              int *inventoryCursorPosition,
              string log[], int *inventoryMode) {
    string currentItem = itemList[hero -> inventory[*inventoryCursorPosition - 2]][0];

    if (currentItem == "Зелье")
        hero -> HP += 20;
    else if (currentItem == "Яд")
        hero -> HP -= 20;
    else if (currentItem == "")
        logMessage("Вы выбрали пустую ячейку", log);
    else
        logMessage("Данный предмет не может быть использован", log);
 
    hero -> inventory[*inventoryCursorPosition - 2] = 0;
    *inventoryMode = 0;
}

void enemyCheck (struct enemy enemies[], int enemySize,
                 struct hero *hero, int *battleMode,
                 struct enemy *battler, string log[]) {
    
    for (int i = 0; i < enemySize; i++) {
        if (enemies[i].x == hero -> x && enemies[i].y == hero -> y) {
            *battleMode = 1;
            *battler = enemies[i];
            logMessage("Вы деретесь против " + battler -> name, log);
        }
    }
}

void moveBattleCursor (int *battleAction) {
    enum dirctions {up = 65, down, right, left};

    getch();
    int direction = getch();

    switch (direction){
        case up: *battleAction = 0; break;
        case left: *battleAction = 1; break;
        case right: *battleAction = 2; break;
        case down: *battleAction = 3; break;
    }

}

void heroAction (enum cells map[][20], struct hero *hero, string log[],
                 struct item itemList[], int itemListSize,
                 int *inventoryMode, int *inventoryCursorPosition,
                 struct enemy enemies[], int enemiesSize, int *battleMode,
                 struct enemy *battler, int *currentLevel, int *newLevel, int *battleAction) {

    char userAction = getch();

    if ((int)userAction == 27 && *inventoryMode == 0 && *battleMode == 0)
        moveHero(
            map, hero, log,
            itemList, itemListSize,
            currentLevel, newLevel
        );
    else if (userAction == 'e') 
        examine(map, hero, log, itemList, itemListSize);
    // else if (userAction == 'i')
    //     *inventoryMode = !(*inventoryMode);
    // else if ((int)userAction == 27 && *inventoryMode == 1)
    //     moveItemCursor(inventoryCursorPosition);
    // else if ((int)userAction == 27 && *battleMode == 1)
    //     moveBattleCursor(battleAction);
    // else if (userAction == '\n' && *inventoryMode == 1)
    //     useItem(hero, itemList, inventoryCursorPosition, log, inventoryMode);

    // if (*battleMode == 0)
    //     enemyCheck(enemies, enemiesSize, hero, battleMode, battler, log);
}

