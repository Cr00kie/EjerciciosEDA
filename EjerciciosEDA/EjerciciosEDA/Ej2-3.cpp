// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

// Este algoritmo implementa una recursion multiple 
// Calculo del coste:
//      a = 2
//      b = 2
//      k = 0
// --> a > b^k --> O(n^(log2 2)) = O(n)
bool parcialmenteOrdenado(const vector<int>& v, int ini, int fin, int& min, int& max) {
    int m = (ini+fin)/2;
    int minIzq, maxIzq, minDer, maxDer;

    if(ini == fin-1){
        // Si el subvector es de un solo elemento, esta ordenado y el elemento es el minimo y maximo
        min = v[ini]; max = v[ini];
        return true;
    }
    
    if(parcialmenteOrdenado(v, ini, m, minIzq, maxIzq)
        && parcialmenteOrdenado(v, m, fin, minDer, maxDer))
    {
        max = maxDer; // Si esta parcialmente ordenado el maximo siempre sera el de la derecha
        min = minIzq; // Si esta parcialmente ordenado el minimo siempre sera el de la izquierda
        // Si lo anterior no es cierto entonces no esta parcialmente ordenado
        return maxDer >= maxIzq && minIzq <= minDer;
    }
    
    // Si los subvectores no son parcialmente ordenados el vector completo tampoco
    return false;
}

bool parcialmenteOrdenado(const vector<int>& v) {
    int min, max;
    return parcialmenteOrdenado(v,0,v.size(),min,max);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int e;
    cin >> e;
    if (e == 0) return false;
    vector<int> sec;
    while (e != 0) {
        sec.push_back(e);
        cin >> e;
    }
    cout << (parcialmenteOrdenado(sec)? "SI" : "NO") << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}