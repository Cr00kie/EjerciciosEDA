// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

using NombreEquipo = string;
using NombreProblema = string;
using Minutos = int;

struct ResultadoEquipo{
    NombreEquipo nombre;
    int nProblemasResueltos;
    Minutos minutos;
};

bool comparaEquipos(ResultadoEquipo& e1, ResultadoEquipo& e2){
    if(e1.nProblemasResueltos > e2.nProblemasResueltos) return true;
    else if (e2.nProblemasResueltos > e1.nProblemasResueltos) return false;
    else if (e1.minutos < e2.minutos) return true;
    else if (e2.minutos < e1.minutos) return false;
    else if (e1.nombre < e2.nombre) return true;
    else return false;
}

void procesaEnvios(vector<ResultadoEquipo>& resultados){
    unordered_map<NombreEquipo, unordered_map<NombreProblema, pair<Minutos, bool>>> resultadoPorEquipo;

    string equipo, problema, veredicto;
    int minuto;
    
    cin >> equipo;
    while (equipo != "FIN") {
        cin >> problema >> minuto >> veredicto;

        auto& resultadoProblema = resultadoPorEquipo[equipo][problema];

        // Si el equipo no ha resuelto el problema todavia
        if(!resultadoProblema.second)
        {
            // Si el veredicto es CORRECTO
            if(veredicto == "AC"){
                resultadoProblema.first = minuto   -   resultadoProblema.first;
                resultadoProblema.second = true;
                // tiempo de entrega-^ penalización acumulada-^
            }
            else{
                // Guardamos la penalizacion en negativo para saber si el problema ha sido resuelto o no
                resultadoProblema.first -= 20;
            }
        }
        
        cin >> equipo;
    }

    resultados.resize(resultadoPorEquipo.size());
    int i = 0;
    for(auto it = resultadoPorEquipo.begin(); it != resultadoPorEquipo.end(); ++it){
        resultados[i].nombre = it->first;
        for(auto problema = it->second.begin(); problema != it->second.end(); ++problema){
            if(problema->second.second){
                resultados[i].nProblemasResueltos++;
                resultados[i].minutos += problema->second.first;
            }
        }
        ++i;
    }

    sort(resultados.begin(), resultados.end(), comparaEquipos);
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    //...
    vector<ResultadoEquipo> resultados;
    procesaEnvios(resultados);

    for(ResultadoEquipo& r : resultados) std::cout << r.nombre << ' ' << r.nProblemasResueltos << ' ' << r.minutos << '\n';
    cout << "---\n";
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
    //system("PAUSE");
#endif

    return 0;
}