// Adrian Isasi Martinez
// EDA-GDV33


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>

// Coste O(datos.size())
bool resolver(const std::string& datos) {
    std::stack<char> aux;

    for(char c : datos){
        switch(c){
            case '[':
                aux.push(c);
                break;
            case '(':
                aux.push(c);
                break;
            case '{':
                aux.push(c);
                break;
            case ']':
                if(aux.empty() || aux.top() != '[') return false;
                aux.pop();
                break;
            case ')':
                if(aux.empty() || aux.top() != '(') return false;
                aux.pop();
                break;
            case '}':
                if(aux.empty() || aux.top() != '{') return false;
                aux.pop();
                break;
        }
    }
    
    return aux.empty();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string datos;
    std::getline(std::cin, datos);

    if (! std::cin)
        return false;
    
    std::cout << (resolver(datos) ? "SI" : "NO") << '\n';  
    
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