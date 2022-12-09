#include <iostream>

#ifndef INTERFACE_H
#define INTERFACE_H
enum cells {
    Wall, Floor, Player, Trap, Item, Up,

    // items, after appending item here, append it to:
    // main.cpp [28], lib/hero.cpp [58], lib/interface.cpp [46], include/levels
    Potion,
    Poison
};

struct item {
    int id; // number in cells enum above
    std::string name;
    std::string description;
};

#endif


void logMessage (std::string message, std::string log[]);
void reload (enum cells map[][20], int mapSize, struct hero *hero,
             std::string log[],  struct item itemList[], int itemListSize,
	     int inventoryMode, int inventoryCursorPosition,
             struct enemy enemies[], int enemiesSize,
             int battleMode, struct enemy *battler, int battleAction);
