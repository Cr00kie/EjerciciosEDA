// Adrian Isas
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// función que resuelve el problema y justificación del coste
bool resolver(vector<bool>& soluc, int k, int n, vector<int> const& numeros, int resultadoRama, int resultadoEsperado){

    // Si estamos en la primera vuelta, ponemos signo + y pasamos a la siguiente
    if(k == 0 && n != 0){
        soluc[0] = 0;
        resultadoRama += numeros[0];
        k++;
    }

    // Miramos si es solucion
    if(k >= n // Ya hemos puesto todos los signos
    ){
        // for(int i = 0; i < n; ++i){
        //     std::cout << (soluc[i]?'-':'+') << ' ' << numeros[i] << ' ';
        // }
        // std::cout << " = " << resultadoRama << '\n';
        return resultadoRama == resultadoEsperado;
    }

    for(int i = 0; i < 2; i++){
        soluc[k] = i;

        // Sumamos el numero con el signo que estamos probando
        resultadoRama += numeros[k] - i * 2 * numeros[k];

        if(resolver(soluc, k+1, n, numeros, resultadoRama, resultadoEsperado)){
            return true;
        }

        // Restamos el numero que ya hemos probado
        resultadoRama -= numeros[k] - i * 2 * numeros[k];
    }

    return false;
}


void resuelveCaso() {
    int n = 0, M;
    cin >> M >> n;
    vector<int> v(n);
    for (int& e : v)
        cin >> e;

    // llamada a función que resuelve el problema
    vector<bool> soluc(n);
    std::cout << (resolver(soluc, 0, n, v, 0, M)?"SI":"NO") << '\n';
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