// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void resolver(int n, int k, int& sol, std::vector<bool>& marcasFilas, std::vector<bool>& marcasDiagsDesc, std::vector<bool>& marcasDiagsAsc) {
    for(int i = 0; i < n; i++){
        // std::cout << "k: " << k << ", i: " << i << '\n';
        if(!marcasFilas[i] && !marcasDiagsDesc[i-k+n] && !marcasDiagsAsc[i+k]){
            // for(int j = 0; j < n; j++)
            // {
            //     for(int ka = 0; ka < n; ka++){
            //         if(marcasFilas[j] || marcasDiagsDesc[j-ka+n] || marcasDiagsAsc[j+ka]){
            //             std::cout << "X ";
            //         }
            //         else if(j == i && k == ka){
            //             std::cout << "I ";
            //         }
            //         else std::cout << "O ";
            //     }
            //     std::cout << "\n";
            // }
            // std::cout << '\n';
            if(k == n-1){
                // std::cout << "SOLUCION\n";
                sol++;
            }
            else{
                marcasFilas[i] = true;
                marcasDiagsDesc[i-k+n] = true;
                marcasDiagsAsc[i+k] = true;
                resolver(n, k+1, sol, marcasFilas, marcasDiagsDesc, marcasDiagsAsc);
                marcasFilas[i] = false;
                marcasDiagsDesc[i-k+n] = false;
                marcasDiagsAsc[i+k] = false;
            }
        }
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::cin >> n;
    int sol = 0;
    std::vector<bool> marcasFilas(n, 0);
    std::vector<bool> marcasDiagsDesc(n*2, 0);
    std::vector<bool> marcasDiagsAsce(n*2, 0);
    resolver(n, 0, sol, marcasFilas, marcasDiagsDesc, marcasDiagsAsce);
    std::cout << sol << '\n';
}

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
     system("PAUSE");
     #endif
    
    return 0;
}