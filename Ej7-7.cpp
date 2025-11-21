// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>
using namespace std;


using DNI = string;

class carnet_puntos {
private:
    unordered_map<DNI, int> puntosPorConductor;
    unordered_map<int, int> numConductorConPuntos;

public:
    carnet_puntos() {} 

    // Complejidad:
    void nuevo(DNI const& conductor) {
        // if(puntosPorConductor.try_emplace(conductor, 15).second)
        //     throw std::domain_error("Conductor duplicado");
        if(puntosPorConductor.count(conductor))
            throw std::domain_error("Conductor duplicado");

        puntosPorConductor[conductor] = 15;
        numConductorConPuntos[15]++;
    }

    // Complejidad:
    void quitar(DNI const& conductor, int puntos) {
        auto cond = puntosPorConductor.find(conductor);
        if(cond == puntosPorConductor.end())
            throw std::domain_error("Conductor inexistente");
        
        numConductorConPuntos[cond->second]--;
        cond->second -= puntos;
        if(cond->second < 0) cond->second = 0;
        numConductorConPuntos[cond->second]++;
    }

    // Complejidad:
    int consultar(DNI const& conductor) const {
        auto cond = puntosPorConductor.find(conductor);
        if(cond == puntosPorConductor.end())
            throw std::domain_error("Conductor inexistente");
        else 
            return cond->second;
    }

    // Complejidad:
    int cuantos_con_puntos(int puntos) const {
        if(puntos < 0 || puntos > 15)
            throw std::domain_error("Puntos no validos");
        
        auto res = numConductorConPuntos.find(puntos);
        
        return res == numConductorConPuntos.end() ? 0 : res->second;
    }
};

bool resuelveCaso() {
    std::string orden, dni;
    int punt;
    std::cin >> orden;
    if (!std::cin)
        return false;
    
    carnet_puntos dgt;
    
    while (orden != "FIN") {
        try {
            if (orden == "nuevo") {
                cin >> dni;
                dgt.nuevo(dni);
            } else if (orden == "quitar") {
                cin >> dni >> punt;
                dgt.quitar(dni, punt);
            } else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            } else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            } else
                cout << "OPERACION DESCONOCIDA\n";
        } catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}


int main() {
    // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());
    
    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
