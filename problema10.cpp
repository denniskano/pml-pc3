#include <iostream>
#include <stack>
#include <string>
using namespace std;

string eliminarPares(string s) {
    stack<char> pila;

    for (char c : s) {
        if (!pila.empty() && pila.top() == c) {
            // busca un par consecutivo
            pila.pop();
        } else {
            pila.push(c);
        }
    }

    // genera la nueva cadena
    string resultado = "";
    while (!pila.empty()) {
        resultado = pila.top() + resultado;
        pila.pop();
    }

    return resultado;
}

/*int main() {
    string linea;
    cin >> linea;

    string resultado = eliminarPares(linea);
    cout << resultado << endl;

    return 0;
}*/

int main() {
    // Ejemplos de prueba
    string ejemplo1 = "hhoowaaaareyyoouu";
    string ejemplo2 = "reallazy";
    string ejemplo3 = "abacabaabacabaa";

    cout << "Entrada: " << ejemplo1 << endl;
    cout << "Salida:  " << eliminarPares(ejemplo1) << endl << endl;

    cout << "Entrada: " << ejemplo2 << endl;
    cout << "Salida:  " << eliminarPares(ejemplo2) << endl << endl;

    cout << "Entrada: " << ejemplo3 << endl;
    cout << "Salida:  " << eliminarPares(ejemplo3) << endl << endl;

    return 0;
}

