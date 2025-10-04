// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

void debug(const std::vector<char>& datos, int ini, int fin){
    for(int i = ini; i < fin; i++){
        std::cout << datos[i] << " ";
    }
    std::cout << std::endl;
}

// función que resuelve el problema
char resolver(const vector<char>& sec, int primer, int ini, int fin) {
    int m = (ini+fin)/2;
    
    if(sec[0] != primer) return primer;

    if(ini == fin-1) return primer + ini + 1;
    

    if(sec[m] - primer == m)
        return resolver(sec, primer, m, fin);
    else return resolver(sec, primer, ini, m);
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    char prim, ult, n;
    cin >> prim >> ult;
    n = ult-prim;
    vector<char> sec(n);
    for (char& e : sec) cin >> e;
    cout << resolver(sec, prim, 0, n) << endl;
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