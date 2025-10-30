// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include "list_eda.h"
using namespace std;

// Complejidad: O(n) siendo n = l.size()
void adelantar(list<char>& l, int pos, int length, int newPos) {

    if(pos <= 0 || pos >= l.size()  || // Posicion de origen incorrecta
           newPos < 0 || newPos >= l.size() ||
           length ==  0 || newPos == pos) return;

    // Buscamos la posicion deseada 
    list<char>::iterator nuevaPosicion =  l.begin();
    int i = 0;
    for(i; i < newPos; ++i)
        ++nuevaPosicion;
    
    // Buscamos comienzo del segmento
    list<char>::iterator comienzoSegmento = nuevaPosicion;
    for(; i < pos; ++i) ++comienzoSegmento;


    // Vamos borrando y reinsertando los elementos del segmento
    for(int j = 0; j < length && comienzoSegmento != l.end(); ++j){
        nuevaPosicion = ++(l.insert(nuevaPosicion, *comienzoSegmento));
        comienzoSegmento = l.erase(comienzoSegmento);
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    char e;
    int n, pos, length, dif;
    list<char> l;

    // leer los datos de la entrada
    cin >> n >> pos >> length >> dif;
    for (int i = 1; i <= n; ++i) {
        cin >> e;
        l.push_back(e);
    }

    adelantar(l, pos, length, pos-dif);

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
    cout << endl;
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
