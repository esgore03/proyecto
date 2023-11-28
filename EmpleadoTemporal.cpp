#include "EmpleadoTemporal.h"
#include <iostream>
  
EmpleadoTemporal::EmpleadoTemporal(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado) : Persona(nombrePersona, documentoPersona, edadPersona), Empleado(idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado){
}

EmpleadoTemporal::~EmpleadoTemporal(){
}

//Método calcularPago().
float EmpleadoTemporal::calcularPago(){
  return (horasTrabajadas*valorHora);
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

