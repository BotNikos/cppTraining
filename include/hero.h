#include <iostream>
#include "interface.h"

struct hero {
    int HP;
    int x;
    int y;
    int damage;
    int inventory[20];
    int clearInventorySlot;
    enum cells lastCell;
};

void heroAction(enum cells map[][20], struct hero *hero, std::string log[],
                struct item itemList[], int itemListSize,
                int *inventoryMode, int *inventoryCursorPosition,
                struct enemy enemies[], int ememySize, int *battleMode,
                struct enemy *battler, int *currentLevel, int *newLevel,
                int *battleAction);
