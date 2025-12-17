// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;



// función que resuelve el problema
void resolver(const vector<vector<int>>& beneficios, const vector<vector<bool>>& consentimientos,
            vector<int>& sol, int dineroActual, int n, int k,
            vector<bool>& artistasColocados, int& dineroMax, const vector<int>& maximoDesde){
    // Por cada candidato a ocupar la siguiente posicion en la solucion (la lista de cantantes del concierto)
    for(int artista = 0; artista < beneficios.size(); artista++){
        // Actualizamos los datos de la solucion
        sol[k] = artista;
        // std::cout << "Profundidad: " << k << ", artistas colocados: ";
        // for(int a : sol) std::cout << a << ", ";
        // std::cout << "Beneficios calculados actuales: " << dineroActual << ", Solucion optimista esperada: " << dineroActual + maximoDesde[k] << '\n';

        // Comprobamos que la lista de artistas es valida con el nuevo artista
        if (artistasColocados[artista] == false // Comprobamos que el artista no esta ya colocado
            && (k == 0 || consentimientos[artista][sol[k-1]]) // Comprobamos que al artista no le importa tocar despues del anterior artista colocado
            && dineroActual + maximoDesde[k] > dineroMax // Comprobamos que en el caso mas optimista todavia pudiesemos conseguir superar el maximo (Poda del arbol de exploracion para mas eficiencia)
        ){
            // Actualizamos el dinero conseguido hasta ahora
            dineroActual += beneficios[artista][k];

            // std::cout << "Solucion valida\n";
           // Miramos is estamos ante una solucion
            if (
                k == n-1 && // Una respuesta es solucion si todos los artistas se han colocado (se ha llegado a una hoja)
                dineroActual > dineroMax // Es solucion si la solucion es mejor que la que teniamos anteriormente
            ) {
                dineroMax = dineroActual; // Actualizamos la mejor solucion hasta ahora
                // std::cout << "Dinero maximo posible actualizado: " << dineroMax << '\n';
            }
            
            // Si no era solucion continuamos la exploracion hacia abajo
            else if (k < n-1){
                // Marcar que hemos colocado el artista
                artistasColocados[artista] = true;

                // Seguimos explorando las posibles soluciones
                resolver(beneficios, consentimientos, sol, dineroActual, n, k+1, artistasColocados, dineroMax, maximoDesde);
                
                // Desmarcar que hemos colocado el artista
                artistasColocados[artista] = false;
            }

            // Quitamos el dinero actual que habiamos añadido (sino afectara al calculo del resto de candidatos)
            dineroActual -= beneficios[artista][k];
        }
        else{
            // std::cout << "Solucion invalida, ";
            // if(dineroActual + maximoDesde[k] <= dineroMax) std::cout << "SOLUCION OPTIMISTA NO SUFICIENTE, ARBOL PODADO\n";
            // if(artistasColocados[artista] != false) std::cout << "ARTISTA REPETIDO\n";
            // if(k != 0 && !consentimientos[artista][sol[k-1]]) std::cout << "ARTISTA NO CONSIENTE TOCAR EN ESA POSICION\n";
        }
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    vector<vector<int>> beneficios(n,vector<int>(n));
    vector<vector<bool>> consentimientos(n,vector<bool>(n));
    for (int i = 0; i < n ; ++i)
        for (int j = 0; j < n; ++j)
            cin >> beneficios[i][j];

    for (int i = 0; i < n ; ++i)
        for (int j = 0; j < n; ++j) {
            int b;
            cin >> b;
            consentimientos[i][j] = b;
        }

    int solucion = -1; // El dinero maximo que se puede conseguir (se inicializa a -1 para que sea inferior a cualquier solucion y para comprobar si existe o no una solucion valida)
    vector<int> listaArtistas(beneficios.size(), -1);
    vector<bool> artistasColocados(beneficios.size(), 0);

    // Calculamos el maximo dinero que se puede conseguir a partir de una posicion para podar el arbol de exploracion (vamos cogiendo el maximo y le sumamos el maximo anterior)
    vector<int> maximoDesde(beneficios.size(), 0);
    for(int j = beneficios[0].size()-1; j >= 0; j--)
        for(int i = beneficios.size()-1; i >= 0; i--){
            int maxAnterior = j == beneficios[0].size()-1 ? 0 : maximoDesde[j+1];
            if(beneficios[i][j] + maxAnterior > maximoDesde[j]){
                maximoDesde[j] = beneficios[i][j] + maxAnterior;
            }
        }
    
    resolver(
        beneficios, // Datos de beneficios por artista
        consentimientos, // Datos de consentimientos de cada artista
        listaArtistas, // Creamos vector donde rellenar la solucion
        0, // Valor inicial del dinero actual es 0
        beneficios.size(), // Profundidad del arbol de exploracion es el numero de artistas q van a tocar
        0, // Profundidad inicial es 0
        artistasColocados, // Inicializamos mascara de artistas colocados a 0
        solucion,
        maximoDesde
    );

    // salida
    if(solucion == -1){
        std::cout << "NEGOCIA CON LOS ARTISTAS\n";
    }
    else{
        std::cout << solucion << '\n';
    }
}

//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}
