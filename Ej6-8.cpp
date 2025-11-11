// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// función que resuelve el problema
int resolver(bintree<char> const& tree, int& outDiam) {
    if(tree.empty()) return 0;

    int alturaIzq = resolver(tree.left(), outDiam);
    int alturaDer = resolver(tree.right(), outDiam);

    int diametro = alturaIzq + alturaDer + 1;
    if(diametro == 0) diametro = 1; // Si es hoja lo ponemos bien

    if(diametro > outDiam) {
        outDiam = diametro;
    }

    return alturaDer > alturaIzq ? alturaDer+1 : alturaIzq+1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    bintree<char> tree = leerArbol('.');
    int sol = 0;
    resolver(tree, sol);
    std::cout << sol << '\n';

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