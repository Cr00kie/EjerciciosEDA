// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void resolver(int n, int k, std::vector<int>& sol) {
    for(int i = 0; i < 3; i++){
        sol[k] = i;
        if(k == n-1){
            for(int col : sol){
                switch (col)
                {
                case 0: std::cout << "azul "; break;
                case 1: std::cout << "rojo "; break;
                case 2: std::cout << "verde "; break;
                }
            }
            std::cout << '\n';
        }
        else{
            resolver(n, k+1, sol);
        }
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    
    if (n == 0)
        return false;
    
    std::vector<int> torre(n);
    resolver(n, 0, torre);
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
