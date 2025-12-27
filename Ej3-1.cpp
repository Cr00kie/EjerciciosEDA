// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>



// función que resuelve el problema
void resolver(int m, int n, int k, char* sol) {
    for(int i = 0; i < m; i++){
        sol[k] = 'a' + i;
        if(k == n-1){
            for(int j = 0; j < n; j++){
                std::cout << sol[j];
            }
            std::cout << '\n';
        }
        else{
            resolver(m, n, k+1, sol);
        }
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int n, m;
    std::cin >> m >> n;
    
    if (! std::cin)
        return false;

    char* sol = new char[n];
    resolver(m, n, 0, sol);
    std::cout << '\n';

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