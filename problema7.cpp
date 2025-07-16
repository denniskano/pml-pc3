//
// Created by Grupo4 on 15/07/25.
//
#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int digito;     // 0 o 1
    Nodo* siguiente;

    Nodo(int d) : digito(d), siguiente(nullptr) {}
};

// Clase numeros binarios como listas enlazadas
class NumeroBinario {
private:
    Nodo* cabeza;   // Apunta al dígito menos significativo

public:
    // Constructor
    NumeroBinario() : cabeza(nullptr) {}

    // Destructor
    ~NumeroBinario() {
        limpiar();
    }

    // Limpiar la lista
    void limpiar() {
        while (cabeza != nullptr) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    // Insertar dígito al final (más significativo)
    void insertarAlFinal(int digito) {
        Nodo* nuevo = new Nodo(digito);

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    // Insertar dígito al inicio (menos significativo)
    void insertarAlInicio(int digito) {
        Nodo* nuevo = new Nodo(digito);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    // Crear número binario desde string (almacena invertido)
    void crearDesdeString(const string& binario) {
        limpiar();

        // Insertar dígitos desde el final hacia el inicio
        for (int i = binario.length() - 1; i >= 0; i--) {
            if (binario[i] == '0' || binario[i] == '1') {
                insertarAlInicio(binario[i] - '0');
            }
        }
    }

    // Mostrar el número binario
    void mostrar() const {
        if (cabeza == nullptr) {
            cout << "0";
            return;
        }

        // Primero contar cuántos nodos hay
        int count = 0;
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            count++;
            temp = temp->siguiente;
        }

        // Crear array temporal para mostrar en orden correcto
        int* digitos = new int[count];
        temp = cabeza;
        for (int i = 0; i < count; i++) {
            digitos[i] = temp->digito;
            temp = temp->siguiente;
        }

        // Mostrar desde el mas significativo
        for (int i = count - 1; i >= 0; i--) {
            cout << digitos[i];
        }

        delete[] digitos;
    }

    // Mostrar como lista (del menos al mas significativo)
    void mostrarComoLista() const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->digito;
            if (actual->siguiente != nullptr) {
                cout << " ";
            }
            actual = actual->siguiente;
        }
    }

    // Sumar dos números binarios
    static NumeroBinario sumar(const NumeroBinario& num1, const NumeroBinario& num2) {
        NumeroBinario resultado;
        Nodo* p1 = num1.cabeza;
        Nodo* p2 = num2.cabeza;
        int acarreo = 0;

        // Sumar dígito por dígito desde el menos significativo
        while (p1 != nullptr || p2 != nullptr || acarreo != 0) {
            int suma = acarreo;

            if (p1 != nullptr) {
                suma += p1->digito;
                p1 = p1->siguiente;
            }

            if (p2 != nullptr) {
                suma += p2->digito;
                p2 = p2->siguiente;
            }

            // El dígito resultado es suma % 2
            resultado.insertarAlFinal(suma % 2);

            // El nuevo acarreo es suma / 2
            acarreo = suma / 2;
        }

        return resultado;
    }

    // Verificar si la lista está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

int main() {

    string binario1, binario2;

    cout << "Ingrese el primer binario: ";
    cin >> binario1;

    cout << "Ingrese el segundo binario: ";
    cin >> binario2;

    // Validar entrada
    for (char c : binario1) {
        if (c != '0' && c != '1') {
            cout << "Error: El primer numero no es binario" << endl;
            return 1;
        }
    }

    for (char c : binario2) {
        if (c != '0' && c != '1') {
            cout << "Error: El segundo numero no es binario" << endl;
            return 1;
        }
    }

    NumeroBinario num1, num2;
    num1.crearDesdeString(binario1);
    num2.crearDesdeString(binario2);

    NumeroBinario resultado = NumeroBinario::sumar(num1, num2);

    cout << "----------------------------------------------" << endl;

    cout << binario1 << "\t\t\t";
    num1.mostrarComoLista();
    cout << endl;

    cout << binario2 << "\t\t\t";
    num2.mostrarComoLista();
    cout << endl;

    cout << "Resultado ";
    resultado.mostrar();
    cout << "\t\t";
    resultado.mostrarComoLista();
    cout << endl;

    return 0;
}