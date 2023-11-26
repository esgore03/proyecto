#include "EmpleadoTemporal.h"
  
EmpleadoTemporal::EmpleadoTemporal(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado) : Persona(nombrePersona, documentoPersona, edadPersona), Empleado(idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado){
}

float EmpleadoTemporal::pagarSalario(){
  float total = horasTrabajadas*valorHora;

  return total;
}

int EmpleadoTemporal::getHorasTrabajadas(){
  return horasTrabajadas;
}

float EmpleadoTemporal::getPagoPorHora(){
  return valorHora;
}

void EmpleadoTemporal::setHorasTrabajadas(int horasTrabajadas){
  this->horasTrabajadas = horasTrabajadas;
}

void  EmpleadoTemporal::setPagoPorHora(float pagoPorHora){
  this->valorHora = pagoPorHora;
}
