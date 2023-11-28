/*
Autores:
Ivan Ausecha 2328223-3743 ivan.ausecha@correounivalle.edu.co
Esteban Gomez 202330197 esteban.gomez.reyes@correounivalle.edu.co
Jhorman Gomez 202326867 gomez.jhorman@correounivalle.edu.co
Nicolas Salazar 202328060 nicolas.salazar.castillo@correounivalle.edu.co
Dylan Morales 202328330 dylan.morales@correounivalle.edu.co

Fecha de creacion: 30/10/2023
Fecha de ultima modificacion: 26/11/2023
Version: 0.9
*/

#include "EmpleadoPermanente.h"
#include "EmpleadoTemporal.h"
#include "Empresa.h"
#include <iostream>
using namespace std;

//Función cuyo fin es crear objetos iniciales para las pruebas. Esta función no haría parte del programa final, solo es para probar el funcionamiento de este.
void crearObjetosPrueba(Empresa& pericardilla){
    string nombresPersonas[4] = {"Ivan", "Angelica", "Dylan", "Jhorman"};
    string documentosPersonas[4] = {"202330197", "192330196", "102330196", "202369696"};
    string departamentosEmpleados[4] = {"limpieza", "logistica", "cocina", "logistica"};
    string puestosEmpleados[4] = {"aseador", "analista", "mesero", "repartidor"};
    string tiposEmpleados[4] = {"permanente", "permanente", "temporal", "temporal"};
    string idsEmpleados[4] = {"1", "2", "3", "4"};
    int edadesPersonas[4] = {19, 40, 18, 18};
    

    for(int i = 0; i < 4; i++){
        if(tiposEmpleados[i] == "permanente"){
            pericardilla.agregarEmpleado(new EmpleadoPermanente(nombresPersonas[i], documentosPersonas[i], edadesPersonas[i], idsEmpleados[i], departamentosEmpleados[i], puestosEmpleados[i], tiposEmpleados[i]));  
        }
        if(tiposEmpleados[i] == "temporal"){
            pericardilla.agregarEmpleado(new EmpleadoTemporal(nombresPersonas[i], documentosPersonas[i], edadesPersonas[i], idsEmpleados[i], departamentosEmpleados[i], puestosEmpleados[i], tiposEmpleados[i]));  
        }
    }
}

void despedirEmpleadoMenu(Empresa& empresa){
    string idEmpleadoDespedir;
    bool idValida;
    do{
        cout << "\nIngrese el número de id del empleado que desea despedir: ";
        cin >> idEmpleadoDespedir;
        if(idEmpleadoDespedir.length() < 3 or idEmpleadoDespedir.length() > 3){
            idValida = false;
            cout <<"\nIngrese un id válida." << endl;
        }
        else{
            idValida = true;
        }
        empresa.despedirEmpleado(idEmpleadoDespedir);
    }
    while(not idValida);
}

void consultarInformacionEmpleadoMenu(Empresa &empresa){
    string idEmpleado;

    cout << "\nIngrese la id del empleado a consultar: ";
    cin >> idEmpleado;
    bool existeEmpleado = empresa.verificarEmpleado(idEmpleado);
    while(not existeEmpleado){
        cout << "\nNo existe empleado con esa id." << endl;
        cout << "\nIngrese la id del empleado a consultar: ";
        cin >> idEmpleado;
        bool existeEmpleado = empresa.verificarEmpleado(idEmpleado);
    }

    empresa.informacionEmpleado(idEmpleado);
}

void editarInformacionEmpleadoMenu(Empresa& empresa){
    string idEmpleado;

    cout << "\nIngrese la id del empleado a editar: ";
    cin >> idEmpleado;
    bool existeEmpleado = empresa.verificarEmpleado(idEmpleado);
    while(not existeEmpleado){
        cout << "\nNo existe empleado con esa id." << endl;
        cout << "\nIngrese la id del empleado a editar: ";
        cin >> idEmpleado;
        bool existeEmpleado = empresa.verificarEmpleado(idEmpleado);
    }

    //empresa.editarEmpleado(idEmpleado);
}

void menuInicial(Empresa& empresa){
    int opcionMenuPrincipal;
    do {
        cout << "\nBienvenido al sistema de gestión salarial de la empresa " << empresa.getNombreEmpresa() << "." << endl;
        cout << "\nQué desea hacer?" << endl;
        cout << "\n1. Contratar un nuevo empleado." << endl;
        cout << "\n2. Despedir un empleado." << endl;
        cout << "\n3. Editar información de un empleado." << endl;
        cout << "\n4. Consultar información de un empleado." << endl;
        cout << "\n5. Informe general" << endl;  
        cout << "\n6. Salir." << endl;
        cout << "\nOpción a elegir: ";
        cin >> opcionMenuPrincipal; 
        if (opcionMenuPrincipal == 1){
            empresa.contratarEmpleado();
        }
        if (opcionMenuPrincipal == 2){
            despedirEmpleadoMenu(empresa);
        }
        if (opcionMenuPrincipal == 3){
            editarInformacionEmpleadoMenu(empresa);
        }
        if (opcionMenuPrincipal == 4){
            consultarInformacionEmpleadoMenu(empresa);
        }
        if (opcionMenuPrincipal == 5){
            empresa.informeGeneral();
        }
        if (opcionMenuPrincipal == 6){
            cout << "\nGracias por usar el sistema de gestión Pericardillense." << endl;
        }
    }
    while (opcionMenuPrincipal != 6);
}

int main() {
    Empresa pericardilla("Pericardilla");
    crearObjetosPrueba(pericardilla);
    menuInicial(pericardilla);

    return 0;
}
