#include "EmpleadoTemporal.h"
#include <iostream>
  
EmpleadoTemporal::EmpleadoTemporal(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado) : Persona(nombrePersona, documentoPersona, edadPersona), Empleado(idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado){
}

EmpleadoTemporal::~EmpleadoTemporal(){
}

float EmpleadoTemporal::calcularPago(){
  float total = horasTrabajadas*valorHora;
  return total;
}

int EmpleadoTemporal::getHorasTrabajadas(){
  return horasTrabajadas;
}

float EmpleadoTemporal::getValorHora(){
  return valorHora;
}

void EmpleadoTemporal::setHorasTrabajadas(int horasTrabajadas){
  this->horasTrabajadas = horasTrabajadas;
}

void  EmpleadoTemporal::setValorHora(float valorHora){
  this->valorHora = valorHora;
}

