// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void EliminaImpares(std::vector<long long int>& datos) {
    int nValoresBorrados = 0;
    int nUltimaPos = datos.size()-1;
    for(int i = 0; i <= nUltimaPos - nValoresBorrados;){
        // std::cout << "Valores borrados: " << nValoresBorrados << std::endl;
        // std::cout << "i: " << i << std::endl;
        // for(int e : datos) std::cout << e << " ";
        // std::cout << "\n";
        if(datos[i] % 2){
            // Intercambiamos el dato impar con el ultimo dato indeterminado
            // En otras palabra almacenamos todos los impares al final para borrarlos luego
            long long int temp = datos[i];
            datos[i] = datos[nUltimaPos - nValoresBorrados];
            datos[nUltimaPos - nValoresBorrados] = temp;
            // Llevamos la cuenta de los que hemos enviado al final
            nValoresBorrados++;
        }
        // Si el dato es par seguimos al siguiente
        else{
            i++;
        }
    }
    datos.resize(nUltimaPos - nValoresBorrados + 1);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int nSize;
    std::cin >> nSize;
    std::vector<long long int> datos(nSize);
    for(long long int& e : datos) std::cin >> e;
    
    EliminaImpares(datos);

    // escribir sol
    // std::cout << "Vector resultante : ";
    for(long long int e : datos) std::cout << e << " ";
    std::cout << std::endl;
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