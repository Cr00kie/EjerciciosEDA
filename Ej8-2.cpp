// Adrian Isasi Martinez
// EDA-GDV33

#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <set>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <fstream>
using namespace std;

struct fecha{
   int dia, hora, minuto;
   fecha(int d, int h, int m) : dia(d), hora(h), minuto(m){}
};
bool operator< (const fecha& f1, const fecha& f2) {
   if(f1.dia < f2.dia) return true;
   else if(f1.dia > f2.dia) return false;
   else if(f1.hora < f2.hora) return true;
   else if(f1.hora > f2.hora) return false;
   else if(f1.minuto < f2.minuto) return true;
   else return false;
} 

ostream& operator<< (ostream& os, const fecha& obj){
   return os << setfill('0') << setw(2) << obj.hora << ':' << setfill('0') << setw(2) << obj.minuto;
}

using medico = string;
using paciente = string;
using dia = int;
using cita = pair<fecha, paciente>;
bool operator< (const cita& c1, const cita& c2){
   return c1.first < c2.first;
}

class Consultorio{
   unordered_map<medico, set<cita>> consulta;
   unordered_map<medico, map<dia, set<cita>::iterator>> comienzoDias;

   public:
   void nuevoMedico(medico m){
      consulta[m];
   }

   void pideConsulta(const paciente& p, const medico& m, fecha f){
      auto pMedico = consulta.find(m);
      if(pMedico == consulta.end()) throw invalid_argument("Medico no existente");

      auto insertInfo = pMedico->second.insert({f, p});
      if(!insertInfo.second) throw invalid_argument("Fecha ocupada");

      auto findIt = comienzoDias[m].find(f.dia);
      if(findIt == comienzoDias[m].end() || f < comienzoDias[m][f.dia]->first){
         comienzoDias[m][f.dia] = insertInfo.first;
      }
   }

   paciente siguientePaciente(medico m){
      auto pMedico = consulta.find(m);
      if(pMedico == consulta.end()) throw invalid_argument("Medico no existente");

      if(pMedico->second.size() == 0) throw invalid_argument("No hay pacientes");

      return pMedico->second.begin()->second;
   }

   void atiendeConsulta(medico m){
      auto pMedico = consulta.find(m);
      if(pMedico == consulta.end()) throw invalid_argument("Medico no existente");

      if(pMedico->second.size() == 0) throw invalid_argument("No hay pacientes");

      int dia = pMedico->second.begin()->first.dia;
      auto sigDia = pMedico->second.erase(pMedico->second.begin());
      if(sigDia == pMedico->second.end() || sigDia->first.dia != dia)
         comienzoDias[m].erase(dia); 
      else
         comienzoDias[m][dia] = sigDia;
      
   }

   set<cita> listaPacientes(medico m, fecha f){
      auto pMedico = consulta.find(m);
      if(pMedico == consulta.end()) throw invalid_argument("Medico no existente");

      // Si ese dia no tiene nada devolvemos un set vacio
      auto pDia = comienzoDias[m].find(f.dia);
      if(pDia == comienzoDias[m].end())
      {
         return {};
      }

      // Buscamos el fin del dia
      auto findFinIt = comienzoDias[m].upper_bound(f.dia);
      // Si no lo encontramos ponemos todas las citas restantes
      auto finDelDia = findFinIt == comienzoDias[m].end() ? pMedico->second.end() : findFinIt->second;

      // PRUEBA PORQUE NO ENTIENDO PORQUE DA RUN ERROR
      if(pDia->second == finDelDia){
         return {};
      }
      // Creamos el set recorriendo las citas de ese dia solo
      return set<cita>(pDia->second, finDelDia);
   }
};

int casos = 0;
bool resuelve() {
   
   int N;
   cin >> N;
   if (!cin) return false;
   
   string inst; medico med; paciente pac; int d, h, m; char c;
   Consultorio con;
   
   for (int i = 0; i < N; ++i) {
      try {
         cin >> inst;
         if (inst == "nuevoMedico") {
            cin >> med;
            con.nuevoMedico(med);
         } else if (inst == "pideConsulta") {
            cin >> pac >> med >> d >> h >> c >> m;
            con.pideConsulta(pac, med, fecha(d,h,m));
         } else if (inst == "siguientePaciente") {
            cin >> med;
            pac = con.siguientePaciente(med);
            cout << "Siguiente paciente doctor " << med << '\n';
            cout << pac << '\n';
         } else if (inst == "atiendeConsulta") {
            cin >> med;
            con.atiendeConsulta(med);
         } else if (inst == "listaPacientes") {
            cin >> med >> d;
            auto vec = con.listaPacientes(med, fecha(d,0,0));
            cout << "Doctor " << med << " dia " << d << '\n';
            for (auto p : vec) {
               cout << p.second << ' ' << p.first << '\n';
            }
         } else
            assert(false);
      } catch (invalid_argument e) { cout << e.what() << '\n'; }
   }
   cout << "---\n";
   
   return true;
}

int main() {
   // ajuste para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelve());
    
    // restablecimiento de cin
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("pause");
#endif
    return 0;
}
