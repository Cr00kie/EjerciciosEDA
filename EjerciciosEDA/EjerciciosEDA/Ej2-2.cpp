// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>


//             | 9 - num % 10                        si num es el ultimo (num/10 == 0)
// comp(num) = | o
//             | (9 - num % 10) + comp(num/10) * 10  si num no es el ultimo digito
//
// Complejidad:
//      a = 1
//      b = 10
//      k = 0
//      Por tanto: a = b^k -> O(n^0 * log n) = O(log(n))
//              == O(log n) ==
int complementario(int num) {
    if(num/10 == 0) return 9 - num;
    else return (9 - num % 10) + (complementario(num/10) * 10);
}

// ac = 0          | ac*10 + 9-num                       si num es el ultimo (num/10 == 0)
// comp(num, ac) = | o
//                 | comp(num/10, ac*10 + (9 - num%10))  si num no es el ultimo digito
//
// Complejidad:
//      a = 1
//      b = 10
//      k = 0
//      Por tanto: a = b^k -> O(n^0 * log n) = O(log(n))
//              == O(log n) ==
int complementarioInverso(int num, int ac) {
    if(num/10 == 0) return (ac * 10) + (9 - num);
    else return complementarioInverso(num/10, ac*10 + (9 - num % 10));
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int num;
    std::cin >> num;
    
    int sol1 = complementario(num);
    int sol2 = complementarioInverso(num, 0);
    // escribir sol
    std::cout << sol1 << " " << sol2 << std::endl;
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