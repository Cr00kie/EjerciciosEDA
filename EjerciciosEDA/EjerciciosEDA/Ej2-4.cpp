// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


bool comprobarDispersion(const std::vector<int>& datos, int nDispersion, int ini, int fin) {
    int m = (ini+fin)/2;

    if(ini == fin-1){
        return true;
    }

    if(comprobarDispersion(datos, nDispersion, ini, m)
        && comprobarDispersion(datos, nDispersion, m, fin)){
            int dif = datos[ini] - datos[fin-1];
            int difAbs = dif > 0 ? dif : -dif;
            return difAbs >= nDispersion;
    }

    return false;
}

// función auxiliar
bool comprobarDispersion(const std::vector<int>& datos, int nDispersion) {
    return comprobarDispersion(datos, nDispersion, 0, datos.size());
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nCasos, nDispersion;
    std::cin >> nCasos >> nDispersion;
    std::vector<int> datos(nCasos);
    
    if (! std::cin)
        return false;
    
    for(int i = 0; i < nCasos; ++i){
        std::cin >> datos[i];
    }
    
    std::cout << (comprobarDispersion(datos, nDispersion)?"SI":"NO") << std::endl;
    
    
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