// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
// Complejidad: O(n^2)
bool anagramas(const std::string& cad1, const std::string& cad2) {
    if(cad1.size() != cad2.size()) 
        return false;

    int frecuencias[25];
    for(int& e : frecuencias) e = 0;

    for(char e : cad1) frecuencias[int(e)-97]++;
    for(char e : cad2) frecuencias[int(e)-97]--;

    for(int e : frecuencias)
        if(e) return false;
    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    std::string word1, word2;
    std::cin >> word1 >> word2;
    std::cout << (anagramas(word1,word2) ? "SI" : "NO") << std::endl;
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