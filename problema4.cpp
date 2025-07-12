#include <iostream>
#include <vector>
using namespace std;

int contarCaminosDFS(int actual, int destino, const vector<vector<int>>& grafo) {
    if (actual == destino) return 1;

    int caminos = 0;
    for (size_t i = 0; i < grafo.size(); ++i) {
        if (grafo[actual][i] == 1) {
            caminos += contarCaminosDFS(i, destino, grafo);
        }
    }
    return caminos;
}

int main() {
    int numeroDeCasos = 2;

    vector<vector<vector<int>>> matrices = {
        { // Caso 1
            {0, 1, 0, 1},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        },
        { // Caso 2
                {0, 1, 0, 1, 0, 0, 0},
                {0, 0, 1, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 1, 0},
                {0, 0, 1, 0, 1, 0, 0},
                {0, 0, 0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0, 0, 1},
                {0, 0, 0, 0, 0, 0, 0}
        }
    };

    vector<pair<int, int>> origenDestino = {
        {0, 3},
        {1, 4}
    };

    cout << "** DATOS DE ENTRADA **\n";
    cout << numeroDeCasos << "\n\n";

    for (int i = 0; i < numeroDeCasos; ++i) {
        const auto& matriz = matrices[i];
        cout << matriz.size() << "\n";
        for (const auto& fila : matriz) {
            for (int v : fila) cout << v << " ";
            cout << "\n";
        }
        cout << origenDestino[i].first << " " << origenDestino[i].second << "\n\n";
    }

    cout << "** DATOS DE SALIDA **\n";
    for (int i = 0; i < numeroDeCasos; ++i) {
        int resultado = contarCaminosDFS(
            origenDestino[i].first,
            origenDestino[i].second,
            matrices[i]
        );
        cout << resultado << "\n";
    }

    return 0;
}
