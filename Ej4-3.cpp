// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

bool comparaMonomios(const std::pair<int, int>& m1, int m2)
{
    return m1.second < m2;
}

class Polinomio{
    // first = coef, second = exp
    std::vector<std::pair<int, int>> monomios;

    public:
    void AddMonomio(int coef, int exp){
        if(coef == 0) return;

        if(monomios.size() == 0)
        {
            monomios.push_back(std::make_pair(coef, exp));
            return;
        }

        auto it = std::lower_bound(monomios.begin(), monomios.end(), exp, comparaMonomios);
        if((*it).second == exp){
            (*it).first += coef;
            if((*it).first == 0){
                monomios.erase(it);
            }
        }
        else{
            monomios.insert(it, std::make_pair(coef, exp));
        }
    }

    int Evalua(int x){
        int ac = 0;
        for(std::pair<int, int> mon : monomios)
        {
            double pot = std::pow(x, mon.second);
            ac += mon.first * pot;
        }
        return ac;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    Polinomio p;
    int c, e;
    std::cin >> c >> e;

    if (! std::cin)
        return false;
    
    while(c != 0 || e != 0){
        p.AddMonomio(c, e);
        std::cin >> c >> e;
    }

    int nValores;
    std::cin >> nValores;
    for(int i = 0; i < nValores; ++i){
        int n;
        std::cin >> n;
        std::cout << p.Evalua(n) << ' ';
    }
    std::cout << '\n';


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
        ;

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}