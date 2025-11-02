// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

template<class T>
void resuelve(const bintree<T>& tree, int& n, int& h, int& a){
    if(tree.empty()){
        a = 0;
        h = 0;
        return;
    }

    int aDer, aIzq, hDer, hIzq;
    resuelve(tree.right(), n, hDer, aDer);
    resuelve(tree.left(), n, hIzq, aIzq);

    n += 1;
    h = !hDer && !hIzq ? 1 : hDer + hIzq;
    a = (aDer > aIzq ? aDer : aIzq) + 1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    bintree<char> tree;
    tree = leerArbol('.');
    std::cout << tree.nodos() << " " << tree.hojas() << " " << tree.altura() << '\n';
    // int nodos = 0, h = 0, a = 0;
    // resuelve(tree, nodos, h, a);
    // std::cout << nodos << " " << h << " " << a << '\n';
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
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
