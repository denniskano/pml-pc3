#include <iostream>
using namespace std;

int main() {
    int casos[3][8] = {
        {12, 15, 13, 11, 0, 0, 0, 0},
        {2, 2, 1, 5, 3, 8, 7, 3},
        {2, 5, 3, 1, 3, 1, 0, 0}
    };
    int tamanos[3] = {4, 8, 6};

    for (int c = 0; c < 3; c++) {
        cout << "Caso " << c + 1 << " - Bloques: ";
        for (int i = 0; i < tamanos[c]; i++) {
            cout << casos[c][i] << " ";
        }
        cout << endl;

        int l = 0, r = tamanos[c] - 1;
        int vaca1 = 0;
        bool turno = true;
        while (l <= r) {
            if (turno) {
                if (casos[c][l] >= casos[c][r]) {
                    vaca1 += casos[c][l];
                    l++;
                } else {
                    vaca1 += casos[c][r];
                    r--;
                }
            } else {
                if (casos[c][l] >= casos[c][r]) {
                    l++;
                } else {
                    r--;
                }
            }
            turno = !turno;
        }
        cout << "vaca 1 comio: " << vaca1 << endl << endl;
    }
    return 0;
}