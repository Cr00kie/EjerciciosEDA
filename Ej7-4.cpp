// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>


// función que resuelve el problema
int resolver(const std::vector<int>& datos) {
    std::unordered_map<int, int> capsEmitidos;

    // -1 es que no se ha emitido
    for(int e : datos) capsEmitidos[e] = -1;

    int maxDiasSinRepe = 0;
    int ultimoDiaSinRepe = 0;
    int i = 0;
    for(; i < datos.size(); ++i){
        int ultimaEmisionCap = capsEmitidos[datos[i]];

        if(ultimaEmisionCap >= ultimoDiaSinRepe && ultimaEmisionCap != -1){
            int diasSinRepe = i - ultimoDiaSinRepe;
            if(diasSinRepe > maxDiasSinRepe) {
                maxDiasSinRepe = diasSinRepe;
                // std::cout << "Segmento mas grande encontrado:\n";
                // for(int j = ultimoDiaSinRepe; j < diasSinRepe; j++) std::cout << datos[j] << ' ';
                // std::cout << '\n';
            }
            ultimoDiaSinRepe = ultimaEmisionCap+1;
        }

        capsEmitidos[datos[i]] = i;
    }

    int ultimosCapitulosSinRepe = i - ultimoDiaSinRepe;
    // std::cout << "Ultimo segmento:\n";
    // for(int j = ultimoDiaSinRepe; j < datos.size(); j++) std::cout << datos[j] << ' ';
    // std::cout << '\n';

    return maxDiasSinRepe > ultimosCapitulosSinRepe ? maxDiasSinRepe : ultimosCapitulosSinRepe;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nCaps;
    std::cin >> nCaps;
    std::vector<int> caps(nCaps);

    for(int& e : caps) std::cin >> e;
    
    std::cout << resolver(caps) << '\n';
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