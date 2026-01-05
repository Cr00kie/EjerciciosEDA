// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, vector<T> const& v){
    for (auto& e : v) out << e << " ";
    return out;
}


// función que resuelve el problema
void resolver(vector<int>& soluc, int k, int n, int m, int l, vector<int>& kilosPorArea, vector<vector<int>> const& kilosPorVoluntario, int& areasLimpias, int& lodoQuitado, int& maxLodoQuitado, const vector<int>& estimacionOptimista ) {
    for(int i = 0; i < m; i++){
        soluc[k] = i;

        // Si todavia queda lodo en el area
        if(kilosPorArea[i] > 0){
            // Sumamos el lodo quitado por el voluntario al computo global
            lodoQuitado += std::min(kilosPorVoluntario[k][i], kilosPorArea[i]);
            // Quitamos del area los kilos que levantar'ia el voluntario
            kilosPorArea[i] -= kilosPorVoluntario[k][i];
            // Si ya no quedan m'as kilos en el area, aumentamos el contador de areas limpias
            if(kilosPorArea[i] <= 0) areasLimpias++;

            // Solo continuamos si la estimacion optimista nos dice que todav'ia podemos superar el maximo
            if(lodoQuitado + estimacionOptimista[k] > maxLodoQuitado){

                // Comprobamos si ya se han asignado todos los voluntarios, si se han limpiado el minimo de areas y si la cantidad de lodo quitada es mejor que la de otra solucion
                if(k == n-1
                && areasLimpias >= l
                && lodoQuitado > maxLodoQuitado){
                    // Marcamos la nueva mejor solucion
                    maxLodoQuitado = lodoQuitado;
                }
                // Si todavia estamos explorando seguimos
                else if(k < n-1){
                    resolver(soluc, k+1, n, m, l, kilosPorArea, kilosPorVoluntario, areasLimpias, lodoQuitado, maxLodoQuitado, estimacionOptimista); 
                }
            }

            // Si el area estaba previamente vac'ia, este voluntario fue el ultimo en vaciarla
            if(kilosPorArea[i] <= 0) areasLimpias--;
            // Volvemos a poner en el area los kilos que levant'o el voluntario
            kilosPorArea[i] += kilosPorVoluntario[k][i];
            // Descontamos el lodo quitado por el voluntario del computo global
            lodoQuitado -= std::min(kilosPorVoluntario[k][i], kilosPorArea[i]);
        }
    }
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> kilosPorArea(m);
    for (int i = 0; i < m; ++i) {
        cin >> kilosPorArea[i];
    }
    vector<vector<int>> kilosPorVoluntario(n, vector<int>(m));
    for (int i = 0; i < n ; ++i)
        for (int j = 0; j < m; ++j)
            cin >> kilosPorVoluntario[i][j];

    // Contiene la cantidad maxima de las areas, acumulados de fin a principio, que puede levantar cada voluntario
    vector<int> estimacionOptimista(n);
    for (int i = n-1; i >= 0; --i){
        // Buscamos por cada voluntario, cual es el maximo de lodo que puede quitar
        int maxLodoVoluntario = 0;
        for (int j = m-1; j >= 0; --j){
            if(maxLodoVoluntario < kilosPorVoluntario[i][j]) maxLodoVoluntario = kilosPorVoluntario[i][j];
        }
        // Vamos acumulando los maximos de lodo que se pueden quitar de fin a principio
        estimacionOptimista[i] = i == n-1 ? 0 : estimacionOptimista[i+1];
        estimacionOptimista[i] += maxLodoVoluntario;
    }

    vector<int> soluc(n);
    int k = 0;
    int areasLimpias = 0;
    int lodoQuitado = 0;
    int maxLodoQuitado = -1;
    resolver(soluc, k, n, m, l, kilosPorArea, kilosPorVoluntario, areasLimpias, lodoQuitado, maxLodoQuitado, estimacionOptimista);
    if (maxLodoQuitado == -1) cout << "IMPOSIBLE" << endl;
    else cout << maxLodoQuitado << endl;
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
