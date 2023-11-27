#include <iostream>
#include "Empresa.h"
#include <algorithm>
using namespace std;

Empresa::Empresa(string nombreEmpresa){
  this->nombreEmpresa = nombreEmpresa;
}

string Empresa::getNombreEmpresa(){
  return nombreEmpresa;  
}

void Empresa::pagarEmpleados(){
  for (EmpleadoPermanente* empleado: empleadosPermanentes){
    empleado->pagarSalario();
  }
  for (EmpleadoTemporal* empleado: empleadosTemporales){
    empleado->pagarSalario();
  }
}

void Empresa::contratarEmpleado(){
  string nombrePersona, documentoPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado;
  int edadPersona;
  char eleccionTipoEmpleado;

  cout << "\nIngrese el nombre del empleado: ";
  cin >> nombrePersona;

  cout << "\nIngrese el documento del empleado: ";
  cin >> documentoPersona;

  cout << "\nIngrese la id del empleado: ";
  cin >> idEmpleado;

  cout << "\nIngrese el departamento del empleado: ";
  cin >> departamentoEmpleado;

  cout << "\nIngrese el puesto del empleado: ";
  cin >> puestoEmpleado;

  cout << "\n¿Que tipo de empleado es?" << endl << "1. Empleado Permanente" << endl << "2. Empleado Temporal" << endl;
  cout << "\nSu elección: ";
  cin >> eleccionTipoEmpleado;
  if(eleccionTipoEmpleado == 1){
    tipoEmpleado = "permanente";
  }
  if(eleccionTipoEmpleado == 2){
    tipoEmpleado = "temporal";
  }

  if(tipoEmpleado == "permanente"){
    empleadosPermanentes.push_back(new EmpleadoPermanente(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado));
    cout << "\nEmpleado contratado con éxito." << endl;
  }

  if(tipoEmpleado == "temporal"){
    empleadosTemporales.push_back(new EmpleadoTemporal(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado));
    cout << "\nEmpleado contratado con éxito." << endl;
  }
}

void Empresa::agregarEmpleadoPermanente(EmpleadoPermanente* unEmpleadoPermanente){
  empleadosPermanentes.push_back(unEmpleadoPermanente);
}

void Empresa::agregarEmpleadoTemporal(EmpleadoTemporal* unEmpleadoTemporal){
  empleadosTemporales.push_back(unEmpleadoTemporal);
}


void Empresa::despedirEmpleado(string idEmpleado){
  //Variables que contendrán la posición del objeto que concuerda con la id del parámetro.
  int it1 = -1;
  int it2 = -1;

  //Se busca el objeto que coincida con la id del parámetro.
  for(int i = 0; i < empleadosPermanentes.size(); i++){
    if(empleadosPermanentes[i]->getIdEmpleado() == idEmpleado){
      it1 = i;
      break;
    }
  }
  for(int i = 0; i < empleadosTemporales.size(); i++){
    if(empleadosTemporales[i]->getIdEmpleado() == idEmpleado){
      it2 = i;
      break;
    }
  }

  /*Nótese que los anteriores for nunca retornarán -1, además de que si no encuentran a un empleado con ese id dentro del respectivo vector, entonces no cambiarán el valor inicial de it1 o it2 que es -1.*/
  if(it1 != -1){
    //Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
    empleadosPermanentes.erase(empleadosPermanentes.begin() + it1);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
  else if(it2 != -1){
    empleadosTemporales.erase(empleadosTemporales.begin() + it2);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
  else{
    cout << "\nNo existe empleado con esa id." << endl;
  }
}

vector<EmpleadoTemporal*> Empresa::getEmpleadosTemporales(){
  return empleadosTemporales;
}

vector<EmpleadoPermanente*> Empresa::getEmpleadosPermanentes(){
  return empleadosPermanentes;
}

void Empresa::informeGeneral(){
  int cantTotalEmpleados = empleadosPermanentes.size() + empleadosTemporales.size();
  cout<<"Cantidad total de empleados: " << cantTotalEmpleados << endl;
  cout<<"Cantidad de empleados permanentes: " << empleadosPermanentes.size() << endl;
  cout<<"Cantidad de empleados temporales: " << empleadosTemporales.size() << endl;
}