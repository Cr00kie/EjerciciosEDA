// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std::string_literals;

class Horas{
    int h, m, s;

    public:
    Horas():h(0),m(0),s(0){}
    Horas(int h, int m, int s) {
        if(h < 0 || h > 23)
            throw "Error leyendo hora"s;
        this->h = h;

        if(m < 0 || m > 59)
            throw "Error leyendo minutos"s;
        this->m = m;

        if(s < 0 || s > 59)
            throw "Error leyendo segundos"s;
        this->s = s;
    }

    bool operator < (const Horas& otro) const{
        unsigned int segTotales1 = h*3600 + m*60 + s;
        unsigned int segTotales2 = otro.h*3600 + otro.m*60 + otro.s;
        return segTotales1 < segTotales2;
    }
    friend std::ostream& operator << (std::ostream& os, const Horas& hor){
        os << std::setfill('0') << std::setw(2) << hor.h << ":" 
           << std::setfill('0') << std::setw(2) << hor.m << ":" 
           << std::setfill('0') << std::setw(2) << hor.s;
        return os;
    }
    friend std::istream& operator >> (std::istream& is, Horas& hor){
        std::string input;
        is >> input;
        hor.h = std::stoi(input.substr(0, 2));
        hor.m = std::stoi(input.substr(3, 2));
        hor.s = std::stoi(input.substr(6, 2));

        if(hor.h < 0 || hor.h > 23)
            throw "Error leyendo hora"s;
        if(hor.m < 0 || hor.m > 59)
            throw "Error leyendo minutos"s;
        if(hor.s < 0 || hor.s > 59)
            throw "Error leyendo segundos"s;

        return is;
    }
};


// función que resuelve el problema
bool resolver(const std::vector<Horas>& trenes, Horas horPedida, Horas& horRet) {
    
    auto it = std::lower_bound(trenes.begin(), trenes.end(), horPedida);
    
    horRet = *it;
    
    return it != trenes.end();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTrenes, nHoras;
    std::cin >> nTrenes >> nHoras;
 
    if (nTrenes == 0 && nHoras == 0)
        return false;

    std::vector<Horas> horTrenes(nTrenes);
    
    // Se garantizan ser correctas
    for(Horas& h : horTrenes) std::cin >> h;

    for(int i = 0; i < nHoras; ++i) {
        try{
            Horas horPedida;
            Horas sol;
            std::cin >> horPedida;
            if(resolver(horTrenes, horPedida, sol)){
                std::cout << sol;
            }
            else {
                std::cout << "NO";
            }
            std::cout << '\n';
        }
        catch (std::string e){
            std::cout << "ERROR\n";
        }
    }
    
    return true;
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    while (resuelveCaso())
    {
        std::cout << "---\n";
    }
     

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}
