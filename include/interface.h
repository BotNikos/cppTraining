#include <iostream>
void logMessage (std::string message, std::string log[]);
void reload (char map[][20], int *heroY, int *heroX,
             int mapSize, int *HP, char *lastCell,
             std::string log[], int inventory[],
             int clearInventorySlot, std::string itemList[][2],
	     int inventoryMode, int inventoryCursorPosition,
             struct enemy enemies[], int enemiesSize);
