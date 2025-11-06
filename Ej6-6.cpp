// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

int zurdo(bintree<char> const& tree){
    if(tree.empty()) return 0;

    int nodosIzq = zurdo(tree.left());
    if(nodosIzq == -1) return -1;

    int nodosDer = zurdo(tree.right());
    if(nodosDer == -1) return -1;
    
    if(!nodosIzq && !nodosDer) return 1;
    return (nodosIzq > nodosDer) ? nodosIzq+nodosDer+1 : -1;
}

// función que resuelve el problema
bool resolver(bintree<char>& tree) {
    int res = zurdo(tree);
    return res!=-1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    bintree<char> tree = leerArbol('.');
    
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