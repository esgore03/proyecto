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

//Función cuyo fin es crear objetos iniciales para las pruebas. Esta función no haría parte del programa final, solo es para probar el funcionamiento de este.
void crearObjetosPrueba(Empresa& pericardilla){
    string nombresPersonas[4] = {"Ivan", "Angelica", "Dylan", "Jhorman"};
    string documentosPersonas[4] = {"202330197", "1923301969", "102330196", "20236969"};
    string departamentosEmpleados[4] = {"limpieza", "logistica", "cocina", "logistica"};
    string puestosEmpleados[4] = {"aseador", "analista", "mesero", "repartidor"};
    string tiposEmpleados[4] = {"permanente", "permanente", "temporal", "temporal"};
    string idsEmpleados[4] = {"125244", "696969", "666666", "131313"};
    int edadesPersonas[4] = {19, 40, 18, 18};
    

    for(int i = 0; i < sizeof(nombresPersonas); i++){
        if(tiposEmpleados[i] == "permanente"){
          pericardilla.agregarEmpleadoPermanente(new EmpleadoPermanente(nombresPersonas[i], documentosPersonas[i], edadesPersonas[i], idsEmpleados[i], departamentosEmpleados[i], puestosEmpleados[i], tiposEmpleados[i]));  
        }
        if(tiposEmpleados[i] == "temporal"){
          pericardilla.agregarEmpleadoTemporal(new EmpleadoTemporal(nombresPersonas[i], documentosPersonas[i], edadesPersonas[i], idsEmpleados[i], departamentosEmpleados[i], puestosEmpleados[i], tiposEmpleados[i]));  
        }
    }
}

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
    while (opcionMenuPrincipal != "4");

}

int main() {
    Empresa pericardilla("Pericardilla");

    crearObjetosPrueba(pericardilla);

}
