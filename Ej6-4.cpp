// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

bool esPrimo(int num){
    if(num < 2) return false;
    int i = 2;
    while(i*i <= num && num%i != 0) ++i;
    return i*i > num;
}

// función que resuelve el problema
std::pair<int, int> resolver(bintree<int> const& tree, int depth) {
    if(tree.empty() || esPrimo(tree.root())) return {-1, -1};
    if(tree.root() % 7 == 0) return {tree.root(), depth};

    std::pair<int, int> primIzq = resolver(tree.left(), depth+1);
    std::pair<int, int> primDer = resolver(tree.right(), depth+1);

    if(primDer.first == -1 && primIzq.first == -1) return {-1, -1};
    else if(primDer.first == -1) return primIzq;
    else if(primIzq.first == -1) return primDer;
    else if(primDer.second < primIzq.second) return primDer;
    else return primIzq;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    bintree<int> tree = leerArbol(-1);
    auto sol = resolver(tree, 1);
    int primo = sol.first;
    int prof = sol.second;
    
    if(primo == -1 || prof == -1) std::cout << "NO HAY\n";
    else std::cout << primo << ' ' << prof << '\n';

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