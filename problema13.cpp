/*
Problema 13: Compresión de Imagen

---
Salidas al correr el programa:

  0 120   0 
120 255 120 
  0 120   0
---
*/

#include <iostream>
using namespace std;

struct Imagen {
    int nFilas, nColumnas;
    int X[6][9]; // tamaño máximo para este ejemplo
};

int main() {
    Imagen img = {
        6, 9,
        {
            { 0, 120, 0, 0, 120, 0, 0, 120, 0 },
            { 120, 255, 120, 120, 255, 120, 120, 255, 120 },
            { 0, 120, 0, 0, 120, 0, 0, 120, 0 },
            { 0, 120, 0, 0, 120, 0, 0, 120, 0 },
            { 120, 255, 120, 120, 255, 120, 120, 255, 120 },
            { 0, 120, 0, 0, 120, 0, 0, 120, 0 }
        }
    };

    int minFilas = img.nFilas;
    int minCols = img.nColumnas;

    // Busca el menor tamaño posible
    for (int f = 1; f <= img.nFilas; f++) {
        if (img.nFilas % f != 0) continue;
        for (int c = 1; c <= img.nColumnas; c++) {
            if (img.nColumnas % c != 0) continue;
            bool ok = true;
            for (int i = 0; i < img.nFilas && ok; i++)
                for (int j = 0; j < img.nColumnas && ok; j++)
                    if (img.X[i][j] != img.X[i % f][j % c])
                        ok = false;
            if (ok) {
                minFilas = f;
                minCols = c;
                goto imprimir;
            }
        }
    }

imprimir:
    // Imprime la subimagen mínima
    for (int i = 0; i < minFilas; i++) {
        for (int j = 0; j < minCols; j++)
            printf("%3d ", img.X[i][j]);
        printf("\n");
    }
    return 0;
}

