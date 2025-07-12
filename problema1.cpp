#include <iostream>
#include <sstream>
using namespace std;

void procesarBuscaminas(const string& datos) {
    istringstream entrada(datos);
    int n, m, campo = 1;
    char tablero[100][100], salida[100][100];

    cout << "=== BUSCAMINAS ===\n";
    cout << "Datos de entrada:\n";
    cout << datos << "\n\n=== RESULTADO ===\n";

    while (entrada >> n >> m && (n != 0 && m != 0)) {
        entrada.get(); // Salta el salto de línea
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                entrada.get(tablero[i][j]);
            }
            entrada.get(); // Salta el salto de línea
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (tablero[i][j] == '*') {
                    salida[i][j] = '*';
                } else {
                    int minas = 0;
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx == 0 && dy == 0) continue;
                            int ni = i + dx, nj = j + dy;
                            if (ni >= 0 && ni < n && nj >= 0 && nj < m && tablero[ni][nj] == '*') {
                                minas++;
                            }
                        }
                    }
                    salida[i][j] = minas + '0';
                }
            }
        }
        cout << "Field #" << campo++ << ":\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << salida[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }
}


int main() {
    string datos = R"(4 4
*...
....
.*..
....
3 5
**...
.....
.*...
0 0)";

    procesarBuscaminas(datos);
    return 0;
}
