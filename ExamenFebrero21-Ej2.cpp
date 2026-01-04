// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

template <class T>
int esSimetrico(bintree<T> const& tree, int k, int sign) {
    if(tree.empty()) return 0;

    int balanceIzq = esSimetrico(tree.left(), k+1, -1);
    int balanceDer = esSimetrico(tree.right(), k+1, 1);

    // std::cout << balanceDer << " + " << balanceIzq << " + " << (sign * k*k) << " = " << balanceDer + balanceIzq + (sign * k*k) << '\n';

    return balanceDer + balanceIzq + (sign * k*k);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');
    int res = esSimetrico(tree, 0, 1);
    cout << (res==0?"SI":"NO") << '\n';
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
