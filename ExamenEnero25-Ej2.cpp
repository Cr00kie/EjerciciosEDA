// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;


template <class T>
int acumuladores(bintree<T> const& tree, int& outNAcumuladores) {
    if(tree.empty()) return 0;

    int sumaIzq = acumuladores(tree.left(), outNAcumuladores);
    int sumaDer = acumuladores(tree.right(), outNAcumuladores);
    int sumaTotal = sumaIzq + sumaDer;

    if(sumaTotal == tree.root())
        outNAcumuladores++;

    return sumaTotal + tree.root();
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree;
    tree = leerArbol(-1);
    int nAcumuladores = 0;
    acumuladores(tree, nAcumuladores);
    cout << nAcumuladores << '\n';
}

//#define DOMJUDGE
int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
