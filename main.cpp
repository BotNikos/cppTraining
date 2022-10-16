#include <iostream>
#include <cstring>

#include "include/hero.h"
#include "include/enemy.h"
#include "include/interface.h"
#include "include/levels.h"

#include "include/conio.h"

using namespace std;

int main () {
    struct hero hero = {
        100,                                                           // HP
        2,                                                             // x
        1,                                                             // y
        10,                                                            // damage
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  // inventory
        0,                                                             // clearInventoryslot
        '.',                                                           // lastCell
    };

    string itemList[][2] = {
        {"", "Пустой элемент"},
        {"Зелье", "восстанавливает 20 ОЗ"},
        {"Яд", "отнимает 20 ОЗ"}
    };

    // data structure {item number from item arr, item y, item x}
    int itemMap[][3] = {
        {1, 1, 3},
        {2, 6, 2}
    };

    int inventoryMode = 0;
    int inventoryCursorPosition = 2;

    int battleMode = 0;
    struct enemy battler;

    int newLevel = 0;
    int currentLevel = 1;
    char map[20][20];
    memmove(map, level1, 400); // copying 400 bytes from level1 to map array

    struct enemy enemies[] = {"Rat", 'R', 20, 3, '.', 3, 2, "Goblin", 'G', 40, 10, '.', 2, 2};
    int enemiesSize = sizeof(enemies)/sizeof(enemy);

    string log[10] = {
        "Привет. Это консоль, для вывода лога твоих",
        "действий.",
        "Ты можешь перемещаться с помощью стрелок.",
        "E - исследовать клетку",
    };

    while (1 == 1) {
        system("clear");
        reload(
            map, 20, &hero, log, itemList,
	    inventoryMode, inventoryCursorPosition,
            enemies, enemiesSize, battleMode, &battler
        );

        heroAction(
            map, &hero, log,
            itemList, itemMap, sizeof(itemMap),
	    &inventoryMode, &inventoryCursorPosition,
            enemies, enemiesSize, &battleMode, &battler,
            &currentLevel, &newLevel
        );

        // if (newLevel) {
        //     heroX = 1;
        //     heroY = 1;
        //     memmove(map, level2, 400);
        //     clearEnemies(enemies, &enemiesSize);
        //     newLevel = 0;
        //     logMessage("Вы перешли на новый уровень", log);
        // }

        // enemyAction(map, heroX, heroY, enemies, &enemiesSize);
    }

    return 0;
}
