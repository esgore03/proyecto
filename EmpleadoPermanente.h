/*
Objetivo: modelar los Empleados de tiempo completo de la empresa .
Relaciones: es subclase de Empleado y Persona.
*/

#ifndef EMPLEADOPERMANENTE__HH
#define EMPLEADOPERMANENTE__HH

#include <iostream>
#include "Empleado.h"
#include "Persona.h"

using namespace std;
 
class EmpleadoPermanente: public Persona, public Empleado{
  private:
    int horasExtra;
    float salarioBasico;
    float valorHora;
  
  public:
    EmpleadoPermanente(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado);
    virtual float calcularPago();
    int getHorasExtra();
    float getSalario();
    void setHorasExtra(int horasExtra);
    void setSalario(float salario);
    void setValorHora(float valorHora);
};

#else
class EmpleadoPermanente;
#endif