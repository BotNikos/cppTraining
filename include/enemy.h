struct enemy {
    std::string name;
    char symb;
    int HP;
    int damage;
    char lastCell;
    int x;
    int y;
};

void enemyAction (char map[][20], struct hero *hero,
                  struct enemy enemies[], int *enemiesSize);

void clearEnemies (struct enemy enemies[], int *enemiesSize);
