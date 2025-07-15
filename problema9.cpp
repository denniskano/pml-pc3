#include <iostream>
#include <string>
using namespace std;

struct Espia {
    string nombre;
    Espia* siguiente;
    Espia(string _nombre) {
        nombre = _nombre;
        siguiente = nullptr;
    }
};

int numeroEspias(Espia* espiaInicial) {
    if (!espiaInicial) return 0;
    int count = 1;
    Espia* actual = espiaInicial->siguiente;
    while (actual != nullptr && actual != espiaInicial) {
        count++;
        actual = actual->siguiente;
    }
    return count;
}

Espia* avanzar(Espia* espiaInicial, int X) {
    Espia* actual = espiaInicial;
    for (int i = 0; i < X; i++) {
        actual = actual->siguiente;
    }
    return actual;
}

Espia* ultimoSobreviviente(Espia* espiaInicial, int K) {
    if (!espiaInicial || K <= 0) return espiaInicial;

    Espia* actual = espiaInicial;

    while (actual->siguiente != actual) {
        // Avanzar K-1 para llegar al que debe morir
        Espia* eliminado = avanzar(actual, K - 1);

        // Buscar el anterior al eliminado
        Espia* anterior = eliminado;
        while (anterior->siguiente != eliminado) {
            anterior = anterior->siguiente;
        }

        cout << "Muere: " << eliminado->nombre << endl;

        //pDiego->siguiente = pPamela;
        anterior->siguiente = eliminado->siguiente;
        actual = eliminado->siguiente;
        delete eliminado;
    }

    return actual;
}


Espia* crearCirculoEspias(string nombres[], int n) {
    if (n == 0) return nullptr;
    Espia* cabeza = new Espia(nombres[0]);
    Espia* actual = cabeza;

    for (int i = 1; i < n; i++) {
        actual->siguiente = new Espia(nombres[i]);
        actual = actual->siguiente;
    }

    actual->siguiente = cabeza; // relaciona circulo de espia
    return cabeza;
}

int main() {
    //ejeplo
    string nombres[] = {"Diego", "Lucas", "Ana", "María", "Paulo"};
    int N = 5;
    int K = 3;

    Espia* inicio = crearCirculoEspias(nombres, N);

    cout << "Cantidad de espías: " << numeroEspias(inicio) << endl;

    Espia* sobreviviente = ultimoSobreviviente(inicio, K);
    cout << "Último sobreviviente: " << sobreviviente->nombre << endl;

    delete sobreviviente;
    return 0;
}