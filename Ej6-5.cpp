// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

bool esSearchBintree(bintree<int> const& tree, int& outMin, int& outMax){
    if(tree.empty()) {
        outMin = -1;
        outMax = -1;
        return true;
    }

    int minIzq,  maxIzq, minDer, maxDer;
    bool esBSTIzq = esSearchBintree(tree.left(), minIzq, maxIzq);
    if(!esBSTIzq) return false;

    bool esBSTDer = esSearchBintree(tree.right(), minDer, maxDer);
    if(!esBSTDer) return false;

    bool esBST = (maxIzq == -1 || tree.root() > maxIzq) && 
                 (minDer == -1 || tree.root() < minDer);


    if(minIzq == -1) minIzq = tree.root();
    if(maxDer == -1) maxDer = tree.root();
    
    outMin = minIzq;
    outMax = maxDer;

    return esBST;
}

// función que resuelve el problema
bool resolver(bintree<int> const& tree) {
    int m1, m2;
    return esSearchBintree(tree, m1, m2);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    bintree<int> tree = leerArbol(-1);
    
    std::cout << (resolver(tree) ? "SI" : "NO") << '\n';

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