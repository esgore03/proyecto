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
  auto it1 =  std::find(empleadosPermanentes.begin(), empleadosPermanentes.end(), idEmpleado);
  auto it2 = std::find(empleadosTemporales.begin(), empleadosTemporales.end(), idEmpleado);

  if(it1 != empleadosPermanentes.end()){
    empleadosPermanentes.erase(it1);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
  else if(it2 != empleadosTemporales.end()){
    empleadosTemporales.erase(it2);
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