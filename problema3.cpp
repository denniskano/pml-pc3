#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;


string reconstruirArchivo(const vector<string>& fragmentos) {
    vector<string> frags = fragmentos;
    sort(frags.begin(), frags.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });

    int total = frags.size();
    int N = total / 2;
    int maxLen = frags.back().size();
    int minLen = frags.front().size();

    for (const string& a : frags) {
        for (const string& b : frags) {
            if (a == b) continue;
            if (a.size() + b.size() != minLen + maxLen) continue;

            string intento = a + b;
            multiset<string> restos(frags.begin(), frags.end());
            bool valido = true;

            for (int i = 0; i < N; ++i) {
                bool emparejado = false;
                for (const string& x : restos) {
                    string y = intento.substr(x.size());
                    if (x + y == intento && restos.count(y)) {
                        restos.erase(restos.find(x));
                        restos.erase(restos.find(y));
                        emparejado = true;
                        break;
                    }
                }
                if (!emparejado) {
                    valido = false;
                    break;
                }
            }

            if (valido) return intento;
        }
    }

    return "[NO HAY SOLUCIÓN]";
}

int main() {
    // Datos de entrada
    int numeroDeCasos = 1;
    vector<vector<string>> casos = {
        { "011", "0111", "01110", "111", "0111", "10111" }
    };

    cout << "** DATOS DE ENTRADA **\n";
    cout << numeroDeCasos << "\n";
    for (const string& frag : casos[0]) {
        cout << frag << "\n";
    }

    cout << "\n** SALIDA DE SALIDA **\n";
    string resultado = reconstruirArchivo(casos[0]);
    cout << resultado << "\n";

    return 0;
}
