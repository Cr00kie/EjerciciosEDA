// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;



// función que resuelve el problema
void resolver(vector<int>& soluc, int k, int n, int numSupermercados, int& gasto, int& mejorGasto, vector<int>& comprasPorSuper,
              const vector<vector<int>>& precios, const vector<int>& mejoresPreciosDesde){
    for (int super = 0; super < numSupermercados; ++super){
        // Anadimos super a la solucion
        soluc[k] = super; // k es el nº de producto

        // Comprobamos que no se haya superado el limite de compras por super
        if (comprasPorSuper[super] <= 2){
            // Aumentamos el gasto acumulado
            gasto += precios[super][k];
            // Marcamos la compra en el super
            comprasPorSuper[super]++;
            if (k == n-1) {
                if (gasto < mejorGasto) {
                    mejorGasto = gasto;
                    // cout << "sol: " << mejorGasto << endl;
                }
            } else {
                // Podamos la rama de exploracion si la estimacion no supera el mejor gasto
                if (gasto + mejoresPreciosDesde[k+1] < mejorGasto)
                    resolver(soluc, k+1, n, numSupermercados, gasto, mejorGasto, comprasPorSuper, precios, mejoresPreciosDesde);
            }
            // Desmarcamos la compra en el super
            comprasPorSuper[super]--;
            // Desmarcamos el gasto del producto
            gasto -= precios[super][k];
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    cin >> m >> n;
    vector<vector<int>> precios(m,vector<int>(n));
    vector<int> mejoresPrecios(n, std::numeric_limits<int>::max());
    
    for (int i = 0; i < m ; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> precios[i][j];
            if (precios[i][j] < mejoresPrecios[j]) mejoresPrecios[j] = precios[i][j];
        }
    //cout << mejoresPrecios << endl;

    for (int i = n-2; i >= 0; --i){
        mejoresPrecios[i] += mejoresPrecios[i+1];
    }
    //cout << mejoresPrecios << endl;

    vector<int> soluc(n);
    int k = 0;
    int gasto = 0;
    int mejorGasto = std::numeric_limits<int>::max();
    vector<int> comprasPorSuper(m,0);
    resolver(soluc,k,n,m,gasto,mejorGasto,comprasPorSuper,precios,mejoresPrecios);
    if(mejorGasto == std::numeric_limits<int>::max()) cout << "Sin solucion factible\n";
    else cout << mejorGasto << '\n';
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
