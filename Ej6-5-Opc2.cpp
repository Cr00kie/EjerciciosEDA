// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include "bintree_eda.h"

// Complejidad:
// O(n) siendo n el numero de nodos de tree
bool esSearchBintree(bintree<int> const &tree, int inMinValid, int inMaxValid)
{
    if(tree.empty()) return true;

    if (tree.root() > inMinValid && tree.root() < inMaxValid)
    {
        return esSearchBintree(tree.left(), inMinValid, tree.root()) && esSearchBintree(tree.right(), tree.root(), inMaxValid);
    }
    else return false;
}

// función que resuelve el problema
bool resolver(bintree<int> const &tree)
{
    int max = std::numeric_limits<int>::max(), min = std::numeric_limits<int>::min();
    return esSearchBintree(tree, min, max);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso()
{
    // leer los datos de la entrada

    bintree<int> tree = leerArbol(-1);

    std::cout << (resolver(tree) ? "SI" : "NO") << '\n';
}

int main()
{
// Para la entrada por fichero.
// Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); // save old buf and redirect std::cin to casos.txt
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