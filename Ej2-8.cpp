// Adrián Isasi Martínez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

void debug(std::vector<int> datos, int ini, int fin, int m){
    for(int e : datos) std::cout << e << " ";
    std::cout << std::endl;
    for(int i = 0; i <= fin; ++i) {
        if(i == ini) std::cout << "i ";
        else if (i == fin) std::cout << "f ";
        else if (i == m) std::cout << "m ";
        else std::cout << "  ";
    }
    std::cout << std::endl;
}

// función que resuelve el problema
int resolver(const std::vector<int>& datos, int ini, int fin) {
    int m = (ini+fin)/2;

    //debug(datos, ini, fin, m);

    if(ini+1 == fin) return datos[m];

    if(datos[m] < datos[ini] && datos[m] < datos[fin-1]){
        if(datos[ini] < datos[fin-1]) return resolver(datos, m, fin);
        else return resolver(datos, ini, m);
    }
    else if(datos[m] > datos[ini] && datos[m] >= datos[fin-1]){
        if(datos[ini] > datos[fin-1]) return resolver(datos, m, fin);
        else return resolver(datos, ini, m);
    }
    else{ // datos[m] < datos[ini] && datos[m] > datos[fin]
        return resolver(datos, m, fin);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTam;
    std::cin >> nTam;

    if (! std::cin)
        return false;

    std::vector<int> datos(nTam);
    for(int& e : datos) std::cin >> e;
    std::cout << resolver(datos, 0, nTam) << std::endl;
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