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
    float valorHora = 5000;
    int horasTrabajadas = 0;

  public:
    EmpleadoTemporal(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado);
    virtual ~EmpleadoTemporal();
    virtual float calcularPago();
    float getValorHora();
    int getHorasTrabajadas();
    void setValorHora(float valorHora);
    void setHorasTrabajadas(int horasTrabajadas);
};

#else
class EmpleadoTemporal;
#endif