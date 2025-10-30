// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"


template <class T>
class queue_plus : public queue<T> {
    using Nodo = typename queue<T>::Nodo;

public:
    // Complejidad: O(n) siendo n = queue.size()
    void cuela(const T& a, const T& b){
        // Ojo que para acceder a prim o ult hay que escribir this->prim o this->ult
        Nodo* nodoA;
        Nodo* nodoB;

        // Buscamos el elemento a
       Nodo* aux = this->prim;
        while(aux && aux->elem != a)
            aux = aux->sig;
        if(!aux) return;
        nodoA = aux;

        // Buscamos el elemento b
        while(aux->sig && aux->sig->elem != b)
            aux = aux->sig;
        if(!aux->sig) return;
        nodoB = aux->sig;

        // Quitamos b de su posicion
        aux->sig = nodoB->sig;
        if(this->ult == nodoB) this->ult = aux;

        // Colocamos b detras de a
        nodoB->sig = nodoA->sig;
        nodoA->sig = nodoB;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a, b;
    queue_plus<int> q;
    std::cin >> n;
    if (n == -1) return false;
    while (n != -1){
        q.push(n);
        std::cin >> n;
    }
    std::cin >> a >> b;

    // llamada a metodo
    q.cuela(a,b);

    // escribir sol (pero antes dar una vuelta para comprobar que la cola está bien formada)
    for (int i = 0; i < q.size(); ++i){
        n = q.front();
        q.pop();
        q.push(n);
    }
    // Ahora imprimimos la cola y de paso la dejamos vacía
    while (!q.empty()){
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << std::endl;
    return true;
}

//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}
