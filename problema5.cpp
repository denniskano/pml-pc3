//
// Created by Grupo4 on 12/07/25.
//
#include <iostream>
#include <string>
#include <set>
using namespace std;

bool verificarPropiedad(const string& secuencia) {
    int n = secuencia.length();

    // Para cada longitud de ventana k desde 1 hasta n
    for (int k = 1; k <= n; k++) {
        set<string> patrones;

        // Obtener todos los patrones de longitud k
        for (int i = 0; i <= n - k; i++) {
            string patron = secuencia.substr(i, k);
            patrones.insert(patron);
        }

        // Verificar si hay más de k+1 patrones diferentes
        if (patrones.size() > k + 1) {
            return false;
        }
    }

    return true;
}

int encontrarInfractor(const string& secuencia) {
    int n = secuencia.length();

    // Verificamos cada prefijo de la secuencia
    for (int prefijo = 1; prefijo <= n; prefijo++) {
        string subsecuencia = secuencia.substr(0, prefijo);

        if (!verificarPropiedad(subsecuencia)) {
            return prefijo;
        }
    }

    return n;
}

int main() {
    string linea;
    int numeroSecuencia = 1;

    while (true) {
        cout << "Secuencia " << numeroSecuencia << ": ";
        getline(cin, linea);

        if (linea.empty()) {
            cout << "Programa terminado." << endl;
            break;
        }

        cout << "Verificando: \"" << linea << "\"" << endl;

        if (verificarPropiedad(linea)) {
            cout << "Resultado: SI" << endl;
        } else {
            int posicionInfractor = encontrarInfractor(linea);
            cout << "Resultado: NO:" << posicionInfractor << endl;
            cout << "El simbolo en la posicion " << posicionInfractor
                 << " ('" << linea[posicionInfractor-1] << "') es el primer infractor." << endl;
        }

        cout << endl;
        numeroSecuencia++;
    }

    return 0;
}