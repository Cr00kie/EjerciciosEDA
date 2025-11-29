// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <unordered_map>
#include <algorithm>
using namespace std;


using DNI = string;


class carnet_puntos {
private:
using InfoConductor = pair<int, list<DNI>::iterator>;
    unordered_map<DNI, InfoConductor> infoConductor;
    list<DNI> numConductoresConPuntos[16];

public:
    carnet_puntos() {
    } 

    // Complejidad:
    void nuevo(DNI const& conductor) {
        // if(puntosPorConductor.try_emplace(conductor, 15).second)
        //     throw std::domain_error("Conductor duplicado");
        if(infoConductor.count(conductor))
            throw std::domain_error("Conductor duplicado");

        infoConductor[conductor].first = 15;
        numConductoresConPuntos[15].push_front(conductor);
        infoConductor[conductor].second = numConductoresConPuntos[15].begin();
    }

    // Complejidad:
    void quitar(DNI const& conductor, int puntos) {
        auto cond = infoConductor.find(conductor);
        if(cond == infoConductor.end())
            throw std::domain_error("Conductor inexistente");
        
        numConductoresConPuntos[cond->second.first].erase(cond->second.second);
        cond->second.first -= puntos;
        if(cond->second.first < 0) cond->second.first = 0;
        numConductoresConPuntos[cond->second.first].push_front(conductor);
        infoConductor[conductor].second = numConductoresConPuntos[cond->second.first].begin();
    }

    // Complejidad:
    int consultar(DNI const& conductor) const {
        auto cond = infoConductor.find(conductor);
        if(cond == infoConductor.end())
            throw std::domain_error("Conductor inexistente");
        else 
            return cond->second.first;
    }

    // Complejidad:
    int cuantos_con_puntos(int puntos) const {
        if(puntos < 0 || puntos > 15)
            throw std::domain_error("Puntos no validos");
        
        return numConductoresConPuntos[puntos].size();
    }

    void recuperar(DNI const& conductor, int puntos){
        auto cond = infoConductor.find(conductor);
        if(cond == infoConductor.end())
            throw std::domain_error("Conductor inexistente");
        
        int puntosAntes = cond->second.first;
        cond->second.first += puntos;
        if(cond->second.first > 15) cond->second.first = 15;
        if(puntosAntes != cond->second.first){
            numConductoresConPuntos[puntosAntes].erase(infoConductor[conductor].second);
            numConductoresConPuntos[cond->second.first].push_front(conductor);
            infoConductor[conductor].second = numConductoresConPuntos[cond->second.first].begin();
        }
    }

    list<DNI> lista_por_puntos(int puntos){
        if(puntos < 0 || puntos > 15)
            throw std::domain_error("Puntos no validos");
            
        return numConductoresConPuntos[puntos];
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
            } else if (orden == "recuperar") {
                cin >> dni >> punt;
                dgt.recuperar(dni, punt);
            } else if (orden == "consultar") {
                cin >> dni;
                punt = dgt.consultar(dni);
                cout << "Puntos de " << dni << ": " << punt << '\n';
            } else if (orden == "cuantos_con_puntos") {
                cin >> punt;
                int cuantos = dgt.cuantos_con_puntos(punt);
                cout << "Con " << punt << " puntos hay " << cuantos << '\n';
            } else if (orden == "lista_por_puntos") {
                cin >> punt;
                auto const& lista = dgt.lista_por_puntos(punt);
                cout << "Tienen " << punt << " puntos:";
                for (auto const& dni : lista)
                    cout << ' ' << dni;
                cout << '\n';
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
