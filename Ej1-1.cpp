// Adrián Isasi Martínez
// EDA-GDV33
// Resolver cada vinieta individualmente tiene complejidad O(n) porque solo tiene un while


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// Funcion para calcular el signo de la diferencia entre dos valores
inline int CalculaSignoDiferencia(int datoIni, int datoFin){
    // Si es positivo 1 - 0 = 1
    // Si es negativo 0 - 1 = -1
    // Si es 0        0 - 0 = 0
    // las comparaciones y restas deberian las operaciones mas rapidas posibles
    return ((datoFin - datoIni) > 0)  -  ((datoFin - datoIni) < 0);
}

// Función que comprueba si los elementos de un vector estan en un orden estricto
bool ComprobarOrdenEstricto(std::vector<int> datos) {
    // Guardamos el tamanio del vector
    int nLength = datos.size();

    // Si el vector mide mas de uno entonces podemos comparar valores
    if(nLength > 1){
        // Calculamos si la secuencia es inicialmente creciente o decreciente
        int nSignoDiferenciaIni = CalculaSignoDiferencia(datos[0], datos[1]);

        // Si los dos primeros valores son iguales entonces NO es un orden estricto
        if(nSignoDiferenciaIni == 0)
            return false;

        // Hacemos una busqueda por el vector de un par de valores
        //      que cambie el orden inicial.
        int i = 1;
        while(i < nLength - 1 &&
              nSignoDiferenciaIni == CalculaSignoDiferencia(datos[i], datos[i+1])){
            i++;
        }

        // Si hemos terminado antes de llegar al final es que NO es un orden estricto
        return i >= nLength - 1;
    }
    // Si el vecto mide 1 ya asumimos que esta ordenado
    else {
        return true;
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    //Leemos los datos de la entrada
    int nPersonas;
    std::cin >> nPersonas;
    
    // Si leemos el valor centinela salimos
    if (nPersonas == 0)
        return false;
    
    // Rellenamos el vector con los datos dados
    std::vector<int> datos(nPersonas);
    for(int i = 0; i < nPersonas; i++){
        std::cin >> datos[i];
    }

    // Le pasamos los datos al algoritmo y recibimos su respuesta
    bool bEstaOrdenado = ComprobarOrdenEstricto(datos);
    
    // escribimos su respuesta
    if(bEstaOrdenado)
        std::cout << "DALTON" << std::endl;
    else
        std::cout << "DESCONOCIDOS" << std::endl;

    // Continuamos a por el siguiente set de datos
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
