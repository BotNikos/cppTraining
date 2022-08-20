#include <iostream>
using namespace std;

void showInfo (int *heroX, int *heroY, int *HP, char *lastCell) {
    cout << "\033[s";
    cout << "\033[1;26H" << "HP: " << *HP;
    cout << "\033[2;26H" << "X: " << *heroX << " Y: " << *heroY;
    cout << "\033[3;26H" << "Cell under hero: " << *lastCell;
    cout << "\033[u";
}

void showMessage (string message) {
    cout << "\033[s";
    cout << "\033[5;26H" << "\033[3m" << message << "\033[0m" ;
    cout << "\033[u";
}
