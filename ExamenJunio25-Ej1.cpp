// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"


class queue_plus : public queue<int>{
    public:
    void reordena(){
        Nodo* explorador = this->prim;

        // debug(explorador);

        while(explorador->sig != nullptr){

            if(explorador->sig->elem < 0){
                Nodo* nodoRecolocado = explorador->sig;
                // Quitamos el nodo de su posicion
                explorador->sig = nodoRecolocado->sig;
                if(nodoRecolocado == this->ult) this->ult = explorador;

                // Colocamos el nodo en el principio
                nodoRecolocado->sig = prim;
                prim = nodoRecolocado;
            }
            else{
                // Solo avanzamos si el siguiente nodo esta bien colocad
                explorador = explorador->sig;
            }
            // debug(explorador);
        }
    }
    void debug(queue<int>::Nodo *explorador)
    {
        Nodo *impresora = this->prim;
        while (impresora != nullptr)
        {
            std::cout << impresora->elem;
            if (impresora == prim)
                std::cout << "(p) ";
            else if (impresora == ult)
                std::cout << "(u) ";
            else if (impresora == explorador)
                std::cout << "(e) ";
            else
                std::cout << ' ';
            impresora = impresora->sig;
        }
        std::cout << '\n';
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    
    if (n == 0)
        return false;

    queue_plus datos;
    for(int i = 0; i < n; i++){
        int e;
        std::cin >> e;
        datos.push(e);
    }

    datos.reordena();

    for(int i = 0; i < datos.size(); i++){
        int front = datos.front();
        datos.pop();
        datos.push(front);
    }
    
    // escribir sol
    while(!datos.empty()){
        std::cout << datos.front() << ' ';
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
