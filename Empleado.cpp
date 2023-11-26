#include "Empleado.h"

Empleado::Empleado(string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado){
  this->idEmpleado = idEmpleado;
  this->departamentoEmpleado = departamentoEmpleado;
  this->puestoEmpleado = puestoEmpleado;
  this->tipoEmpleado = tipoEmpleado;
}

Empleado::~Empleado(){
}

string Empleado::getTipoEmpleado(){
  return tipoEmpleado;
}

string Empleado::getIdEmpleado(){
  return idEmpleado;
}

string Empleado::getDepartamentoEmpleado(){
  return departamentoEmpleado;
}

string Empleado::getPuestoEmpleado(){
  return puestoEmpleado;
}

void Empleado::setIdEmpleado(string idEmpleado){
  this->idEmpleado = idEmpleado;
}

void Empleado::setDepartamentoEmpleado(string departamentoEmpleado){
  this->departamentoEmpleado = departamentoEmpleado;
}

void Empleado::setPuestoEmpleado(string puestoEmpleado){
  this->puestoEmpleado = puestoEmpleado;
}

void Empleado::setTipoEmpleado(string tipoEmpleado){
  this->tipoEmpleado = tipoEmpleado;
}