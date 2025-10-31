// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;


template <class T>
class list_plus : public list<T> {
    using Nodo = typename list<T>::Nodo;

public:
    // Complejidad: O(pos+length) porque siempre tenemos que ir hasta el final del segmento
    void adelantar(int pos, int length, int newPos) {
        Nodo* prevNewPos;
        Nodo* prevComienzoSegmento;
        Nodo* comienzoSegmento;
        Nodo* finSegmento;

        if(pos <= 0 || pos >= this->size()  || // Posicion de origen incorrecta
           newPos < 0 || newPos >= this->size() ||
           length ==  0 || newPos == pos) return;

        // Buscamos el nodo anterior al de la nueva posicion
        int i = 0;
        Nodo* aux = this->fantasma; // Empezamos en fan por si es necesario poner el segmento al principio
        while(aux->sig != this->fantasma && i != newPos) {aux = aux->sig; ++i;}
        prevNewPos = aux;
        if(aux == this->fantasma) aux = aux->sig; // Si nos hemos quedado en el fantasma, avanza uno para que el siguiente bucle pueda trabajar
        else --i; // Quitamos uno teniendo en cuenta que hemos empezado en el fantasma

        // Buscamos el nodo anterior al del primer elemento del segmento
        while(aux != this->fantasma && i != pos-1) {aux = aux->sig; ++i;}
        prevComienzoSegmento = aux;

        // Buscamos el final del segmento
        while(aux->sig != this->fantasma && i != pos+length-1) {aux = aux->sig; ++i;}
        finSegmento = aux;

        //Quitamos el segmento de su posicion original
        comienzoSegmento = prevComienzoSegmento->sig;
        prevComienzoSegmento->sig = finSegmento->sig;
        finSegmento->sig->ant = prevComienzoSegmento;

        // Colocamos el segmento en la posicion deseada
        finSegmento->sig = prevNewPos->sig;
        finSegmento->sig->ant = finSegmento;
        prevNewPos->sig = comienzoSegmento;
        comienzoSegmento->ant = prevNewPos;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list_plus<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    l.adelantar(pos, length, pos-dif);

    // Le damos una vuelta para comprobar que la lista está bien formada
    for (int i = 0; i < l.size(); ++i){
        e = l.back();
        l.pop_back();
        l.push_front(e);
    }

    // Ahora imprimimos la lista y de paso la dejamos vacía (tb para probar su consistencia)
    while (!l.empty()){
        cout << l.front() << " ";
        l.pop_front();
    }
    cout << '\n';
}


//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}
