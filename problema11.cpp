#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// progresión aritmética
bool esPA(const vector<int>& v) {
    if (v.size() < 2) return false;
    int d = v[1] - v[0];
    for (int i = 2; i < v.size(); i++) {
        if (v[i] - v[i - 1] != d) return false;
    }
    return true;
}

// progresión geométrica
bool esPG(const vector<int>& v) {
    if (v.size() < 2) return false;
    if (v[0] == 0) return false; // no considera la division por 0
    int r = v[1] / v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i - 1] == 0 || v[i] % v[i - 1] != 0 || v[i] / v[i - 1] != r) {
            return false;
        }
    }
    return true;
}

// función de verificación
vector<int> verificador(int X[], int n, unordered_set<int> excluidos, bool (*verificador)(const vector<int>&)) {
    vector<int> mejor;

    // bitmask para todas las combinaciones posibles
    for (int mask = 1; mask < (1 << n); mask++) {
        vector<int> actual;
        unordered_set<int> usados;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i) && excluidos.count(X[i]) == 0) {
                actual.push_back(X[i]);
                usados.insert(X[i]);
            }
        }

        if (actual.size() >= 2) {
            sort(actual.begin(), actual.end());
            if (verificador(actual) && actual.size() > mejor.size()) {
                mejor = actual;
            }
        }
    }

    return mejor;
}



void imprimirProgresiones(int X[], int n) {
    // Encontrar la mejor PA
    unordered_set<int> vacio;
    vector<int> PA = verificador(X, n, vacio, esPA);

    // Marcar usados en PA
    unordered_set<int> usados(PA.begin(), PA.end());

    // Encontrar la mejor PG sin usar elementos de PA
    vector<int> PG = verificador(X, n, usados, esPG);

    // Imprimir resultados
    cout << "Progresión Aritmética: ";
    for (int num : PA) cout << num << " ";
    cout << endl;

    cout << "Progresión Geométrica: ";
    for (int num : PG) cout << num << " ";
    cout << endl;
}

/*void imprimirProgresiones(int X[], int n) {
    vector<int> A(X, X + n);

    vector<int> mejorPA;
    vector<int> mejorPG;
*/

int main() {
    int X[] = {1, 10, 9, 5, 7, 13, 100};
    int n = sizeof(X)/sizeof(X[0]);

    imprimirProgresiones(X, n);

    return 0;
}

