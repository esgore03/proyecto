/*
Objetivo: Modelar la empresa.
Relaciones: contiene a instancias de EmpleadosPermanentes y EmpleadosTemporales.
*/

#ifndef EMPRESA__HH
#define EMPRESA__HH

#include "Empleado.h"
#include "EmpleadoPermanente.h"
#include "EmpleadoTemporal.h"
#include <iostream>
#include <vector>

using namespace std;

class Empresa {
  private:
    vector<EmpleadoPermanente*> empleadosPermanentes;
    vector<EmpleadoTemporal*> empleadosTemporales;
    vector<Empleado*> empleados;
    string nombreEmpresa;
    string idEmpresa;
    float totalPagos;

  public:
    Empresa(string nombreEmpresa);
    vector<Empleado*> getEmpleados();
    vector<EmpleadoPermanente*> getEmpleadosPermanentes();
    vector<EmpleadoTemporal*> getEmpleadosTemporales();
    void agregarEmpleado(Empleado* unEmpleado);
    string getNombreEmpresa();
    bool verificarEmpleado(string idEmpleado);
    void informacionEmpleado(string idEmpleado);
    void calcularPagos();
    void editarEmpleado(string idEmpleado);
    void contratarEmpleado();
    void despedirEmpleado(string idEmpleado);
    void informeGeneral();
  };

#else
class Empresa;
#endif