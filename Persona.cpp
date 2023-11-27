#include "Persona.h"
using namespace std;

Persona::Persona(string nombrePersona, string documentoPersona,
                 int edadPersona) {
  this->nombrePersona = nombrePersona;
  this->documentoPersona = documentoPersona;
  this->edadPersona = edadPersona;
}

Persona::~Persona(){
}

int Persona::getEdad() { return edadPersona; }

string Persona::getDocumento() { return documentoPersona; }

string Persona::getNombre() { return nombrePersona; }

void Persona::setEdad(int edadPersona) { this->edadPersona = edadPersona; }

void Persona::setDocumento(string documentoPersona) {
  this->documentoPersona = documentoPersona;
}

void Persona::setNombre(string nombrePersona) {
  this->nombrePersona = nombrePersona;
}