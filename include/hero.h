#include <iostream>

struct hero {
    int HP;
    int x;
    int y;
    int damage;
    int inventory[20];
    int clearInventorySlot;
    char lastCell;
};

void heroAction(char map[][20], int *heroX, int *heroY,
                char *lastCell,
                int *HP, std::string log[],
                int inventory[], int *clearInventorySlot,
                std::string itemList[][2], int itemMap[][3],
                int itemMapSize, int *inventoryMode, int *inventoryCursorPosition,
                struct enemy enemies[], int ememySize, int *battleMode,
                struct enemy *battler, int *currentLevel, int *newLevel);
