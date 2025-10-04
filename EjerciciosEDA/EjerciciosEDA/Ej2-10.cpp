// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>


// función que resuelve el problema
int encuentraImpar(const std::vector<int>& datos, int ini, int fin) {
    int m = (ini+fin)/2;

    if(datos[m] % 2)
        return datos[m];

    if(ini >= fin)
        return -1;

    if(datos[m] == datos[ini] + 2*(m-ini)){
        return encuentraImpar(datos, m+1, fin);
    }
    else{
        return encuentraImpar(datos, ini, m);
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTam;
    std::cin >> nTam;

    if (nTam == 0)
        return false;
    std::vector<int> datos(nTam);
    for(int& e : datos)
        std::cin >> e;
     
    std::cout << encuentraImpar(datos, 0, nTam) << "\n";
    
    // escribir sol
    
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
