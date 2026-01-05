// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;


class Fecha {
    int _dia, _mes, _anio;

public:
    Fecha(int d = 0, int m = 0, int a = 0) : _dia(d), _mes(m), _anio(a) {}
    int dia() const { return _dia; }
    int mes() const { return _mes; }
    int anio() const { return _anio; }
    bool operator<(Fecha const& other) const {
        return _anio < other._anio ||
               (_anio == other._anio && _mes < other._mes) ||
               (_anio == other._anio && _mes == other._mes && _dia < other._dia);
    }
};

inline std::istream& operator>>(std::istream & entrada, Fecha & h) {
    int d,m,a; char c;
    std::cin >> d >> c >> m >> c >> a;
    h = Fecha(d, m, a);
    return entrada;
}

inline std::ostream& operator<<(std::ostream & salida, Fecha const& f) {
    salida << std::setfill('0') << std::setw(2) << f.dia() << '/';
    salida << std::setfill('0') << std::setw(2) << f.mes() << '/';
    salida << std::setfill('0') << std::setw(2) << f.anio();
    return salida;
}

bool operator< (std::pair<Fecha, int> unidad1, std::pair<Fecha, int> unidad2){
    return unidad1.first < unidad2.first;
}

using Codigo = string;
using Cliente = string;

class Tienda {
private:
struct InfoProducto{
    std::map<Fecha, int> unidades;
    int unidadesTotales;
    std::queue<Cliente> interesados;
};

std::unordered_map<Codigo, InfoProducto> almacen;

public:
    // Complejidad: O(min(almacen[cod].interesados.size(), cant) + log almacen[cod].unidades.size())
    vector<Cliente> adquirir(Codigo const& cod, Fecha const& f, int cant) {
        // O(min(almacen[cod].interesados.size(), cant))
        // Si hay clientes en cola de espera, les servimos el producto (guardamos los clientes a los que vamos sirviendo)
        std::vector<Cliente> clientesServidos;
        while(!almacen[cod].interesados.empty() && cant > 0){
            // Reducimos la cantidad de producto disponible
            cant--;
            // Quitamos el cliente servido de la cola de espera
            clientesServidos.push_back(almacen[cod].interesados.front());
            almacen[cod].interesados.pop();
        }

        // O(log almacen[cod].unidades.size())
        // Si hay producto restante
        if(cant > 0){
            // Intentamos insertar el producto entre las unidades disponibles
            auto insertResult = almacen[cod].unidades.insert({f, cant});
            // Si ya había unidades con esa fecha, sumamos la cantidad de las adquiridas a las ya existentes
            if(!insertResult.second){
                insertResult.first->second += cant;
            }
            // Aniadimos al registro de unidades totales las unidades aniadidas
            almacen[cod].unidadesTotales += cant;
        }

        return clientesServidos;
    }

    // Complejidad: O(1)
    pair<bool,Fecha> vender(Codigo const& cod, Cliente const& cli) {
        std::pair<bool, Fecha> ret;
        // Si hay unidades disponibles O(1)
        if(almacen[cod].unidadesTotales > 0){
            // Cogemos el producto con la fecha menor (el primero)
            auto itProductoAVender = almacen[cod].unidades.begin();

            // Establecemos los datos del producto vendido
            ret.first = true;
            ret.second = itProductoAVender->first;

            // Reducimos la cantidad del producto vendido con esa fecha
            itProductoAVender->second--;
            // Si ya no quedan unidades con esta fecha, se borra la instancia
            if(itProductoAVender->second <= 0){
                almacen[cod].unidades.erase(itProductoAVender);
            }

            // Quitamos una unidad del registro de unidades totales
            almacen[cod].unidadesTotales--;
        }
        // Si no hay unidades disponibles O(1)
        else{
            // Establecemos que no hay unidades disponibles
            ret.first = false;

            // Aniadimos el cliente a la lista de espera
            almacen[cod].interesados.push(cli);
        }

        return ret;
    }

    // Complejidad: O(1)
    int cuantos(Codigo const& cod) const {
        auto itProducto = almacen.find(cod);
        if(itProducto == almacen.end()) return 0;

        return itProducto->second.unidadesTotales;
    }

    // Complejidad: O(1)
    bool hay_esperando(Codigo const& cod) const {
        auto itProducto = almacen.find(cod);
        if(itProducto == almacen.end()) return false;
        
        return !(itProducto->second.interesados.empty());
    }
};

bool resuelveCaso() {
    std::string operacion, cod, cli;
    Fecha f;
    int cant;
    std::cin >> operacion;
    if (!std::cin)
        return false;

    Tienda tienda;

    while (operacion != "FIN") {
        if (operacion == "adquirir") {
            cin >> cod >> f >> cant;
            vector<Cliente> clientes = tienda.adquirir(cod, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            for (auto c : clientes)
                cout << ' ' << c;
            cout << '\n';
        } else if (operacion == "vender") {
            cin >> cod >> cli;
            pair<bool,Fecha> venta = tienda.vender(cod, cli);
            if (venta.first) {
                cout << "VENDIDO " << venta.second << '\n';
            } else
                cout << "EN ESPERA\n";
        } else if (operacion == "cuantos") {
            cin >> cod;
            cout << tienda.cuantos(cod) << '\n';
        } else if (operacion == "hay_esperando") {
            cin >> cod;
            if (tienda.hay_esperando(cod))
                cout << "SI\n";
            else
                cout << "NO\n";
        }

        std::cin >> operacion;
    }
    std::cout << "---\n";
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