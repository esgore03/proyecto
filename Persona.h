/*
El objetivo que cumple esta clase es la de una superclase de
Empleado,EmpleadoTemporal y EmpleadoPermanente*/
/*
La relacion de esta clase es funcionar como clase madre de
Empleado,EmpleadoTemporal y EmpleadoPermanente*/

#ifndef PERSONA__HH
#define PERSONA__HH

#include <iostream>

using namespace std;

class Persona {
private:
  string nombrePersona;
  string documentoPersona;
  int edadPersona;

protected:
  Persona(string nombrePersona, string documentoPersona, int edadPersona);
  virtual ~Persona();
  int getEdad();
  string getDocumento();
  string getNombre();
  void setEdad(int edadPersona);
  void setDocumento(string documentoPersona);
  void setNombre(string nombrePersona);
};

#else
class Persona;
#endif