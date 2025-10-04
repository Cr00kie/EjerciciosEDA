// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

// Este algoritmo tiene complejidad lineal O(n)
// En el peor caso, tendriamos que recorrer (n + m) (n y m siendo los tamanios d elos vectores de entrada) 
//      porque todos sus elementos serian distintos y se haria el primer while para uno de los dos y uno de
//      los siguientes whiles para el restante.
//
// [Cuestion del enunciado]:
// Si *NO ESTAN ORDENADOS*, podriamos ordenarlos con coste O(nlogn) y luego aplicar el algoritmo ya ordenados.
//      Por tanto, el coste seria O(nlogn + mlogm + n + m), y la cota superior seria O(nlogn) 
void comparaListados(vector<string> const& eda, vector<string> const& tpv, 
    vector<string>& comunes, vector<string>& soloEda, vector<string>& soloTpv){
    
    int idxEDA = 0, idxTPV = 0;
    
    while(idxEDA < eda.size() && idxTPV < tpv.size()){

        if(eda[idxEDA] == tpv[idxTPV]){
            comunes.push_back(eda[idxEDA]);
            ++idxEDA;
            ++idxTPV;
        }
        else if(eda[idxEDA] < tpv[idxTPV]){
            soloEda.push_back(eda[idxEDA]);
            ++idxEDA;
        }
        else{
            soloTpv.push_back(tpv[idxTPV]);
            ++idxTPV;
        }
    }

    while(idxEDA < eda.size()){
        soloEda.push_back(eda[idxEDA]);
        ++idxEDA;
    }

    while(idxTPV < tpv.size()){
        soloTpv.push_back(tpv[idxTPV]);
        ++idxTPV;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<string> eda(n);
    vector<string> comunes;
    vector<string> soloEda;
    vector<string> soloTpv;
    for (string& e : eda) cin >> e;
    cin >> n;
    vector<string> tpv(n);
    for (string& e : tpv) cin >> e;
    comparaListados(eda,tpv,comunes,soloEda,soloTpv);
    for (string& e : comunes) cout << e << " ";
    cout << endl;
    for (string& e : soloEda) cout << e << " ";
    cout << endl;
    for (string& e : soloTpv) cout << e << " ";
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
