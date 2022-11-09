#include <iostream>
#include "include/conio.h"

using namespace std;

int main () {
    int cursorX = 0;
    int cursorY = 0;

    while (1 == 1) {
        system ("clear");

        // right border of map
        for (int i = 0; i <= 20; i++)
            cout << "\033[" << i << ";40H" << "|";


        // left border of map
        for (int i = 0; i <= 40; i++)
            cout << "\033[21;" << i << "H" << "-";

        cout << "\n";
        cout << "\033[s";
        cout << "\033[" << cursorY << ";" << cursorX << "H" << "X";
        cout << "\033[u";

        getch();
        getch();
        int userDirection = getch();

        enum dirctions {up = 65, down, right, left};
        switch (userDirection) {
            case up: cursorY--; break;
            case down: cursorY++; break;
            case left: cursorX--; break;
            case right: cursorX++; break;
        }

        if (cursorX > 39)
            cursorX = 39;

        if (cursorY > 20)
            cursorY = 20;
    }


    return 0;
}
