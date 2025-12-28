// Adrian Isasi
// EDA-GDV
// Realizado siguiendo el video explicativo de como hacerlo

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

const int NUM_MONEDAS = 8;
const int valores[NUM_MONEDAS] = {1,2,5,10,20,50,100,200};


// función que resuelve el problema
void resolver(vector<int>& soluc, int k, int n, int monedas[NUM_MONEDAS], int precio, int numMonedas, int suma, int& maxNumMonedas){
    for(int cant = 0; cant <= monedas[k]; cant++){
        soluc[k] = cant;
        suma += valores[k]*cant;
        numMonedas += cant;

        if(suma <= precio){
            if(suma == precio){
                if(numMonedas > maxNumMonedas) maxNumMonedas = numMonedas;
            }
            else if(k < n-1){
                int estimacionOpt = (precio-suma)/valores[k+1];
                if(numMonedas + estimacionOpt > maxNumMonedas)
                    resolver(soluc, k+1, n, monedas, precio, numMonedas, suma, maxNumMonedas);
            }
        }

        suma -= valores[k]*cant;
        numMonedas -= cant;
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int precio;
    int monedas[NUM_MONEDAS];
    cin >> precio;
    for (int i = 0; i < NUM_MONEDAS; ++i)
        cin >> monedas[i];
    vector<int> soluc(NUM_MONEDAS);
    int maxMonedas = -1;
    resolver(soluc, 0, NUM_MONEDAS, monedas, precio, 0, 0, maxMonedas);
    // Mostrar salida
    if(maxMonedas != -1) std::cout << maxMonedas << '\n';
    else std::cout << "IMPOSIBLE\n";
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
