/*
Problema 12: Dobletes

---
Entradas y salidas al correr el programa:

booster
rooster
roaster
coasted
roasted
coastal
postal
booster roasted
coastal postal

---
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
using namespace std;

// Diccionario
vector<string> diccionario;

// Estructura para guardar dobletes
struct Par {
    string origen, destino;
};
vector<Par> pares;

int indicePalabra(const string& w) {
    for (int i = 0; i < diccionario.size(); i++)
        if (diccionario[i] == w)
            return i;
    return -1;
}

bool difUnaLetra(const string& a, const string& b) {
    if (a.size() != b.size()) return false;
    int dif = 0;
    for (int i = 0; i < a.size(); i++)
        if (a[i] != b[i] && ++dif > 1) return false;
    return dif == 1;
}

void procesarConsulta(const string& inicio, const string& destino, bool primera) {
    int start = indicePalabra(inicio);
    int goal = indicePalabra(destino);

    if (!primera) cout << '\n';

    if (start == -1 || goal == -1) {
        cout << "No solution." << endl;
        return;
    }

    vector<bool> visitado(diccionario.size(), false);
    vector<int> parent(diccionario.size(), -1);

    queue<int> q;
    q.push(start);
    visitado[start] = true;

    // Se usa BFS para encontrar el camino más corto
    bool encontrado = false;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == goal) { encontrado = true; break; }
        for (int v = 0; v < diccionario.size(); v++) {
            if (!visitado[v] && difUnaLetra(diccionario[u], diccionario[v])) {
                visitado[v] = true;
                parent[v] = u;
                q.push(v);
                if (v == goal) { encontrado = true; break; }
            }
        }
    }

    if (!encontrado) {
        cout << "No solution." << endl;
        return;
    }

    // Imprimir el camino
    vector<int> camino;
    for (int at = goal; at != -1; at = parent[at])
        camino.push_back(at);

    for (int i = camino.size() - 1; i >= 0; i--)
        cout << diccionario[camino[i]] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. Leer el diccionario y primer doblete
    string linea;
    while (getline(cin, linea)) {
        if (linea.empty()) continue; // saltar líneas vacías
        istringstream iss(linea);
        string w1, w2;
        iss >> w1 >> w2;
        if (!w2.empty()) {
            // Es un doblete, no del diccionario
            pares.push_back({w1, w2});
            break;
        } else {
            diccionario.push_back(w1);
        }
    }

    // 2. Leer el resto de los dobletes
    while (getline(cin, linea)) {
        if (linea.empty()) break; // fin de los dobletes
        istringstream iss(linea);
        string w1, w2;
        iss >> w1 >> w2;
        if (!w1.empty() && !w2.empty()) {
            pares.push_back({w1, w2});
        }
    }

    // 3. Procesar los dobletes
    bool primera = true;
    for (const auto& par : pares) {
        procesarConsulta(par.origen, par.destino, primera);
        primera = false;
    }

    return 0;
}
