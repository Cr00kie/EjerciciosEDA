// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// función que resuelve el problema
int resolver(bintree<int> & tree, int& res) {
    if(tree.empty()) return 0;
    bintree<int> izq = tree.left(), der = tree.right();
    if(izq.empty() && der.empty()) return 1;

    int caudalIzq = resolver(izq, res);
    if(caudalIzq >= 3) ++res;

    int caudalDer = resolver(der, res);
    if(caudalDer >= 3) ++res;

    int caudalRes = caudalIzq+caudalDer-tree.root();

    return caudalRes < 0 ? 0 : caudalRes;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    bintree<int> tree = leerArbol(-1);
    int res = 0;
    resolver(tree, res);
    std::cout << res << '\n';

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