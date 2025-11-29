// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <string>
#include <algorithm>

using Estado = std::string;
using Partido = std::string;
using Votos = int;

class ConteoVotos {

private:
    struct InfoEstado{
        int numCompromisarios;
        Partido ganador;
        Votos maxVotos = 0;
        std::unordered_map<Partido, Votos> votosPorPartido;
    };

    struct InfoPartido{
        Partido nombre;
        int compromisariosTotales = 0;
    };

   std::unordered_map<Estado, InfoEstado> infoEstados;
   std::unordered_map<Partido, int> infoPartidos;

public:

    void nuevo_estado(const Estado &nombre, int num_compromisarios) {
        auto insertInfo = infoEstados.insert({nombre, {num_compromisarios}});
        if(!insertInfo.second) throw std::domain_error("Estado ya existente");
    }  
    
    void sumar_votos(const Estado &estado, const Partido &partido, int num_votos) {
        auto estadoIt = infoEstados.find(estado);
        if(estadoIt == infoEstados.end()) throw std::domain_error("Estado no encontrado");
        estadoIt->second.votosPorPartido[partido] += num_votos;
        if(estadoIt->second.votosPorPartido[partido] > estadoIt->second.maxVotos){
            // Quitamos los compromisarios del ganador anterior
            infoPartidos[estadoIt->second.ganador] -= estadoIt->second.numCompromisarios;
            // Actualizamos los votos maximos
            estadoIt->second.maxVotos = estadoIt->second.votosPorPartido[partido];
            // Guardamos el partido ganador
            estadoIt->second.ganador = partido;
            // Sumamos los compromisarios al partido que va ganando
            infoPartidos[estadoIt->second.ganador] += estadoIt->second.numCompromisarios;
        }
    }

    Partido ganador_en(const Estado &estado) const {
        auto estadoIt = infoEstados.find(estado);
        if(estadoIt == infoEstados.end()) throw std::domain_error("Estado no encontrado");
        return estadoIt->second.ganador;
    }

    std::vector<std::pair<Partido,int>> resultados() const {
        std::vector<std::pair<Partido, int>> ret;
        for(auto it = infoPartidos.begin(); it != infoPartidos.end(); ++it){
            if(it->second > 0) ret.push_back({it->first, it->second});
        }
        std::sort(ret.begin(), ret.end());
        return ret;
    }

}; 


bool resuelveCaso() {
    std::string comando;
    std::cin >> comando;
    if (!std::cin) return false;

    ConteoVotos elecciones;

    while (comando != "FIN") {
        try {
            if (comando == "nuevo_estado") {
                Estado estado;
                int num_compromisarios;
                std::cin >> estado >> num_compromisarios;
                elecciones.nuevo_estado(estado, num_compromisarios);
            } else if (comando == "sumar_votos") {
                Estado estado;
                Partido partido;
                int num_votos;
                std::cin >> estado >> partido >> num_votos;
                elecciones.sumar_votos(estado, partido, num_votos);
            } else if (comando == "ganador_en") {
                Estado estado;
                std::cin >> estado;
                Partido ganador  = elecciones.ganador_en(estado);
                std::cout << "Ganador en " << estado << ": " << ganador << "\n";
            } else if (comando == "resultados") {
                for (const auto &par : elecciones.resultados()) {
                    std::cout << par.first << " " << par.second << "\n";
                }
            }
        } catch (std::exception &e) {
            std::cout << e.what() << "\n";
        }
        std::cin >> comando;
    }

    std::cout << "---\n";
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
#endif
    while(resuelveCaso()) { }

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
