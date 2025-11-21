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
using InfoProblema = unordered_map<NombreProblema, int>;

struct ResultadoEquipo{
    NombreEquipo nombre;
    int nProblemasResueltos;
    Minutos minutos;
};

struct InfoEquipo{
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

// Complejidad:
// O(n + e + elog(e)) con -> n = numero de entregas totales realizadas por los participantes
//                          -> e = numero de equipos que participan en el concurso
void procesaEnvios(vector<ResultadoEquipo>& resultados){
    unordered_map<NombreEquipo, InfoProblema> infoProblemasCadaEquipo;
    unordered_map<NombreEquipo, InfoEquipo> infoEquipos; 

    string equipo, problema, veredicto;
    int minuto;
    
    cin >> equipo;
    // O(n) siendo n el numero de entregas realizadas por los participantes
    while (equipo != "FIN") {
        cin >> problema >> minuto >> veredicto;

        auto& infoIntentosProblema = infoProblemasCadaEquipo[equipo][problema];
        auto& infoEquipo = infoEquipos[equipo];

        // Si el equipo no ha resuelto el problema todavia
        if (infoIntentosProblema != -1)
        {
            // Si el veredicto es CORRECTO
            if(veredicto == "AC"){
                infoEquipo.minutos += minuto + infoIntentosProblema*20;
                // tiempo de entrega-^ penalización acumulada-^
                infoEquipo.nProblemasResueltos++;
                infoIntentosProblema = -1;
            }
            else{
                // Guardamos la penalizacion en negativo para saber si el problema ha sido resuelto o no
                infoIntentosProblema++;
            }
        }
        
        cin >> equipo;
    }

    resultados.resize(infoEquipos.size());
    int i = 0;
    //O(e) siendo 'e' el numero de equipos
    for(auto it = infoEquipos.begin(); it != infoEquipos.end(); ++it)
    {
        resultados[i].nombre = it->first;
        resultados[i].minutos = it->second.minutos;
        resultados[i].nProblemasResueltos = it->second.nProblemasResueltos;
        ++i;
    }

    // O(eloge) siendo 'e' el numero de equipos que participan en el concurso
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