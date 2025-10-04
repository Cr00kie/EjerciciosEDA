// Adrián Isasi Martínez
// EDA-GDV33
// Complejidad O(n) porque solo se recorren los 'n' datos una vez

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
bool CompruebaCambioTemp(const std::vector<int>& datos, int nPos) {
    // Recorrido hasta la posicion 'nPos' (incluido) para encontrar la temperatura maxima de dicho rango
    int i = 1, tempMax = datos[0], nSize = datos.size();
    for(; i <= nPos; i++){
        if(datos[i] > tempMax) tempMax = datos[i];
    }

    // Busqueda desde 'nPos' hasta el fin de datos de una temperatura menor que 'tempMax'
    while(i < nSize && datos[i] > tempMax) i++;

    return i >= nSize;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nValores, nPos;
    std::cin >> nValores >> nPos;
    std::vector<int> datos(nValores);
    for(int i = 0; i < nValores; i++){
        std::cin >> datos[i];
    }

    bool bHayCambioTemp = CompruebaCambioTemp(datos, nPos);
    
    // escribir sol
    if(bHayCambioTemp){
        std::cout << "SI" << std::endl;
    }
    else{
        std::cout << "NO" << std::endl;
    }
    
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
    #ifndef DOMJUDGE
     std::ifstream in("datos.txt");
     auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
     #endif 
    
    
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    
    // Para restablecer entrada. Comentar para acepta el reto
     #ifndef DOMJUDGE // para dejar todo como estaba al principio
     std::cin.rdbuf(cinbuf);
     system("PAUSE");
     #endif
    
    return 0;
}