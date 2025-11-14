#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

using Diccionario = std::map<std::string, int>;


void leerDiccionario(Diccionario& diccionario){
    char c;
    string clave;
    int valor;
    cin.get(c);
    while (c != '\n'){
        cin.unget();
        cin >> clave >> valor;
        diccionario[clave] = valor;
        cin.get(c);
    }
}

void resuelve(const Diccionario& antiguo, const Diccionario& nuevo, std::vector<std::string>& outAnyadidos, std::vector<std::string>& outQuitados, std::vector<std::string>& outModificados){
    
    auto antiguoIt = antiguo.begin();
    auto nuevoIt = nuevo.begin();

    while(antiguoIt != antiguo.end() && nuevoIt != nuevo.end()){
        if(antiguoIt->first == nuevoIt->first){
            if(antiguoIt->second != nuevoIt->second) outModificados.push_back(antiguoIt->first);
            ++antiguoIt;
            ++nuevoIt;
        }
        else if(antiguoIt->first < nuevoIt->first){
            outQuitados.push_back(antiguoIt->first);
            ++antiguoIt;
        }
        else{
            outAnyadidos.push_back(nuevoIt->first);
            ++nuevoIt;
        }
    }

    while(antiguoIt != antiguo.end()){
        outQuitados.push_back(antiguoIt->first);
        ++antiguoIt;
    }

    while(nuevoIt != nuevo.end()){
        outAnyadidos.push_back(nuevoIt->first);
        ++nuevoIt;
    }
}

void resuelveCaso(){
    Diccionario antiguo;
    Diccionario nuevo;
    std::vector<std::string> anyadidos;
    std::vector<std::string> quitados;
    std::vector<std::string> modificados;
    
    leerDiccionario(antiguo);
    leerDiccionario(nuevo);
    resuelve(antiguo, nuevo, anyadidos, quitados, modificados);

    if(anyadidos.empty() && quitados.empty() && modificados.empty()) std::cout << "Sin cambios\n";
    else{
        if(!anyadidos.empty()){
            std::cout << "+ ";
            for(std::string& s : anyadidos) std::cout << s << ' ';
            std::cout << '\n';
        }
        if(!quitados.empty()){
            std::cout << "- ";
            for(std::string& s : quitados) std::cout << s << ' ';
            std::cout << '\n';
        }
        if(!modificados.empty()){
            std::cout << "* ";
            for(std::string& s : modificados) std::cout << s << ' ';
            std::cout << '\n';
        }
    }
    std::cout << "---\n";
}


int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    int numCasos; char c;
    cin >> numCasos;
    cin.get(c);
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif

    return 0;
}
