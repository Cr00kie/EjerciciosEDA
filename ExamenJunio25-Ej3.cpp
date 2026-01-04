// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

// Complejidad: O( log(c.size()) + k )
template <class K, class V>
void eliminaKMenores(map<K, V>& map, int k){
    // De esta forma optimizamos para todas las k mayores que map.size() a tiempo constante
    if (k >= map.size()) {
        map.clear();
        return;
    }

    auto segmentEnd = map.begin();
    for(int i = 0; i < k; ++i) segmentEnd++; // O(k)
    map.erase(map.begin(), segmentEnd); // O(log(c.size) + k)
}

// Complejidad: O( map.size() * 2log(k) )
template <class C, class V>
void eliminaKMenores(unordered_map<C, V>& map, int k){
    if (k >= map.size()) {
        map.clear();
        return;
    }

    std::priority_queue<string> kMenores;

    // O(map.size() * ( 2log(kMenores.size()) ))
    for(auto par : map){
        kMenores.push(par.first); // log(kMenores.size())
        if(kMenores.size() > k){
            kMenores.pop(); // 2*log(kMenores.size())
        }
    }

    // O(map.size() * ( 2log(kMenores.size()) ))
    while(!kMenores.empty()){
        map.erase(kMenores.top());
        kMenores.pop(); // 2*log(kMenores.size())
    }
}



void resuelveCaso() {
    map<string, int> map1;
    unordered_map<string, int> map2;
    int n, k;

    // Lectura de datos
    cin >> n >> k;
    string clave;
    int valor;
    for (int i = 0; i < n; ++i){
        cin >> clave >> valor;
        map1.insert({clave, valor});
        map2.insert({clave, valor});
    }

    // Llamada a funciones
    eliminaKMenores(map1, k);
    eliminaKMenores(map2, k);

    // Escritura de la salida

    // Imprimir map1 ordenado por claves
    for (auto pair : map1) std::cout << pair.first << ' ' << pair.second << '\n';
    cout << "-\n";

    // Imprimir map2 ordenado por claves (para ello debes volcarlo a un vector, ordenarlo e imprimirlo)
    std::vector<std::pair<string, int>> map2Ordenado(map2.begin(), map2.end());
    std::sort(map2Ordenado.begin(), map2Ordenado.end());
    for (std::pair<string, int>& pair : map2Ordenado) std::cout << pair.first << ' ' << pair.second << '\n';
	
    cout << "---\n";
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