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
  //vector<Empleado*> empleados;
  string nombreEmpresa;
  string idEmpresa;

public:
  Empresa(string nombreEmpresa);
  //vector<Empleado*> getEmpleados();
  vector<EmpleadoPermanente*> getEmpleadosPermanentes();
  vector<EmpleadoTemporal*> getEmpleadosTemporales();
  void agregarEmpleadoPermanente(EmpleadoPermanente* unEmpleadoPermanente);
  void agregarEmpleadoTemporal(EmpleadoTemporal* unEmpleadoTemporal);
  //void agregarEmpleado(Empleado* unEmpleado);
  string getNombreEmpresa();
  void pagarEmpleados();
  void contratarEmpleado();
  void despedirEmpleado(string idEmpleado);
  void informeGeneral();
};

#else
class Empresa;
#endif