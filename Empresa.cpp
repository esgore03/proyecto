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

void Empresa::calcularPagos(){
  float pago;
  totalPagos = 0;
  cout << "\nEMPLEADOS PERMANENTES." << endl;
  for (EmpleadoPermanente* empleado: empleadosPermanentes){
    pago = empleado->calcularPago();
    totalPagos += pago;
    cout << "\nAl empleado " << empleado->getNombre() << " identificado con id de empleado: " << empleado->getIdEmpleado() << " se le debe pagar: " << pago << " persos" << endl;
  }
  cout << "\nEMPLEADOS TEMPORALES." << endl;
  for (EmpleadoTemporal* empleado: empleadosTemporales){
    pago = empleado->calcularPago();
    totalPagos += pago;
    cout << "\nAl empleado " << empleado->getNombre() << " identificado con id de empleado: " << empleado->getIdEmpleado() << " se le debe pagar: " << pago << " persos" << endl;
  }
}

void Empresa::contratarEmpleado(){
  string nombrePersona, documentoPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado;
  int edadPersona;
  char eleccionTipoEmpleado;

  cout << "\nIngrese el nombre del empleado: ";
  cin >> nombrePersona;

  /*No se agregan restricciones al documento pero perfectamente podría ser hecho siguiendo la lógica de la restricción en idEmpleado, eso queda a gusto del cliente final.*/
  cout << "\nIngrese el documento del empleado: ";
  cin >> documentoPersona;

  do{
    cout << "\nIngrese la edad del empleado: ";
    cin >> edadPersona;

    if(edadPersona < 18 and edadPersona > 100){
      cout <<"\nIngrese una edad válida." << endl;
    }
  }
  while(edadPersona < 18 and edadPersona > 100);

  //Se agrega la restricción de carácteres a 3, este número puede ser mayor o menor dependiendo del cliente.
  do{
    cout << "\nIngrese la id del empleado: ";
    cin >> idEmpleado;

    if(idEmpleado.length() < 3 and idEmpleado.length() > 3){
      cout << "\nIngrese una id de 3 carácteres." << endl;
    }
  }
  while(idEmpleado.length() < 3 and idEmpleado.length() > 3);

  cout << "\nIngrese el departamento del empleado: ";
  cin >> departamentoEmpleado;

  cout << "\nIngrese el puesto del empleado: ";
  cin >> puestoEmpleado;

  //Se agrega lógica para que se ingrese un input válido y soportado.
  do{
    cout << "\n¿Que tipo de empleado es?" << endl << "1. Empleado Permanente" << endl << "2. Empleado Temporal" << endl;
    cout << "\nSu elección: ";
    cin >> eleccionTipoEmpleado;
    if(eleccionTipoEmpleado == 1){
      tipoEmpleado = "permanente";
    }
    if(eleccionTipoEmpleado == 2){
      tipoEmpleado = "temporal";
    }
    else{
      cout << "\nPor favor ingrese 1 o 2." << endl;
    }
  }
  while(eleccionTipoEmpleado != 1 and eleccionTipoEmpleado != 2);

  if(tipoEmpleado == "permanente"){
    empleadosPermanentes.push_back(new EmpleadoPermanente(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado));
    cout << "\nEmpleado contratado con éxito." << endl;
  }

  if(tipoEmpleado == "temporal"){
    empleadosTemporales.push_back(new EmpleadoTemporal(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado));
    cout << "\nEmpleado contratado con éxito." << endl;
  }
}

/*En el programa final este método no debería ser parte de él, solo fue creado para facilitar pruebas con el programa*/
void Empresa::agregarEmpleado(Empleado* unEmpleado){
  empleados.push_back(unEmpleado);

  //Se verifica el tipoEmpleado.
  if(unEmpleado->getTipoEmpleado() == "permanente"){
    //Se intenta realizar dynamic casting, si es exitoso retorna un puntero válido, si no lo es, retorna nullptr.
    EmpleadoPermanente* empleado = dynamic_cast<EmpleadoPermanente*>(unEmpleado);
    if(empleado != nullptr){
      empleadosPermanentes.push_back(empleado);
    }
    //Teóricamente este cout nunca debería ocurrir, pero si ocurre ya se sabría que error ocurrió,
    else{
      cout << "\nAcción no exitosa." << endl;
    }
  }
  if(unEmpleado->getTipoEmpleado() == "temporal"){
    EmpleadoTemporal* empleado = dynamic_cast<EmpleadoTemporal*>(unEmpleado);
    if(empleado != nullptr){
      empleadosTemporales.push_back(empleado);
    }
    else{
      cout << "\nAcción no exitosa." << endl;
    }
  }
}

void Empresa::despedirEmpleado(string idEmpleado){
  //Variables que contendrán la posición del objeto que concuerda con la id del parámetro.
  int it1 = -1;
  int it2 = -1;
  int it3 = -1;

  //Se busca el objeto que coincida con la id del parámetro.
  for(int i = 0; i < empleados.size(); i++){
    if(empleados[i]->getIdEmpleado() == idEmpleado){
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

  for(int i = 0; i < empleadosPermanentes.size(); i++){
    if(empleadosPermanentes[i]->getIdEmpleado() == idEmpleado){
      it3 = i;
      break;
    }
  }

  /*Nótese que los anteriores for nunca retornarán -1, además de que si no encuentran a un empleado con ese id dentro del respectivo vector, entonces no cambiarán el valor inicial de it1, it2 o it3 que es -1.*/
  if(it1 != -1 and it2 != -1){
    //Antes de proceder, se debe borrar el puntero para evitar fugas.
    delete empleados[it1];
    empleados[it1] = nullptr;
    delete empleadosPermanentes[it2];
    empleadosPermanentes[it2] = nullptr;

    //Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
    empleados.erase(empleados.begin() + it1);
    empleadosPermanentes.erase(empleadosPermanentes.begin() + it2);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
  else if(it1 != -1 and it3 != -1){
    //Antes de proceder, se debe borrar el puntero para evitar fugas.
    delete empleados[it1];
    empleados[it1] = nullptr;
    delete empleadosTemporales[it3];
    empleadosTemporales[it3] = nullptr;

    //Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
    empleados.erase(empleados.begin() + it1);
    empleadosTemporales.erase(empleadosTemporales.begin() + it3);
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
  cout << "\nCantidad total de empleados: " << empleados.size() << endl;
  cout << "\nCantidad de empleados permanentes: " << empleadosPermanentes.size() << endl;
  cout << "\nCantidad de empleados temporales: " << empleadosTemporales.size() << endl;

  cout << "\nEstado financiero de cada empleado dividido por tipos:" << endl;
  calcularPagos();

  cout << "\nLo anterior dando un total de: " << totalPagos << " pesos" <<  endl;
}