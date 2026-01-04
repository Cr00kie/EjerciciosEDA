// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;


template <class T>
bool esSimetrico(bintree<T> const& treeLeft, bintree<T> const& treeRight) {
    if(treeLeft.empty() && treeRight.empty()) return true; 
    else if(!treeLeft.empty() && !treeRight.empty()) return esSimetrico(treeRight.left(), treeLeft.right()) && esSimetrico(treeRight.right(), treeLeft.left());
    else return false;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<char> tree;
    tree = leerArbol('.');
    bool res = esSimetrico(tree.right(), tree.left());
    cout << (res?"SI":"NO") << '\n';
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
