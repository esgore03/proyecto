/*
Objetivo: servir como superclase de EmpleadoTemporal y EmpleadoPermanente.
Relaciones: subclase de persona, clase madre de EmpleadoTemporal y EmpleadoPermanente. 
*/

#ifndef EMPLEADOTEMPORAL__HH
#define EMPLEADOTEMPORAL__HH

#include <iostream>
#include "Persona.h"
#include "Empleado.h"
using namespace std;

class EmpleadoTemporal : public Persona, public Empleado{
  private:
    float valorHora;
    int horasTrabajadas;

  public:
    EmpleadoTemporal(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado);
    virtual float calcularPago();
    float getValorHora();
    int getHorasTrabajadas();
    void setValorHora(float valorHora);
    void setHorasTrabajadas(int horasTrabajadas);
};

#else
class EmpleadoTemporal;
#endif