// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>


// función que resuelve el problema
void resolver(int m, int n, int k, std::vector<std::string>& tipos, int& asignaciones, std::vector<int>& sol) {
    for(int i = 0; i < m; i++){
        sol[k] = i;
        if(k % 2!=1 || sol[k-1] < sol[k] && tipos[sol[k-1]] != tipos[sol[k]]){
            if(k == (n*2)-1){
                asignaciones++;
                for(int regalo : sol) std::cout << regalo << ' ';
                std::cout << '\n';
            }
            else{
                resolver(m, n, k+1, tipos, asignaciones, sol);
            }
        }
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

    std::vector<std::string> tipos(m);
    for(std::string& tipo : tipos) std::cin >> tipo;
    
    int asignaciones = 0;
    std::vector<int> sol(n*2);
    resolver(m, n, 0, tipos, asignaciones, sol);
    if(asignaciones == 0) std::cout << "SIN SOLUCION\n";
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