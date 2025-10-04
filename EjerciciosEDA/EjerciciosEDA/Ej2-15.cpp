// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// Complejidad:
//   a = 1; b = 2; k = 0;
//   a == b^k --> T(datos.size) e n^k * log n = log datos.size
//              == O(log datos.size) ==
int resolver(const std::vector<int>& datos, int nSalario, int ini, int fin) {
    int m = (ini+fin)/2;

    if(nSalario == 0) return 0;

    if(ini == fin-1) return -1;

    int nIncremento = datos[m] - datos[m-1];

    if(nIncremento > nSalario){
        return resolver(datos, nSalario, ini, m); 
    }
    else if(nIncremento < nSalario){
        return resolver(datos, nSalario, m, fin); 
    }
    else return m; //PQ siempre crece entonces este es el mas preciso
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nTam, nSalario;
    std::cin >> nSalario >> nTam;

    std::vector<int> datos(nTam);
    
    for(int& e : datos) std::cin >> e;

    std::cout << resolver(datos, nSalario, 0, nTam) << '\n';
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