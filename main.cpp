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

void menuInicial(Empresa Pericardilla){
    string opcionMenuPrincipal = "0";
    do {
    cout << "Bienvenido al sistema de gestión Pericardillense\n";
    cout << "\nQué desea hacer?" << endl;
    cout << "\n1. Contratar un nuevo empleado." << endl;
    cout << "\n2. Despedir un empleado." << endl;
    cout << "\n3. Informe general" << endl;  
    cout << "\n4. Salir." << endl;
    cin >> opcionMenuPrincipal;  
    } 
    while (opcionMenuPrincipal != "4");
    if (opcionMenuPrincipal == "1"){
        Pericardilla.contratarEmpleado();
    }
    if (opcionMenuPrincipal == "2"){
        string idEmpleadoDespedir;
        cout << "Ingrese el número de id del empleado que desea despedir: ";
        cin >> idEmpleadoDespedir;
        Pericardilla.despedirEmpleado(idEmpleadoDespedir);
    }
    if (opcionMenuPrincipal == "3"){
        Pericardilla.informeGeneral();
    }
    if (opcionMenuPrincipal == "4"){
        cout << "Gracias por usar el sistema de gestión Pericardillense."<<endl;
    }
}

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
