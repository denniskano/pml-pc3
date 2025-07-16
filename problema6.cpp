//
// Created by Grupo4 on 15/07/25.
//
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct Estacion {
    queue<int> colaB;  // Cola de cargas en plataforma B
    int capacidadCola;

    Estacion(int capacidad) : capacidadCola(capacidad) {}

    bool puedeAgregarACola() {
        return colaB.size() < capacidadCola;
    }
};

class TransportadorCarga {
private:
    stack<int> pila;  // Pila de cargas en el transportador
    int capacidadMaxima;

public:
    TransportadorCarga(int capacidad) : capacidadMaxima(capacidad) {}

    bool estaVacio() {
        return pila.empty();
    }

    bool estaLleno() {
        return pila.size() >= capacidadMaxima;
    }

    void cargarCarga(int destino) {
        if (!estaLleno()) {
            pila.push(destino);
        }
    }

    int verTopeCarga() {
        if (!estaVacio()) {
            return pila.top();
        }
        return -1;
    }

    int descargarCarga() {
        if (!estaVacio()) {
            int carga = pila.top();
            pila.pop();
            return carga;
        }
        return -1;
    }

    int tamano() {
        return pila.size();
    }
};

int simularTransporte(int N, int S, int Q, vector<vector<int>>& cargasIniciales) {
    // Crear estaciones
    vector<Estacion> estaciones(N + 1, Estacion(Q)); // 1-indexado

    // Inicializar colas de las estaciones
    for (int i = 1; i <= N; i++) {
        for (int destino : cargasIniciales[i]) {
            estaciones[i].colaB.push(destino);
        }
    }

    // Crear transportador
    TransportadorCarga transportador(S);

    int tiempoTotal = 0;
    int estacionActual = 1;

    // Continuar hasta que todas las colas estén vacías
    while (true) {
        bool hayCargas = false;

        // Verificar si quedan cargas en alguna cola
        for (int i = 1; i <= N; i++) {
            if (!estaciones[i].colaB.empty()) {
                hayCargas = true;
                break;
            }
        }

        // Terminar, si no hay cargas y el transportador está vacío
        if (!hayCargas && transportador.estaVacio()) {
            break;
        }

        // FASE DE DESCARGA
        int cargasDescargadas = 0;

        // Descargar cargas que tienen como destino la estación actual
        while (!transportador.estaVacio()) {
            int destinoCarga = transportador.verTopeCarga();

            if (destinoCarga == estacionActual) {
                // Descargar en plataforma A
                transportador.descargarCarga();
                cargasDescargadas++;
            } else {
                // Intentar descargar en plataforma B (cola)
                if (estaciones[estacionActual].puedeAgregarACola()) {
                    int carga = transportador.descargarCarga();
                    estaciones[estacionActual].colaB.push(carga);
                    cargasDescargadas++;
                } else {
                    break;
                }
            }
        }

        // Tiempo de descarga: 1 minuto por cada carga descargada
        tiempoTotal += cargasDescargadas;

        // FASE DE CARGA
        int cargasCargadas = 0;

        // Cargar desde la cola de la plataforma B
        while (!estaciones[estacionActual].colaB.empty() && !transportador.estaLleno()) {
            int carga = estaciones[estacionActual].colaB.front();
            estaciones[estacionActual].colaB.pop();
            transportador.cargarCarga(carga);
            cargasCargadas++;
        }

        // Tiempo de carga: 1 minuto por cada carga cargada
        tiempoTotal += cargasCargadas;

        // MOVERSE A LA SIGUIENTE ESTACIÓN
        estacionActual++;
        if (estacionActual > N) {
            estacionActual = 1;
        }

        // Tiempo de movimiento: 2 minutos
        tiempoTotal += 2;
    }

    return tiempoTotal;
}

int main() {

    int SET;
    cout << "Ingrese el numero de conjuntos de datos: ";
    cin >> SET;

    for (int conjunto = 1; conjunto <= SET; conjunto++) {
        cout << "\n--- Conjunto de datos " << conjunto << " ---" << endl;

        int N, S, Q;
        cout << "Ingrese N (estaciones), S (cap. transportador), Q (cap. cola): ";
        cin >> N >> S >> Q;

        vector<vector<int>> cargasIniciales(N + 1); // 1-indexado

        cout << "Ingrese las cargas para cada estacion:" << endl;
        for (int i = 1; i <= N; i++) {
            int numCargas;
            cout << "Estacion " << i << " - Numero de cargas: ";
            cin >> numCargas;

            if (numCargas > 0) {
                cout << "Destinos de las cargas: ";
                for (int j = 0; j < numCargas; j++) {
                    int destino;
                    cin >> destino;
                    cargasIniciales[i].push_back(destino);
                }
            }
        }

        int tiempoTotal = simularTransporte(N, S, Q, cargasIniciales);
        cout << "Tiempo total para completar el trabajo: " << tiempoTotal << " minutos" << endl;
    }

    return 0;
}