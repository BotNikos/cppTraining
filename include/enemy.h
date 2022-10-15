struct enemy {
    std::string name;
    char symb;
    int HP;
    int damage;
    char lastCell;
    int x;
    int y;
};

void enemyAction (char map[][20], int heroX, int heroY,
                  struct enemy enemies[], int *enemiesSize);
void clearEnemies (struct enemy enemies[], int *enemiesSize);
