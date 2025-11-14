// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// función que resuelve el problema
int resolver(bintree<int> const & tree, int& accEquipos) {
    if(tree.empty()) return 0;

    int maxIzq = resolver(tree.left(), accEquipos);
    int maxDer = resolver(tree.right(), accEquipos);


    if(!maxIzq && !maxDer && tree.root()) {
        ++accEquipos;
    }

    return maxIzq > maxDer ? maxIzq+tree.root() : maxDer+tree.root();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> tree = leerArbol(-1);
    int nEquipos = 0, nRutaMax;
    nRutaMax = resolver(tree, nEquipos);
    std::cout << nEquipos << ' ' << nRutaMax << '\n';

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
     system("PAUSE");
     #endif
    
    return 0;
}