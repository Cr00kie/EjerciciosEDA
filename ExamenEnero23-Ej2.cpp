// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"


// función que resuelve el problema
// <hoja, dragones>
std::pair<int, int> resolver(const bintree<int>& datos) {
    if(datos.empty()){
        return {-1, INT_MAX};
    }

    if(datos.left().empty() && datos.right().empty()){
        // std::cout << "RAIZ: " << datos.root() << "\n";
        return {datos.root(), 0};
    }

    
    std::pair<int, int> resIzq = resolver(datos.left());
    std::pair<int, int> resDer = resolver(datos.right());

    // std::cout << "i(" << resIzq.first << ", " << resIzq.second << "), d(" << resDer.first << ", " << resDer.second << ") seleccionado: " << (resIzq.second <= resDer.second ? resIzq.first : resDer.first) << '\n';

    std::pair<int, int> ret = resIzq.second <= resDer.second ? resIzq : resDer;

    if(datos.root() == 1){
        ret.second++;
    }

    return ret;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> arbol = leerArbol(-1);
    
    auto sol = resolver(arbol);
    // escribir sol
    std::cout << sol.first << '\n';
    
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