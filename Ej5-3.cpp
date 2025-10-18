// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include "stack_eda.h"
#include "LinkedListStack.h"

// O(2datos.size)
void resolverExterno(std::stack<int>& datos) {
    std::stack<int> aux;

    while(!datos.empty()) {
        aux.push(datos.top());
        datos.pop();
    }

    while(!aux.empty()) {
        datos.push(aux.top());
        datos.push(aux.top());
        aux.pop();
    }
}

// O(datos.size)
void resolverInternoArrDin(stack<int>& datos) {
    datos.reverseAndDouble();
}

void resolverInternoArrLink(LinkedListStack<int>& datos){
    datos.reverseAndDouble();
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    LinkedListStack<int> datos;

    int dato;
    std::cin >> dato;
    
    if (! std::cin)
        return false;

    while(dato)
    {
        datos.push(dato);
        std::cin >> dato;
    }
    
    resolverInternoArrLink(datos);
    
    while(!datos.empty()) {
        std::cout << datos.top() << ' ';
        datos.pop();
    }
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