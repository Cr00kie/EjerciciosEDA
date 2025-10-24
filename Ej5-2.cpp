// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "deque_eda.h"


// función que resuelve el problema
void resolver(deque<int>& datos) {
    deque<int> aux;
    int size = datos.size();
    
    for(int i = 0; i < size; ++i){
        int dato = datos.front();
        datos.pop_front();
        if(dato < 0){
            aux.push_front(dato);
        }
        else{
            aux.push_back(dato);
        }
    }

    datos = aux;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nVal;
    std::cin >> nVal;
    
    if (nVal <= 0)
        return false;

    deque<int> datos;

    for(int i = 0; i < nVal; ++i){
        int dato;
        std::cin  >> dato;
        datos.push_back(dato);
    }
    
    resolver(datos);
    
    for(int i = 0; i < nVal; ++i){
        std::cout << datos.front() << ' ';
        datos.pop_front();
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
    
    
    while (resuelveCaso())
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
