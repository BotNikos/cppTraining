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
        100, // HP
        2,   // x
        1,   // y
        10,  // damage
        {},  // inventory
        0,   // clearInventoryslot
        Floor, // lastCell
    };

    // filling hero inventory with empty slots
    for (int i = 0; i < 20; i++)
        hero.inventory[i] = 0;

    string itemList[][2] = {
        {"", "Пустой элемент"},
        {"Зелье", "восстанавливает 20 ОЗ"},
        {"Яд", "отнимает 20 ОЗ"}
    };

    // data structure {item number from item arr, item y, item x}
    int itemMap[][3] = {
        {1, 1, 3},
        {2, 6, 2},
        {1, 8, 2}
    };

    int inventoryMode = 0;
    int inventoryCursorPosition = 2;

    int battleMode = 0;
    int battleAction = 2; // 0 - Attack; 1 - Spells; 2 - Item; 3 - Escape;
    struct enemy battler;

    int newLevel = 0;
    int currentLevel = 1;
    enum cells map[20][20];
    memmove(map, newLevelStyle, 1600); // copying 400 bytes from level1 to map array

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
            enemies, enemiesSize, battleMode, &battler,
            battleAction 
        );

        heroAction(
            map, &hero, log,
            itemList, itemMap, sizeof(itemMap),
	    &inventoryMode, &inventoryCursorPosition,
            enemies, enemiesSize, &battleMode, &battler,
            &currentLevel, &newLevel, &battleAction
        );

        // if (newLevel) {
        //     hero.x = 1;
        //     hero.y = 1;
        //     memmove(map, level2, 400);
        //     clearEnemies(enemies, &enemiesSize);
        //     newLevel = 0;
        //     logMessage("Вы перешли на новый уровень", log);
        // }

        // enemyAction(map, &hero, enemies, &enemiesSize);
    }

    return 0;
}
