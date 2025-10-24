// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"

// función que resuelve el problema
void resolver(queue<int>& datos, const std::vector<int>& frec) {
    datos.duplicaFrecuencias(frec);
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nTam;
    std::cin >> nTam;

    queue<int> datos;
    std::vector<int> frec(nTam);

    for(int i = 0; i < nTam; ++i){
        int dato;
        std::cin >> dato;
        datos.push(dato);
    }


    for(int& e : frec) std::cin >> e;
    
    resolver(datos, frec);
    
    while(!datos.empty()){
        std::cout << datos.front() << ' ';
        datos.pop();
    }
    
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