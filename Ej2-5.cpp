// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Este algoritmo implementa una recursion multiple 
// Calculo del coste:
//      a = 2
//      b = 2
//      k = 0
// --> a > b^k --> O(n^(log2 2)) = O(n)
bool caucasico(const vector<int>& datos, int ini, int fin, int& nPares){
    int m = (ini+fin)/2;

    if(ini == fin-1){
        nPares = datos[ini]%2 == 0 ? 1 : 0;
        return true;
    }

    int nParesIzq = 0, nParesDer = 0;

    if(caucasico(datos, ini, m, nParesIzq)
        && caucasico(datos, m, fin, nParesDer)){
            nPares += nParesIzq + nParesDer;
            int dif = nParesIzq - nParesDer;
            int difAbs = dif > 0 ? dif : -dif;
            return difAbs <= 2;
    }

    return false;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (n == 0) return false;
    vector<int> sec(n);
    for (int& e : sec) cin >> e;
    int nPares;
    cout << (caucasico(sec, 0, sec.size(), nPares)? "SI" : "NO") << endl;
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