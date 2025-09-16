// Adrián Isasi Martínez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void CuentaPicosYValles(const std::vector<int>& datos, int& outPicos, int& outValles) {
    int nSize = datos.size();
    outPicos = 0;
    outValles = 0;
    
    for(int i = 0; i < nSize-2; i++){
        if(datos[i+1] - datos[i] < 0 && datos[i+2] - datos[i+1] > 0)
            ++outValles;
        if(datos[i+1] - datos[i] > 0 && datos[i+2] - datos[i+1] < 0)
            ++outPicos;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nValores, nPicos, nValles;
    std::cin >> nValores;

    // Rellenamos el vector
    std::vector<int> datos(nValores);
    for(int i = 0; i < nValores; i++){
        std::cin >> datos[i];
    }
    
    CuentaPicosYValles(datos, nPicos, nValles);
    
    // escribir sol
    std::cout << nPicos << " " << nValles << std::endl;
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