// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"

// función que resuelve el problema
int resolver(bintree<std::string> & tree, std::string& lider) {
    if(tree.empty()) return 0;

    bintree<std::string> left = tree.left(), right = tree.right();

    if(left.empty() && right.empty()){
        lider = tree.root();
        return 1;
    }

    std::string liderIzq("~");
    int nGrupoIzq = resolver(left, liderIzq);

    std::string liderDer("~");
    int nGrupoDer = resolver(right, liderDer);

    if(nGrupoDer > nGrupoIzq)
        lider = liderDer;
    else if(nGrupoDer < nGrupoIzq)
        lider = liderIzq;
    else lider = liderIzq > liderDer ? liderDer : liderIzq;

    int nGrupo = nGrupoIzq + nGrupoDer;
    if(tree.root() == "Orcos") nGrupo/=2;
    return nGrupo;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    
    bintree<std::string> tree = leerArbol(std::string("."));
    std::string lider("~");
    int num = resolver(tree, lider);
    if(num)
        std::cout << lider << ' ' << num << '\n';
    else std::cout << "Ninguno\n";
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