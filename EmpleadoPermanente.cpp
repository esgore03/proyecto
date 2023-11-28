#include "EmpleadoPermanente.h"

EmpleadoPermanente::EmpleadoPermanente(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado) : Persona(nombrePersona, documentoPersona, edadPersona), Empleado(idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado){
}

EmpleadoPermanente::~EmpleadoPermanente(){
}

//Método calcularPago().
float EmpleadoPermanente::calcularPago(){
  return (horasExtra*valorHora) + salarioBasico;
}

float EmpleadoPermanente::getSalario(){
  return salarioBasico;
}

int EmpleadoPermanente::getHorasExtra(){
  return horasExtra;
}

void EmpleadoPermanente::setHorasExtra(int horasExtra){
  this->horasExtra = horasExtra;
}

void EmpleadoPermanente::setSalario(float salario){
  this->salarioBasico = salario;
}

void EmpleadoPermanente::setValorHora(float valorHora){
  this->valorHora = valorHora;
}


