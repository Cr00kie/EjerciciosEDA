// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>


// función que resuelve el problema
void resolver(int m, int n, int k, std::vector<std::vector<int>>& satisfaccionPorNino, int& satisfaccionMax, int satisfaccionActual, std::vector<bool>& juguetesDados, std::vector<int>& estimacion) {
    for(int i = 0; i < m; i++){

        // Si el juguete no habia sido asignado todavia y la rama tiene posibilidades de superar el maximo
        if(!juguetesDados[i] && satisfaccionActual + estimacion[k] > satisfaccionMax){
            if(k == n){
                // std::cout << "\nResultado combinacion: " << satisfaccionActual << '\n';
                if(satisfaccionActual > satisfaccionMax) {satisfaccionMax = satisfaccionActual; }
            }
            else{
                // std::cout << i << '(' << satisfaccionActual << " + " << satisfaccionPorNino[k][i] << ") ";
                // Marcamos el juguete como dado
                juguetesDados[i] = true;
                // Marcamos la satisfaccion del juguete
                satisfaccionActual += satisfaccionPorNino[k][i];
                // LLama recursiva
                resolver(m, n, k+1, satisfaccionPorNino, satisfaccionMax, satisfaccionActual, juguetesDados, estimacion);
                // Desmarcamos el juguete como dado
                juguetesDados[i] = false;
                // Desmarcamos la satisfaccion del juguete
                satisfaccionActual -= satisfaccionPorNino[k][i];
            }
        }
        // else{
        //     if(satisfaccionActual + estimacion[k] <= satisfaccionMax) {
        //         std::cout << "Rama podada\t" << satisfaccionActual << " + " << estimacion[k] << " <= " << satisfaccionMax << '\n';
        //     }
        // }

    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int m, n;
    std::cin >> m >> n;
    
    if (! std::cin)
    return false;
    
    std::vector<std::vector<int>> satisfaccionesPorNino(n);
    std::vector<int> estimacion(n);
    for(int i = 0; i < n; i++){
        satisfaccionesPorNino[i].resize(m);
        int max = 0;
        for(int& sat : satisfaccionesPorNino[i]) {
            std::cin >> sat;
            if(sat > max) max = sat;
        }
        for(int j = 0; j <= i; j++) estimacion[j] += max;
    }
    // std::cout << "estimaciones: ";
    // for(int est : estimacion) std::cout << est << ' ';
    // std::cout << '\n';
    
    int satisfaccionMax = 0;
    std::vector<bool> juguetesDados(m, 0);
    resolver(m, n, 0, satisfaccionesPorNino, satisfaccionMax, 0, juguetesDados, estimacion);
    
    std::cout << satisfaccionMax << '\n';

    // saltar la linea en blanco
    std::string line;
    std::getline(std::cin, line);
    
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