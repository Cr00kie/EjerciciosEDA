// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "bintree_eda.h"


template <class T>
void minimo(bintree<T> const& tree, T& min){
    if(tree.empty()) return;

    if(tree.root() < min) min = tree.root();
    minimo(tree.right(), min);
    minimo(tree.left(), min);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    char tipo;
    std::cin >> tipo;
    if (!std::cin) return false;
    if (tipo == 'N'){
        bintree<int> tree = leerArbol(int(-1));
        int min = 99999999; 
        minimo(tree, min);
        std::cout << min << std::endl;
    } else if (tipo == 'P'){
        bintree<std::string> tree = leerArbol(std::string("#"));
        std::string min = "~";
        minimo(tree, min);
        std::cout << min << std::endl;
    }
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso());

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
