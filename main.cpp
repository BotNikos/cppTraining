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
        1,   // x
        1,   // y
        10,  // damage
        {},  // inventory
        0,   // clearInventoryslot
        Floor, // lastCell
    };

    // filling hero inventory with empty slots
    for (int i = 0; i < 20; i++)
        hero.inventory[i] = 0;

    struct item itemList[] = {
    // id, name, description
        -1, "", "Пустой элемент",
        6, "Зелье", "восстанавливает 20 ОЗ",
        7, "Яд", "отнимает 20 ОЗ",
    };
    int itemListSize = sizeof(itemList)/sizeof(item);

    int inventoryMode = 0;
    int inventoryCursorPosition = 2;

    int battleMode = 0;
    int battleAction = 2; // 0 - Attack; 1 - Spells; 2 - Item; 3 - Escape;
    struct enemy battler;

    int newLevel = 0;
    int currentLevel = 1;
    enum cells map[20][20];
    memmove(map, newLevelStyle, 1600); // copying 400 bytes from level1 to map array

    struct enemy enemiesList[] = {
    // name, hp, damage
        "Rat", 20, 3, 
        "Goblin", 40, 10, 
        "Slime", 30, 1, 
    };

    int enemiesSize = sizeof(enemiesList)/sizeof(enemy);

    string log[10] = {
        "Привет. Это консоль, для вывода лога твоих",
        "действий.",
        "Ты можешь перемещаться с помощью стрелок.",
        "E - исследовать клетку",
    };

    while (1 == 1) {
        system("clear");
        reload(
            map, 20, &hero, log, itemList, itemListSize,
            inventoryMode, inventoryCursorPosition,
            enemiesList, enemiesSize, battleMode, &battler,
            battleAction 
        );

        heroAction(
            map, &hero, log,
            itemList, itemListSize,
            &inventoryMode, &inventoryCursorPosition,
            enemiesList, enemiesSize, &battleMode, &battler,
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
