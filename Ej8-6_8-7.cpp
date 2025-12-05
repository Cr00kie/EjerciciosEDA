// Adrian Isasi
// EDA-GDV33


#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <list>
#include <unordered_map>
using namespace std;

using cancion = std::string;
using artista = std::string;

class iPud {
    private:
    struct InfoCancion{
        artista autor;
        int duracion;
        list<cancion>::iterator posLista;
        list<cancion>::iterator posHistorial;
    };

    unordered_map<cancion, InfoCancion> registroCanciones;
    list<cancion> listaReproduccion;
    list<cancion> historialReproduccion;
    int tiempoListaReproduccion = 0;

    public:
    void addSong(cancion titulo, artista autor, int tiempo){
        // Buscamos la cancion
        auto itCancion = registroCanciones.find(titulo);
        if(itCancion != registroCanciones.end()) throw invalid_argument("Cancion ya existente");

        // Registramos la cancion
        registroCanciones[titulo] = {autor, tiempo, listaReproduccion.end(), historialReproduccion.end()};
    }

    void addToPlayList(cancion titulo){
        // Buscamos la cancion
        auto itCancion = registroCanciones.find(titulo);
        if(itCancion == registroCanciones.end()) throw invalid_argument("Cancion inexistente");

        // Si la cancion no esta en la play list
        if(itCancion->second.posLista == listaReproduccion.end()){
            // Metemos la cancion en la playlist
            itCancion->second.posLista = listaReproduccion.insert(listaReproduccion.end(), titulo);
            tiempoListaReproduccion += itCancion->second.duracion;
        }
    }

    cancion current() const {
        if(listaReproduccion.empty()) throw invalid_argument("current");
        return listaReproduccion.front();
    }

    void play() {
        if(!listaReproduccion.empty())
        {
            // La quitamos de la lista
            cancion actual = listaReproduccion.front();
            listaReproduccion.pop_front();

            // Anulamos su iterador
            registroCanciones[actual].posLista = listaReproduccion.end();

            // Restamos su tiempo del total
            tiempoListaReproduccion -= registroCanciones[actual].duracion;

            // Registramos la cancion en el historial
            // Si la cancion ya esta en el historial
            if(registroCanciones[actual].posHistorial != historialReproduccion.end()){
                // La borramos de su posicion anterior
                historialReproduccion.erase(registroCanciones[actual].posHistorial);
            }
            // La colocamos como la mas reciente
            historialReproduccion.push_front(actual);
            // Actualizamos su iterador en el registro
            registroCanciones[actual].posHistorial = historialReproduccion.begin();
        }
    }

    int totalTime() const {
        return tiempoListaReproduccion;
    }

    list<cancion> recent(int N) const{
        auto ultimaCancionPedida = historialReproduccion.begin();
        int i = 0;
        while(ultimaCancionPedida != historialReproduccion.end() && i != N){
            ++i;
            ++ultimaCancionPedida;
        }
        return list<cancion>(historialReproduccion.begin(), ultimaCancionPedida);
    }

    void deleteSong(cancion titulo){
        // Buscamos la cancion
        auto itCancion = registroCanciones.find(titulo);
        if(itCancion != registroCanciones.end()) {
            // Si la cancion esta en la lista de reproduccion
            if(itCancion->second.posLista != listaReproduccion.end()){
                // Eliminamos la cancion de la lista de reproduccion
                listaReproduccion.erase(itCancion->second.posLista);

                // Restamos su tiempo del total
                tiempoListaReproduccion -= itCancion->second.duracion;
            }

            // Si la cancion esta en el historial de reproduccion
            if(itCancion->second.posHistorial != historialReproduccion.end()){
                // Borramos la cancion del historial
                historialReproduccion.erase(itCancion->second.posHistorial);
            }

            // La borramos del registro
            registroCanciones.erase(titulo);
        }
    }
};


bool resuelve() {
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    cancion tit; artista aut; int dur;
    iPud ipud;
    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> tit >> aut >> dur;
                ipud.addSong(tit, aut, dur);
            } else if (operacion == "addToPlaylist") {
                cin >> tit;
                ipud.addToPlayList(tit);
            } else if (operacion == "current") {
                tit = ipud.current(); // aunque no se hace nada, puede producir error
            } else if (operacion == "play") {
                try {
                    string tocando = ipud.current(); // para saber si la lista es vacía
                    ipud.play();
                    cout << "Sonando " << tocando << '\n';
                } catch (invalid_argument e) {
                    cout << "No hay canciones en la lista\n";
                }
            } else if (operacion == "totalTime") {
                cout << "Tiempo total " << ipud.totalTime() << '\n';
            } else if (operacion == "recent") {
                int N;
                cin >> N;
                auto lista = ipud.recent(N);
                if (lista.empty())
                    cout << "No hay canciones recientes\n";
                else {
                    cout << "Las " << lista.size() << " mas recientes\n";
                    for (auto const& s : lista)
                        cout << "    " << s << '\n';
                }
            } else if (operacion == "deleteSong") {
                cin >> tit;
                ipud.deleteSong(tit);
            } else { // operacion desconocida
                assert(false);
            }
        } catch (invalid_argument e) {
            cout << "ERROR " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main(){
    #ifndef DOMJUDGE
    ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while(resuelve()) { }

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}
