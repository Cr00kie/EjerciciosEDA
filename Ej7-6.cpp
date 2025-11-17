// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <list>
using namespace std;


using Pelicula = string;
using Actor = string;
using RepartosPeliculas = unordered_map<string, unordered_map<string, int>>;

// Complejidad: numPeliculas * numActores * (1 + 1)
void leerRepartos(int numPeliculas, RepartosPeliculas& peliculas){
    Pelicula peli; int numActores;
    Actor actor; int minutos;
    for (int i = 0; i < numPeliculas; ++i){
        cin >> peli; cin >> numActores;
        for (int j = 0; j < numActores; ++j){
            cin >> actor >> minutos;
            peliculas[peli][actor] = minutos;
        }
    }
}

// Coste +Infinito, que asco de funcion
void procesarEmisiones(RepartosPeliculas const& repartos, vector<string> const& secEmisiones){
    map<string, int> minTotalesActor;
    int maxMin = 0;

    unordered_map<string, int> numEmisionsPeliculas;
    string peliculaMasEmitida;
    int emisionesPeliMasEmitida = 0;

    for(const string& emision : secEmisiones){
        for(auto it = repartos.at(emision).begin(); it != repartos.at(emision).end(); ++it){
            minTotalesActor[it->first] = 0;
        }
        numEmisionsPeliculas[emision] = 0;
    }

    for(const string& emision : secEmisiones){
        for(auto it = repartos.at(emision).begin(); it != repartos.at(emision).end(); ++it){
            minTotalesActor[it->first] += it->second;
            if(minTotalesActor[it->first] > maxMin){
                maxMin = minTotalesActor[it->first];
            }
        }
        numEmisionsPeliculas[emision] += 1;

        if(numEmisionsPeliculas[emision] >= emisionesPeliMasEmitida){
            peliculaMasEmitida = emision;
            emisionesPeliMasEmitida = numEmisionsPeliculas[emision];
        }
    }

    // Imprime pelicula mas emitida
    std::cout << emisionesPeliMasEmitida << ' ' << peliculaMasEmitida << '\n';

    // Imprime actores con mas minutos
    std::cout << maxMin;
    // Esto me duele mucho hacerlo
    for(auto it = minTotalesActor.begin(); it != minTotalesActor.end(); ++it){
        if(it->second == maxMin) std::cout << ' ' << it->first;
    }
    
    std::cout << '\n';
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numPelis, numEmisiones;
    cin >> numPelis;
    if (numPelis == 0)
        return false;

    // Lectura de los repartos de las peliculas
    RepartosPeliculas repartos;
    leerRepartos(numPelis, repartos);

    // Lectura de la secuencia de peliculas emitidas en vector<string>
    cin >> numEmisiones;
    vector<string> secEmisiones(numEmisiones);
    for (string& s : secEmisiones) cin >> s;

    procesarEmisiones(repartos, secEmisiones);

    return true;
}


//#define DOMJUDGE
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
#endif

    return 0;
}