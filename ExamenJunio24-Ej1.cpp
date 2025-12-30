// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"

class ListPlus : public list<int>{
    public:
    void partition(int pivote){
        Nodo* base = this->fantasma;
        Nodo* explorador = this->fantasma->sig;

        while(explorador != this->fantasma){
            Nodo* siguienteNodo = explorador->sig;

            if(explorador->elem <= pivote){
                // Quitamos el nodo de su posicion
                explorador->ant->sig = explorador->sig;
                explorador->sig->ant = explorador->ant;

                // Insertamos el nodo en su nueva posicion
                base->sig->ant = explorador;
                explorador->sig = base->sig;
                base->sig = explorador;
                explorador->ant = base;

                // Avanzamos la posicion de base
                base = base->sig;
            }

            explorador = siguienteNodo;
        }
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, pivote;
    std::cin >> n >> pivote;
    
    if (! std::cin)
        return false;
    
    ListPlus list;

    for(int i = 0; i < n; i++){
        int num;
        std::cin >> num;
        list.push_back(num);
    }

    list.partition(pivote);

    for(int i = 0; i < list.size(); i++){
        int top = list.front();
        list.pop_front();
        list.push_back(top);
    }
    
    // escribir sol
    while(!list.empty()){
        std::cout << list.front() << ' ';
        list.pop_front();
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