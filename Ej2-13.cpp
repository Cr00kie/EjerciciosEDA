// ADRIAN ISASI MARTINEZ
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema
int resolver(const std::vector<int>& datos, int ini, int fin) {
    int m = (ini+fin)/2;
    int n = fin-ini;

    if(n == 1) return ini;

    if(n % 4 == 1){
        if(datos[m] == datos[m+1])
            return resolver(datos, m, fin);
        else return resolver(datos, ini, m+1); // m-1 para que el subvector sea impar
    }
    else{
        if(datos[m] == datos[m-1])
            return resolver(datos, m+1, fin); // m+1 para que el vector sea impar
        else return resolver(datos, ini, m);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<int> v(n);
    for (int& e : v) cin >> e;
    
    // Llamada a la función resolver y mostrar el resultado
    std::cout << resolver(v, 0, n) << "\n";
}


//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}