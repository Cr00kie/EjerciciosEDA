// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

void debug(const std::vector<int>& datos, int ini, int fin){
    for(int i = ini; i < fin; i++){
        std::cout << datos[i] << " ";
    }
    std::cout  << std::endl;
}

// función que resuelve el problema
bool resolver(const std::vector<int>& datos, int nValorBuscado, int ini, int fin) {
    int m = (ini+fin)/2;
    //debug(datos, ini, fin);
    if(ini >= fin) return false;

    if(datos[m] == nValorBuscado || datos[ini] == nValorBuscado) return true;
    
    if(datos[m] > datos[ini]){
        if(nValorBuscado < datos[m] && nValorBuscado > datos[ini])
            return resolver(datos, nValorBuscado, ini, m);
        else return resolver(datos, nValorBuscado, m+1, fin);
    }
    else {
        if(nValorBuscado > datos[m] && nValorBuscado < datos[ini])
            return resolver(datos, nValorBuscado, m+1, fin);
        else return resolver(datos, nValorBuscado, ini, m);
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTam, nValorBuscado;
    std::cin >> nTam >> nValorBuscado;

    if (nTam == -1)
        return false;
    
    std::vector<int> datos(nTam);

    for(int& e : datos)
        std::cin >> e;

    std::cout << (resolver(datos, nValorBuscado, 0, nTam) ? "SI" : "NO") << '\n';
    
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
