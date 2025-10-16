// Adrián Isasi Martínez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <algorithm>

int calculaSiguiente(int dato){
    int ac = 0;
    while(dato != 0){
        ac += (dato%10) * (dato%10);
        dato /= 10;
    }
    return ac;
}

// función que resuelve el problema
int resolver(std::set<int>& outRet) {
    int sig = *outRet.begin();
    bool ciclo = false;
    while(sig != 1 && !ciclo)
    {
        // Para imprimir exactamente la secuencia en el orden que se genera debo hacer esto
        //      Sino, la clase set ordena los valores y se pierde el orden.
        std::cout << sig << ' '; 
        
        sig = calculaSiguiente(sig);
        
        // log outRet.size()
        ciclo = std::binary_search(outRet.begin(), outRet.end(), sig);

        // outRet.size()?
        outRet.insert(sig);
    }
    std::cout << sig << ' ';
    return sig == 1;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int dato;
    std::set<int> ret;
    std::cin >> dato;
    ret.insert(dato);
    
    if (! std::cin)
        return false;
    
    std::cout << resolver(ret) << '\n';
    
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