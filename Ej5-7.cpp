// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"


// función que resuelve el problema
void resolver(list<int>& datos, int e) {
    datos.borraElementos(e);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    list<int> datos;
    int dato, datoBuscado;

    std::cin >> dato;
    list<int>::iterator it = datos.begin();
    while(dato != -1){
        it = datos.insert(it, dato);
        it++;
        std::cin >> dato;
    }
    std::cin >> datoBuscado;

    for(auto it = datos.begin(); it != datos.end(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
    
    resolver(datos, datoBuscado);
    
    for(auto it = datos.begin(); it != datos.end(); ++it){
        std::cout << *it << ' ';
    }
    std::cout << '\n';
    
    
    return true;
    
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