// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

using Heroe = string;
using Villano = string;

class SistemaBatallas {
private:
    struct HeroeInfo{
        int hp;
        map<string, int> ataques;
        list<string>::iterator anchor;
    };
    struct VillanoInfo{
        int hp;
        int damage;
        list<string>::iterator anchor;
    };

    unordered_map<Heroe, HeroeInfo> heroes;
    unordered_map<Villano, VillanoInfo> villains;
    list<string> battleQueue;

public:
    // Coste:
    void aparece_villano(Villano const& v, int puntos, int valor){
        // Buscamos villano
        auto villainIt = villains.find(v);
        if(villainIt != villains.end()) throw invalid_argument("Personaje ya existente");

        // Creamos villano
        battleQueue.push_back(v);
        villains[v] = {puntos, valor, --battleQueue.end()};
    }

    // Coste:
    void aparece_heroe(Heroe const& h, int puntos){
        // Buscamos heroe
        auto heroeIt = heroes.find(h);
        if(heroeIt != heroes.end()) throw invalid_argument("Personaje ya existente");

        // Creamos heroe
        battleQueue.push_back(h);
        heroes[h].hp = puntos;
        heroes[h].anchor = --battleQueue.end();
    }

    // Coste:
    void aprende_ataque(Heroe const& h, string const& ataque, int valor){
        // Buscamos heroe
        auto heroeIt = heroes.find(h);
        if(heroeIt == heroes.end()) throw invalid_argument("Heroe inexistente");

        // Buscamos ataque
        auto ataqueIt = heroeIt->second.ataques.find(ataque);
        if(ataqueIt != heroeIt->second.ataques.end()) throw invalid_argument("Ataque repetido");

        // Ponemos ataque
        heroeIt->second.ataques[ataque] = valor;
    }

    // Coste:
    vector<pair<string,int>> mostrar_ataques(Heroe const& h){
        // Buscamos heroe
        auto heroeIt = heroes.find(h);
        if(heroeIt == heroes.end()) throw invalid_argument("Heroe inexistente");
        
        // Ponemos cada ataque en la solucion
        vector<pair<string,int>> res(heroeIt->second.ataques.size());
        int i = 0;
        for(auto it = heroeIt->second.ataques.begin(); it != heroeIt->second.ataques.end(); ++it){
            res[i] = {it->first, it->second};
            
            ++i;
        }
        return res;
    }

    // Coste:
    vector<pair<string,int>> mostrar_turnos(){
        vector<pair<string,int>> res(battleQueue.size());
        int i = 0;
        for(auto it = battleQueue.begin(); it != battleQueue.end(); ++it){
            int hpPje = -1;
            // Buscamos heroe o villano
            auto heroeIt = heroes.find(*it);
            auto villainIt = villains.find(*it);
            // Cogemos el HP del pje
            if(heroeIt != heroes.end()) hpPje = heroeIt->second.hp;
            else if(villainIt != villains.end()) hpPje = villainIt->second.hp;

            // Ponemos pje en la lista
            res[i] = {(*it), hpPje};

            ++i;
        }
        return res;
    }

    // Coste:
    bool villano_ataca(Villano const& v, Heroe const& h){
        bool resultado = false;

        // Buscamos villano
        auto villainIt = villains.find(v);
        if(villainIt == villains.end()) throw invalid_argument("Villano inexistente");

        // Buscamos heroe
        auto heroeIt = heroes.find(h);
        if(heroeIt == heroes.end()) throw invalid_argument("Heroe inexistente");

        // Coger pje con el turno actual
        string pjeActual = battleQueue.front();
        if(v != pjeActual) throw invalid_argument("No es su turno");
        
        // Quitar vida al heroe
        heroeIt->second.hp -= villainIt->second.damage;
        if(heroeIt->second.hp <= 0){
            // Quitar al heroe del battleQueue y de los datos
            battleQueue.erase(heroeIt->second.anchor);
            heroes.erase(heroeIt);
            resultado = true;
        }

        // Actualizar posicion del villano
        battleQueue.pop_front();
        battleQueue.push_back(pjeActual);

        return resultado;
    }

    // Coste:
    bool heroe_ataca(Heroe const& h, string const& ataque, Villano const& v){
        bool resultado = false;

        // Buscamos villano
        auto villainIt = villains.find(v);
        if(villainIt == villains.end()) throw invalid_argument("Villano inexistente");

        // Buscamos heroe
        auto heroeIt = heroes.find(h);
        if(heroeIt == heroes.end()) throw invalid_argument("Heroe inexistente");

        // Coger pje con el turno actual
        string pjeActual = battleQueue.front();
        if(h != pjeActual) throw invalid_argument("No es su turno");

        // Buscamos ataque
        auto ataqueIt = heroeIt->second.ataques.find(ataque);
        if(ataqueIt == heroeIt->second.ataques.end()) throw invalid_argument("Ataque no aprendido");
        
        // Quitar vida el villano
        villainIt->second.hp -= ataqueIt->second;
        if(villainIt->second.hp <= 0){
            // Quitar al heroe del battleQueue y de los datos
            battleQueue.erase(villainIt->second.anchor);
            villains.erase(villainIt);
            resultado = true;
        }

        // Actualizar posicion del villano
        battleQueue.pop_front();
        battleQueue.push_back(pjeActual);

        return resultado;
    }

};


bool resuelveCaso() { // No tacar nada de esta función!
    string comando;
    cin >> comando;
    if (!cin) return false;

    SistemaBatallas sistema;
    Villano v; Heroe h; 
    string ataque; int ptos; int valor;
    while (comando != "FIN") {
        try {
            if (comando == "aparece_villano") {
                cin >> v >> ptos >> valor;
                sistema.aparece_villano(v, ptos, valor);
            } else if (comando == "aparece_heroe") {
                cin >> h >> ptos;
                sistema.aparece_heroe(h, ptos);
            } else if (comando == "aprende_ataque") {
                cin >> h >> ataque >> valor;
                sistema.aprende_ataque(h, ataque, valor);
            } else if (comando == "mostrar_ataques") {
                cin >> h;
                auto ataques = sistema.mostrar_ataques(h);
                cout << "Ataques de " << h << endl;
                for(auto it = ataques.begin(); it != ataques.end(); ++it){
                    cout << it->first << " " << it->second << "\n";
                }
            } else if (comando == "mostrar_turnos") {
                cout << "Turno: " << endl;
                auto turnos = sistema.mostrar_turnos();
                for(auto it = turnos.begin(); it != turnos.end(); ++it){
                    cout << it->first << " " << it->second << "\n";
                }
            } else if (comando == "villano_ataca") {
                cin >> v >> h;
                bool derrotado = sistema.villano_ataca(v, h);
                cout << v << " ataca a " << h << endl;
                if (derrotado) cout << h << " derrotado" << endl;
            } else if (comando == "heroe_ataca") {
                cin >> h >> ataque >> v;
                bool derrotado = sistema.heroe_ataca(h, ataque, v);
                cout << h << " ataca a " << v << endl;
                if (derrotado) cout << v << " derrotado" << endl;
            }
        } catch (std::exception& e) {
            cout << "ERROR: " << e.what() << "\n";
        }
        cin >> comando;
    }

    cout << "---\n";
    return true;
}

//#define DOMJUDGE
int main() {
#ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(resuelveCaso()) { }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
