/*
Autores:
Ivan Ausecha 2328223-3743 ivan.ausecha@correounivalle.edu.co
Esteban Gomez 202330197 esteban.gomez.reyes@correounivalle.edu.co
Jhorman Gomez 202326867 gomez.jhorman@correounivalle.edu.co
Nicolas Salazar 202328060 nicolas.salazar.castillo@correounivalle.edu.co
Dylan Morales 202328330 dylan.morales@correounivalle.edu.co

Fecha de creacion: 30/10/2023
Fecha de ultima modificacion: 30/10/2023
Version: 0.9
*/
#include "EmpleadoPermanente.h"
#include "EmpleadoTemporal.h"
#include "Empresa.h"
#include "Persona.h"
#include <iostream>
using namespace std;

/*
void menuInicial() {
string opcion = "0";
cout << "Bienvenido al sistema de gestión Pericardillense\n";
cout << "Qué desea hacer?\n";
cout << "1. Registrar una empresa nueva\n";
cout << "2. Iniciar Sesión\n";
cout << "3. Salir\n";
cin >> opcion;
do {
if (opcion == "1") {
    cout << "Ingrese el nombre de la empresa que va a registrar: ";
}

if (opcion == "2") {
    cout << "Digite el nombre de Usuari:o " << endl;
}
if (opcion == "3") {
    cout << "Saliste del Sistema de Gestion Pericardillense\n Vuelve Pronto"
        << endl;
}
while (opcion != "3"){}

}
}
*/
void menuInicial(){
    do
    string opcionMenuPrincipal = "0";
    do{
    cout << "Bienvenido al sistema de gestión Pericardillense\n";
    cout << "\nQué desea hacer?" << endl;
    cout << "\n1. Registrar su empresa." << endl;
    cout << "\n2. Contratar un nuevo empleado." << endl;
    cout << "\n3. Informe empleados." << endl;
    cout << "\n4. Informe pagos." << endl;    
    }while (opcion != "5");in >> opcion;
    }
        while (opcion != "5");


int main() {
    EmpleadoPermanente empleado1(string x = "Ivan", string y = "202330197",
                            int z = 19, int w = 125244, string p = "baños",
                            string o = "aseo", string q = "permanente");
    EmpleadoPermanente empleado2(
    string x1 = "Angelica", string y1 = "1923301969", int z1 = 40,
    int w = 69696969, string p1 = "logistica",
    string o1 = "analisisEstadistico", string q1 = "permanente");
    EmpleadoTemporal empleado3(string x2 = "Dylan", string y2 = "102330196",
                            int z2 = 18, int w = 6666666, string p2 = "cocina",
                            string o2 = "mesero", string q2 = "temporal");
    EmpleadoTemporal empleado4(string x3 = "Jhorman", string y3 = "20236969",
                            int z3 = 18, int w = 131313,
                            string p3 = "logistica", string o3 = "cdo",
                            string q3 = "temporal");

    Empresa pericardilla("Pericardilla");
    pericardilla.agregarEmpleado(empleado1);
    pericardilla.agregarEmpleado(empleado2);
    pericardilla.agregarEmpleado(empleado3);
    pericardilla.agregarEmpleado(empleado4);

}
