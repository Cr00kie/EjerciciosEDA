// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <list>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>

using Jugador = std::string;
using Equipo = std::string;

class GestorFutbolistas {
private:

struct FichaJugador{
    Equipo equipo;
    std::list<Jugador>::iterator posFichaEquipo;
    std::unordered_set<Equipo> equiposALosQueHaPertenecido;
};
    std::unordered_map<Jugador, FichaJugador> jugadores;
    std::unordered_map<Equipo, std::list<Jugador>> equipos;


public:
    // Coste: O(1)
    void fichar(const Jugador& jugador, const Equipo& equipo) {
        // Comprobamos si el jugador ya esta dado de alta
        auto jugadorIt = jugadores.find(jugador);
        // Si no esta dado de alta
        if(jugadorIt == jugadores.end())
        {
            // Creamos una ficha para el nuevo jugador
            FichaJugador ficha;
        
            // Registramos en la ficha del equipo que el jugador pertenece a su plantilla
            equipos[equipo].push_front(jugador);

            // Ponemos los datos del jugador en su ficha
            ficha.equipo = equipo;
            ficha.posFichaEquipo = equipos[equipo].begin();
            ficha.equiposALosQueHaPertenecido.insert(equipo);

            // Registramos la ficha del jugador
            jugadores[jugador] = ficha;
        }
        // Si esta dado de alta y el equipo es distinto
        else if(equipo != jugadores[jugador].equipo){
            // Quitamos el fichaje de la ficha del equipo anterior
            equipos[jugadores[jugador].equipo].erase(jugadores[jugador].posFichaEquipo);

            // Registramos el jugador en su nuevo equipo
            equipos[equipo].push_front(jugador);

            // Actualizamos la ficha del jugador
            jugadores[jugador].equipo = equipo;
            jugadores[jugador].posFichaEquipo = equipos[equipo].begin();
            jugadores[jugador].equiposALosQueHaPertenecido.insert(equipo);
        }

    }

    // Coste: O(1)
    Equipo equipoActual(const Jugador& jugador) const {
        auto jugadorIt = jugadores.find(jugador);
        if(jugadorIt == jugadores.end()) throw std::domain_error("Jugador inexistente");
        return jugadorIt->second.equipo;
    }

    // Coste: O(1)
    int fichados(const Equipo& equipo) const {
        auto equipoIt = equipos.find(equipo);
        if(equipoIt == equipos.end()) throw std::domain_error("Equipo inexistente");
        return equipoIt->second.size();
    }

    // Coste: O(min(n, equipos[equipo].size()))
    std::list<Jugador> ultimosFichajes(const Equipo& equipo, int n) const {
        auto equipoIt = equipos.find(equipo);
        if(equipoIt == equipos.end()) throw std::domain_error("Equipo inexistente");

        // Copiamos n jugadores de una lista a otra
        std::list<Jugador> ret;
        auto itSource = equipoIt->second.begin();
        for(int i = 0; i < n && itSource != equipoIt->second.end(); ++i, ++itSource){
            ret.push_back(*itSource);
        }
        
        return ret;
    }

    // Coste: O(1)
    int cuantosEquipos(const Jugador& jugador) const {
        auto itJugador = jugadores.find(jugador);
        if(itJugador == jugadores.end()) return 0;

        return itJugador->second.equiposALosQueHaPertenecido.size();
    }
};


bool resuelveCaso() {
    std::string operacion;
    std::cin >> operacion;
    if (!std::cin) return false;

    GestorFutbolistas gestor;
    while (operacion != "FIN") {
        try {
            if (operacion == "fichar") {
                std::string jugador, equipo;
                std::cin >> jugador >> equipo;
                gestor.fichar(jugador, equipo);
            } else if (operacion == "equipo_actual") {
                std::string jugador;
                std::cin >> jugador;
                std::string equipo = gestor.equipoActual(jugador);
                std::cout << "El equipo de " << jugador << " es " << equipo << std::endl;
            } else if (operacion == "fichados") {
                std::string equipo;
                std::cin >> equipo;
                int n = gestor.fichados(equipo);
                std::cout << "Jugadores fichados por " << equipo << ": " << n << std::endl;
            } else if (operacion == "ultimos_fichajes") {
                std::string equipo;
                int n;
                std::cin >> equipo >> n;
                std::list<std::string> ultimos = gestor.ultimosFichajes(equipo, n);
                std::cout << "Ultimos fichajes de " << equipo << ": ";
                for (const auto& jugador : ultimos) {
                    std::cout << jugador << " ";
                }
                std::cout << std::endl;
            } else if (operacion == "cuantos_equipos") {
                std::string jugador;
                std::cin >> jugador;
                int n = gestor.cuantosEquipos(jugador);
                std::cout << "Equipos que han fichado a " << jugador << ": " << n << std::endl;
            } 
        } catch (std::exception& e) {
            std::cout << "ERROR: " << e.what() << "\n";
        }
        std::cin >> operacion;
    }

    std::cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) { }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
