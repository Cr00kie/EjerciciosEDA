// Adrian Isasi Martinez
// EDA-GDV33

#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

bool ordenarDeportes(const pair<string,int>& d1, const pair<string,int>& d2){
    if(d1.second > d2.second) return true;
    else if(d2.second > d1.second) return false;
    else if(d1.first < d2.first) return true;
    else return false;
}

void resolver(string const& primerDeporte, vector<pair<string,int>>& resultado){
    unordered_map<string, string> deportesApuntadosPorAlumno;
    unordered_map<string, int> alumnosPorDeporte;

    string deporte, alumno;
    deporte = primerDeporte;
    while (deporte != "_FIN_") {
        alumnosPorDeporte[deporte] = 0;
        //std::cout << "Deporte: " << deporte << '\n';
        cin >> alumno;
        while (!isupper(alumno[0]) && alumno != "_FIN_") {
            //std::cout << "Alumno: " << alumno << '\n';
            // Cogemos el deporte en el que esta apuntado
            string& deporteAlumno = deportesApuntadosPorAlumno[alumno];
            //std::cout << "\tDeporte ya apuntado: " << deporteAlumno << '\n';
            // Si no esta apuntado a ningun deporte
            if(deporteAlumno == ""){
                //std::cout << "\tApuntando alumno a nuevo deporte\n";
                // Guardamos a que deporte se ha apuntado
                deporteAlumno = deporte;
                // Aumentamos el numero de participantes del deporte
                ++alumnosPorDeporte[deporte];
            }
            // Si ya estaba apuntado a un deporte
            else{
                //std::cout << "\tAlumno ya apuntado\n";
                // Miramos si es la primera vez que aparece repetido y si el deporte es distinto
                if(deporteAlumno != "no-contar" && deporteAlumno != deporte){
                    //std::cout << "\tDescontando alumno del deporte anterior\n";
                    // Para descontarlo la primera vez restamos en el deporte en el que se habia apuntado
                    alumnosPorDeporte[deporteAlumno] = alumnosPorDeporte[deporteAlumno] - 1 < 0 ? 0 : alumnosPorDeporte[deporteAlumno]-1;
                    // Usamos su ultimo deporte como flag para marcar que debe ser ignorado
                    deporteAlumno = "no-contar";
                }

            }
            cin >> alumno;
            //std::cout << "Alumnos en " << deporte << ": " << alumnosPorDeporte[deporte] << '\n';
        }
        deporte = alumno;
    }
    resultado.resize(alumnosPorDeporte.size());
    int i = 0;
    for(auto it = alumnosPorDeporte.begin(); it != alumnosPorDeporte.end(); ++it){
        resultado[i] = {it->first, it->second};
        ++i;
    }
    std::sort(resultado.begin(), resultado.end(), ordenarDeportes);

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    string primerDeporte;
    cin >> primerDeporte;
    if (!cin) return false;
    vector<pair<string, int>> resultado;
    resolver(primerDeporte, resultado);
    for(auto it = resultado.begin(); it != resultado.end(); ++it){
        std::cout << it->first << ' ' << it->second << '\n';
    }
    cout << "---\n";
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
#endif

    return 0;
}