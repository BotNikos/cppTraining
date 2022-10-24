#include <iostream>
void logMessage (std::string message, std::string log[]);
void reload (char map[][20], int mapSize, struct hero *hero,
             std::string log[], std::string itemList[][2],
	     int inventoryMode, int inventoryCursorPosition,
             struct enemy enemies[], int enemiesSize,
             int battleMode, struct enemy *battler, int battleAction);
