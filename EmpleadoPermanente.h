/*
Objetivo: modelar los Empleados de tiempo completo de la empresa.
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
    int horasExtra = 0;
    int horasExtraTrabajadas = 0;
    //Se coloca como salario predeterminado 10000 porque si se coloca 1160000 que es el salario mínimo legal vigente actual, se imprime en notación científica.
    float salarioBasico = 10000;
    float valorHora = 5000;
  
  public:
    EmpleadoPermanente(string nombrePersona, string documentoPersona, int edadPersona, string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado);
    virtual ~EmpleadoPermanente();
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