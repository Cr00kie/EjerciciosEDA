// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
int resolver(const std::vector<int>& datos, int ini, int fin) {
    int m = (ini+fin)/2;

    if(ini == fin-1) return datos[ini];

    if(datos[ini] + (m-ini) == datos[m])
        return resolver(datos, m, fin);
    else return resolver(datos, ini, m);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nTam;
    std::cin >> nTam;
    std::vector<int> datos(nTam);
    for(int& e : datos) std::cin >> e;
    
    std::cout << resolver(datos, 0, nTam) << '\n';
    // escribir sol
    
    
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