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
  for (Empleado* empleado: empleados){
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
    empleados.push_back(new EmpleadoPermanente(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado));
    cout << "\nEmpleado contratado con éxito." << endl;
  }

  if(tipoEmpleado == "temporal"){
    empleados.push_back(new EmpleadoTemporal(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado));
    cout << "\nEmpleado contratado con éxito." << endl;
  }
}

void Empresa::agregarEmpleado(Empleado* unEmpleado){
  empleados.push_back(unEmpleado);
}


void Empresa::despedirEmpleado(string idEmpleado){
  auto it =  std::find(empleados.begin(), empleados.end(), idEmpleado);
  
  if(it != empleados.end()){
    empleados.erase(it);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
  else{
    cout << "\nNo existe empleado con esa id." << endl;
  }
}

vector<EmpleadoTemporal*> Empresa::getEmpleadosTemporales(){
  for(Empleado* empleado: empleados){
    if(empleado->getTipoEmpleado() == "temporal"){
      empleadosTemporales.push_back(empleado);
    }
  }

  return empleadosTemporales;
}

vector<EmpleadoPermanente*> Empresa::getEmpleadosPermanentes(){
  for(Empleado* empleado: empleados){
    if(empleado->getTipoEmpleado() == "permanente"){
      empleadosPermanentes.push_back(empleado);
    }
  }

  return empleadosPermanentes;
}

void Empresa::informeGeneral(){
  cout<<"Cantidad total de empleados: " << empleados.size() << endl;
  cout<<"Cantidad de empleados permanentes: " << empleadosPermanentes.size() << endl;
  cout<<"Cantidad de empleados temporales: " << empleadosTemporales.size() << endl;
  
}