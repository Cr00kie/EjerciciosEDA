// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// Complejidad: a = b^k (1 = 1) -> O(n^k log n) = O(log n)
// pos1, pos2   
std::pair<int, int> resolver(const std::vector<int>& creciente, const std::vector<int>& decreciente, int ini, int fin){
    int m = (ini+fin)/2;

    if(creciente[m] == decreciente[m]) return {m, m};
    
    if(ini == fin-1){
        if(creciente[ini] > decreciente[ini]) return {-1, 0};
        else return {ini, fin};
    }
    
    if(creciente[m] < decreciente[m]) return resolver(creciente, decreciente, m, fin);
    else return resolver(creciente, decreciente, ini, m);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    
    if (n == 0)
        return false;

    std::vector<int> creciente(n);
    std::vector<int> decreciente(n);

    for(int& e : creciente) std::cin >> e;
    for(int& e : decreciente) std::cin >> e;
    
    std::pair<int, int> sol = resolver(creciente, decreciente, 0, n);
    
    // escribir sol
    if(sol.first == sol.second) std::cout << "SI " << sol.first << '\n';
    else std::cout << "NO " << sol.first << ' ' << sol.second << '\n';
    
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
