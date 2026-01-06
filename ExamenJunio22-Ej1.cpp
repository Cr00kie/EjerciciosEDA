// Adrian Isasi
// EDA-GDV33

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

template <class T>
ostream& operator<<(ostream& out, const vector<T>& v){
    for (auto e : v) out << e << ' ';
    return out;
}

// - [] Dos alumnos por tarea
// - [X] Un alumno no puede tener mas de t tareas
// - [X] Maximizar la satisfaccion de los alumnos

// función que resuelve el problema
void resolver(std::vector<int>& soluc, int k, int m, int n, int t, std::vector<std::vector<int>> const& preferencias, std::vector<int>& tareasPorAlumno, int& satisfaccionActual, int& satisfaccionMax){
    for(int i = 0; i < m; i++){
        // Marcamos en la tupla solucion el alumno seleccionado para la tarea 'k'
        soluc[k] = i;

        
        // Marcamos que el alumno 'i' tiene una m'as
        tareasPorAlumno[i]++;
        
        if(tareasPorAlumno[i] <= t // Un alumno no puede tener mas de t tareas
            && (k % 2 == 0 || soluc[k] != soluc[k-1]) // No puede estar el mismo alumno dos veces en la misma tarea
        ){
            // Aniadimos la satisfaccion del alumno 'i' por hacer la tarea 'k'
            satisfaccionActual += preferencias[i][k/2];

            if(k == n-1 // Es solucion si todas las tareas han sido asignadas
            ){ 
                if(satisfaccionActual > satisfaccionMax){
                    satisfaccionMax = satisfaccionActual;
                }
            }
            else{
                resolver(soluc, k+1, m, n, t, preferencias, tareasPorAlumno, satisfaccionActual, satisfaccionMax);
            }

            // Descontamos la satisfaccion del alumno 'i' por hacer la tarea 'k'
            satisfaccionActual -= preferencias[i][k/2];
        }

        // Desmarcamos que el alumno 'i' tenga la tarea
        tareasPorAlumno[i]--;
    }

}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, a, t;
    cin >> n >> a >> t;
    if (n == 0 && a == 0 && t == 0) return false;
    vector<vector<int>> preferencias(a,vector<int>(n));
    for (int i = 0; i < a ; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> preferencias[i][j];
        }
    

    std::vector<int> soluc(n*2);
    std::vector<int> tareasPorAlumno(a);
    int satisfaccionAct = 0;
    int satisfaccionMax = -1;
    // n*2 porque hay dos alumnos por tarea (se puede pensar como que hay el doble de tareas)
    resolver(soluc, 0, a, n*2, t, preferencias, tareasPorAlumno, satisfaccionAct, satisfaccionMax);
    // Imprimir solucion
    // if(satisfaccionMax == -1) std::cout << "IMPOSIBLE\n"
    std::cout << satisfaccionMax << '\n';
    return true;
}

//#define DOMJUDGE
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
    //system("PAUSE");
#endif

    return 0;
}