// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <cassert>
#include <utility>
#include <unordered_map>
#include <list>
#include <set>

using namespace std;


using paciente = string;
using gravedad = int;

class urgencias {
protected:
    unordered_map<paciente, pair<gravedad, list<paciente>::iterator>> pacientes;
    list<paciente> colaDeEspera[3]; // Tambien se podria hacer con una sola lista y guardando iteradores de donde comienzan, pero voy a probar asi
    set<paciente> pacientesRecuperados;
public:

    // coste:
    void nuevo_paciente(paciente p, gravedad g) {
        // Buscamos el paciente
        auto pacienteIt = pacientes.find(p);
        if(pacienteIt != pacientes.end()) throw domain_error("Paciente repetido");
        
        // Comprobamos la gravedad
        if(g < 1 || g > 3) throw domain_error("Gravedad incorrecta");
        
        // Lo metemos en la cola de espera
        colaDeEspera[g-1].push_back(p);
        // Registramos al paciente
        pacientes[p] = {g, --colaDeEspera[g-1].end()};
    }
    
    // coste:
    int gravedad_actual(paciente p) const {
        // Buscamos el paciente
        auto pacienteIt = pacientes.find(p);
        if(pacienteIt == pacientes.end()) throw domain_error("Paciente inexistente");
        
        // Devolvemos su gravedad
        return pacienteIt->second.first;
    }

    // coste:
    paciente siguiente() {
        // Buscamos la cola no vacia (siempre coste 3 en peor caso)
        int i = 2;
        while(i >= 0 && colaDeEspera[i].empty()) i--;
        // Si no hemos encontrado una cola vacia, error
        if(i < 0) throw domain_error("No hay pacientes");
        list<paciente>& primeraGravedadNoVacia = colaDeEspera[i];
        
        paciente ret = primeraGravedadNoVacia.front();
        primeraGravedadNoVacia.pop_front();
        pacientes.erase(ret);
        return ret;
    }

    // coste:
    void mejora(paciente p) {
        // Buscamos el paciente
        auto pacienteIt = pacientes.find(p);
        if(pacienteIt == pacientes.end()) throw domain_error("Paciente inexistente");

        // Lo borramos de su lista anterior
        colaDeEspera[pacienteIt->second.first-1].erase(pacienteIt->second.second);
        // Le quitamos gravedad
        int gravedad = --pacienteIt->second.first;
        if(gravedad >= 1){
            // Si todavia se encuentra mal, lo volvemos a meter
            colaDeEspera[gravedad-1].push_front(p);
            // Actualizamos el iterador
            pacienteIt->second.second = --colaDeEspera[gravedad-1].end();
        }
        else{
            // Lo metemos entre los recuperados
            pacientesRecuperados.insert(p);
            // Lo quitamos del registro
            pacientes.erase(p);
        }

    }

    // coste:
    list<paciente> recuperados() const {
        return list<paciente>(pacientesRecuperados.begin(), pacientesRecuperados.end());
    }

    void imprimeCola()
    {
        std::cout << "----------------------\n";
        for (int i = 0; i < 3; i++)
        {
            std::cout << "lista " << i << ": ";
            for (auto it = colaDeEspera[i].begin(); it != colaDeEspera[i].end(); ++it)
            {
                std::cout << *it << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "----------------------\n";
    }
    void imprimeRegistro(){
        std::cout << "----------------------\n";
        std::cout << "pacientes registrados: ";
        for (auto it = pacientes.begin(); it != pacientes.end(); ++it)
        {
            std::cout << it->first << ' ';
        }
        std::cout << '\n';
        std::cout << "----------------------\n";
    }
    void imprimeRecuperados(){
        std::cout << "----------------------\n";
        std::cout << "pacientes recuperados: ";
        for (auto it = pacientesRecuperados.begin(); it != pacientesRecuperados.end(); ++it)
        {
            std::cout << *it << ' ';
        }
        std::cout << '\n';
        std::cout << "----------------------\n";
    }
};

bool resuelveCaso() { // No tocar esta función
    string orden, pac;
    int grav;
    cin >> orden;
    if (!cin) return false;
   
    urgencias sala;
   
    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> pac >> grav;
                sala.nuevo_paciente(pac, grav);
            } else if (orden == "gravedad_actual") {
                cin >> pac;
                int g = sala.gravedad_actual(pac);
                cout << "La gravedad de " << pac << " es " << g << '\n';
            } else if (orden == "siguiente") {
                string p = sala.siguiente();
                cout << "Siguiente paciente: " << p << '\n';
            } else if (orden == "recuperados") {
                auto lista = sala.recuperados();
                cout << "Lista de recuperados:";
                for (auto & p : lista)
                    cout << ' ' << p;
                cout << '\n';
            } else if (orden == "mejora") {
                cin >> pac;
                sala.mejora(pac);
            } 
        } catch (std::domain_error e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }

        // std::cout << "=================================\n";
        // std::cout << "Nueva instruccion: " << orden << '\n';
        // sala.imprimeCola();
        // sala.imprimeRegistro();
        // sala.imprimeRecuperados();
        // std::cout << "=================================\n";

        std::cin >> orden;

        
    }
    std::cout << "---\n";
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
