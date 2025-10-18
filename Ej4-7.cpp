// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int s1Tam, s2Tam;

    std::cin >> s1Tam;
    if (! std::cin)
        return false;

    Set<int> s1(s1Tam);
    for(int i = 0; i < s1Tam; ++i)
    {
        int dato;
        std::cin >> dato;
        s1.add(dato);   
    }


    std::cin >> s2Tam;
    Set<int> s2(s2Tam);
    for(int i = 0; i < s2Tam; ++i)
    {
        int dato;
        std::cin >> dato;
        s2.add(dato);   
    }

    std::cout << (s1 <= s2) << '\n';
    
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