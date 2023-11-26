/*
Objetivo: servir como superclase de EmpleadoTemporal y EmpleadoPermanente.
Relaciones: subclase de persona, clase madre de EmpleadoTemporal y EmpleadoPermanente. 
*/

#ifndef EMPLEADO__HH
#define EMPLEADO__HH

#include <iostream>
using namespace std;

class Empleado{
  private:
    string idEmpleado;
    string departamentoEmpleado;
    string puestoEmpleado;
    string tipoEmpleado;

  public:
    Empleado(string idEmpleado, string departamentoEmpleado, string puestoEmpleado, string tipoEmpleado);
    virtual ~Empleado();
    virtual float pagarSalario() = 0;
    string getTipoEmpleado();
    string getIdEmpleado(); 
    string getDepartamentoEmpleado();
    string getPuestoEmpleado(); 
    void setTipoEmpleado(string tipoEmpleado);
    void setIdEmpleado(string idEmpleado); 
    void setDepartamentoEmpleado(string departamentoEmpleado); 
    void setPuestoEmpleado(string puestoEmpleado); 

};

#else
class Empleado;
#endif