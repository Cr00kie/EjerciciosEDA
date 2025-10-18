// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"
#include <vector>

// Complejidad: n = datos.size(), m = nMin
// Pero caso: O(n * (logm + m))
Set<int> resolver(const std::vector<int>& datos, int nMin) {
    Set<int> aux(nMin);

    // O(n)
    for(int i = 0; i < datos.size(); ++i){
        if(aux.size() < nMin)
            // O(m)
            aux.add(datos[i]);
        else{
            if(aux.getMax() > datos[i]){
                // O(log(m) + m)
                if(!aux.contains(datos[i]))
                {
                    aux.removeMax();
                    aux.add(datos[i]);
                }
            }
        }
    }
    
    return aux;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nMin;
    std::cin >> nMin;

    if (!nMin)
        return false;
    
    std::vector<int> datos;
    int dato;
    std::cin >> dato;
    while(dato != -1){
        datos.push_back(dato);
        std::cin >> dato;
    }
    
    Set<int> sol = resolver(datos, nMin);
    
    std::cout << sol << '\n';
    
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
