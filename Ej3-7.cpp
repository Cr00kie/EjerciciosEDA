// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
void resolver(int n, int k, std::vector<int>& sol, bool anteriorVerde, std::vector<int>& disponibles, std::vector<int>& colocados, int& torresConstruidas) {

    for(int i = 0; i < 3; i++){
        if(disponibles[i] > 0 && (!anteriorVerde || i != 2)){ // Si anterior es verde e i==verde no entramos
            sol[k] = i;
            colocados[i]++;
            disponibles[i]--;
            
            // std::cout << "Torre: ("<<k<<"): ";
            // for(int pieza : sol){
            //     switch (pieza)
            //             {
            //             case 0: std::cout << "azul "; break;
            //             case 1: std::cout << "rojo "; break;
            //             case 2: std::cout << "verde "; break;
            //             }
            // }
            // for(int col : nColores){
            //     std::cout << '(' << col << ") ";
            // }
            // std::cout << '\n';
            if(colocados[2] <= colocados[0]){
                if(k >= n-1){
                    if(colocados[1] > colocados[2]+colocados[0]){
                        
                        torresConstruidas++;
                        for(int col : sol){
                            switch (col)
                            {
                            case 0: std::cout << "azul "; break;
                            case 1: std::cout << "rojo "; break;
                            case 2: std::cout << "verde "; break;
                            }
                        }
                        std::cout << '\n';
                    }
                }
                else{
                    bool save = anteriorVerde;
                    anteriorVerde = i == 2;
                    resolver(n, k+1, sol, anteriorVerde, disponibles, colocados, torresConstruidas);
                    anteriorVerde = save;
                }
            }

            colocados[i]--;
            disponibles[i]++;
        }
    }
    
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    std::vector<int> bloques(3);
    std::cin >> n >> bloques[0] >> bloques[1] >> bloques[2];
    
    if (n == 0)
        return false;
    
    std::vector<int> torre(n);
    torre[0] = 1;
    std::vector<int> colores {0, 1, 0};
    int torresConstruidas = 0;
    bloques[1]--;
    resolver(n, 1, torre, false, bloques, colores, torresConstruidas);
    if(!torresConstruidas) std::cout << "SIN SOLUCION\n";
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
