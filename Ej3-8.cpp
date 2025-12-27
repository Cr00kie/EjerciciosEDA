// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// No haya mas de dos luces seguidas del mismo color
// En cualquier punto de la tira la suma de las luces de un color no supere en mas de una unidad la suma de las luces de los demas colores
// No deben consumir mas de una cierta cantidad de energia

void resolver(std::vector<int>& soluc, int& combinaciones, int n, int m, int k, int consumoMax, int& consumo, std::vector<int>& consumosPorColor, std::vector<int>& totalesPorColor){
    for(int i = 0; i < m; i++){
        soluc[k] = i;

        consumo += consumosPorColor[i];

        totalesPorColor[i]++; 

        // std::cout << "Tira (" << k << "): ";
        //         for(int luz = 0; luz < k+1; luz++) std::cout << soluc[luz] << ' ';
        //         std::cout << '\n';

        bool suficienteVariedad = true;
        int luces = 0;
        // std::cout << "Totales por color: ";
        while(luces < totalesPorColor.size() && suficienteVariedad){
            // std::cout << totalesPorColor[luces] << ' ';
            if(totalesPorColor[luces] - (k+1-totalesPorColor[luces]) >= 2) {
                // std::cout << totalesPorColor[luces] << "-" << (k+1-totalesPorColor[luces]) << "< 2\n";
                suficienteVariedad = false;
            }
            luces++;
        }
        // std::cout << '\n';


        if((k < 2 || (soluc[k] != soluc[k-1] || soluc[k] != soluc[k-2])) &&// No haya mas de dos luces seguidas
           consumo <= consumoMax && // Que cumpla las leyes de consumo
           suficienteVariedad){
            if(k == n-1){
                // std::cout << "Tira final: ";
                // for(int luz : soluc) std::cout << luz << ' ';
                // std::cout << '\n';
                combinaciones++;
            }
            else{
                resolver(soluc, combinaciones, n, m, k+1, consumoMax, consumo, consumosPorColor, totalesPorColor);
            }
        }
        // else{
        //     if(!(k < 2 || (soluc[k] != soluc[k-1] && soluc[k] != soluc[k-2]))){
        //         std::cout << "!(" << k << " < 1" << " || (" << soluc[k] <<" != "<< soluc[k-1] <<" && "<< soluc[k] <<" != "<< soluc[k-2]<<"))\n";
        //         std::cout << "REPETIDAS\n";
        //     }
        //     if(consumo > consumoMax){
        //         std::cout << "CONSUMO EXCEDIDO\n";
        //     }
        //     if(!suficienteVariedad){
        //         std::cout << "POCA VARIEDAD\n";
        //     }
        // }

        consumo -= consumosPorColor[i];

        totalesPorColor[i]--;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m, consumoMax;
    int combinaciones = 0;
    cin >> n;
    if (n == 0) return false;
    cin >> m >> consumoMax;
    vector<int> consumosPorColor(m);
    for (int& e : consumosPorColor) cin >> e;
    vector<int> soluc(n);
    int k = 0;
    int consumo = 0;
    vector<int> totalesPorColor(m,0);
    resolver(soluc, combinaciones, n, m, k, consumoMax, consumo, consumosPorColor, totalesPorColor);
    // Salida
    std::cout << combinaciones << '\n';
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
    //system("PAUSE");
#endif

    return 0;
}