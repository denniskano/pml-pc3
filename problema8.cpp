//
// Created by Grupo4 on 15/07/25.
//
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Estructura para una celda de la matriz
struct Celda {
    int fila;
    int columna;
    int valor;
    Celda* siguiente;

    Celda(int f, int c, int v) : fila(f), columna(c), valor(v), siguiente(nullptr) {}
};

// Clase matriz dispersa
class MatrizDispersa {
private:
    Celda* cabeza;  // Primer nodo de la lista
    int numCeldas;

public:
    // Constructor
    MatrizDispersa() : cabeza(nullptr), numCeldas(0) {}

    // Destructor
    ~MatrizDispersa() {
        limpiar();
    }

    // Limpiar la lista
    void limpiar() {
        while (cabeza != nullptr) {
            Celda* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
        numCeldas = 0;
    }

    // Insertar una celda en la lista
    void insertarCelda(int fila, int columna, int valor) {
        if (valor == 0) return; // No almacenar celdas con valor 0

        Celda* nueva = new Celda(fila, columna, valor);

        // Insertar al inicio de la lista
        nueva->siguiente = cabeza;
        cabeza = nueva;
        numCeldas++;
    }

    // Mostrar todas las celdas almacenadas
    void mostrarCeldas() const {
        cout << "Celdas:" << endl;
        cout << "Fila\tColumna\tValor" << endl;
        cout << "------------------------" << endl;

        Celda* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->fila << "\t\t" << actual->columna << "\t\t" << actual->valor << endl;
            actual = actual->siguiente;
        }
        cout << endl;
    }

    // Calcular la suma de elementos por fila
    void calcularSumasPorFila() const {
        map<int, int> sumasPorFila;

        // Recorrer toda la lista y acumular por fila
        Celda* actual = cabeza;
        while (actual != nullptr) {
            sumasPorFila[actual->fila] += actual->valor;
            actual = actual->siguiente;
        }

        cout << "Suma por fila:" << endl;
        cout << "Fila\tSuma" << endl;
        cout << "---------------" << endl;

        int sumaMaxima = 0;
        vector<int> filasConSumaMaxima;

        // Mostrar sumas y encontrar la maxima
        for (auto& par : sumasPorFila) {
            int fila = par.first;
            int suma = par.second;

            cout << fila << "\t\t" << suma << endl;

            if (suma > sumaMaxima) {
                sumaMaxima = suma;
                filasConSumaMaxima.clear();
                filasConSumaMaxima.push_back(fila);
            } else if (suma == sumaMaxima) {
                filasConSumaMaxima.push_back(fila);
            }
        }

        cout << endl;

        // Mostrar resultado
        cout << "Suma maxima: " << sumaMaxima << endl;
        cout << "En fila(s): ";
        for (int i = 0; i < filasConSumaMaxima.size(); i++) {
            cout << filasConSumaMaxima[i];
            if (i < filasConSumaMaxima.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
};

int main() {

    MatrizDispersa matriz;

    int n;
    cout << "Ingrese el numero de celdas a almacenar: ";
    cin >> n;

    cout << "\nIngrese las celdas en formato: fila columna valor" << endl;

    for (int i = 0; i < n; i++) {
        int fila, columna, valor;
        cout << "Celda " << (i + 1) << ": ";
        cin >> fila >> columna >> valor;

        matriz.insertarCelda(fila, columna, valor);
    }

    cout << "\n=== RESULTADO ===" << endl;

    matriz.mostrarCeldas();

    matriz.calcularSumasPorFila();

    return 0;
}