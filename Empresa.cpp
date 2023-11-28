#include <iostream>
#include "Empresa.h"
#include <algorithm>
#include <cctype>
using namespace std;

Empresa::Empresa(string nombreEmpresa){
  this->nombreEmpresa = nombreEmpresa;
}

string Empresa::getNombreEmpresa(){
  return nombreEmpresa;  
}

//Método que calcula cuanto se le debe pagar a cada empleado.
void Empresa::calcularPagos(){
  float pago;
  totalPagos = 0;
  cout << "\nEMPLEADOS PERMANENTES." << endl;
  //Se recorre el vector respectivo y se aplica el método, además el atributo totalPagos acumula cada "pago".
  for (EmpleadoPermanente* empleado: empleadosPermanentes){
    pago = empleado->calcularPago();
    totalPagos += pago;
    cout << "\nAl empleado " << empleado->getNombre() << " identificado con id de empleado: " << empleado->getIdEmpleado() << " se le debe pagar: " << pago << " persos" << endl;
  }
  cout << "\nEMPLEADOS TEMPORALES." << "\nTéngase en cuenta que el calculo a continuación se basa en las horas trabajadas registradas, si estas son 0, el cálculo retornará 0." << endl;
  for (EmpleadoTemporal* empleado: empleadosTemporales){
    pago = empleado->calcularPago();
    totalPagos += pago;
    cout << "\nAl empleado " << empleado->getNombre() << " identificado con id de empleado: " << empleado->getIdEmpleado() << " se le debe pagar: " << pago << " persos" << endl;
  }
}

//Método para "contratar" un empleado.
void Empresa::contratarEmpleado(){
  string nombrePersona, documentoPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado;
  int edadPersona;
  char eleccionTipoEmpleado;
  
  bool nombrePersonaValido;
  //Ciclo do-while para verificar datos ingresados.
  do{
    cout << "\nIngrese el nombre del empleado: ";
    //getline funciona como un cin solo que lee los datos tal y como fueron ingresados, no los convierte.
    getline(cin, nombrePersona);
    /*Teniendo en cuenta lo anterior, a nombrePersona se le verifica que no se le hayan ingresado dígitos. Esto normalmente sería imposible si no fuera por getline y su peculiaridad de no convertir los datos ingresados.*/
    for(int i = 0; i < nombrePersona.length(); i++){
      //Se verifica si el carácter es dígito.
      if(isdigit(nombrePersona[i])){
        cout << "\nPor favor ingrese el nombre sin dígitos." << endl;
        nombrePersonaValido = false;
        break;
      }
    }
  }
  //Se repite el ciclo hasta que no sea válido el nombre ingresado.
  while(not nombrePersonaValido);

  //Se verifica que no hayan empleados con el mismo documento.
  bool documentoRepetido = false;
  do{
    cout << "\nIngrese el documento del empleado: ";
    cin >> documentoPersona;
    
    for(Empleado* empleado: empleados){
      if(empleado->getTipoEmpleado() == "permanente"){
        EmpleadoPermanente* empleadoPermanente = dynamic_cast<EmpleadoPermanente*>(empleado);

        if(empleadoPermanente->getDocumento() == documentoPersona){
          documentoRepetido = true;
          break;
        }
      }
      else if(empleado->getTipoEmpleado() == "temporal"){
        EmpleadoTemporal* empleadoTemporal = dynamic_cast<EmpleadoTemporal*>(empleado);

        if(empleadoTemporal->getDocumento() == documentoPersona){
          documentoRepetido = true;
          break;
        }
      }
    }
  }
  while(documentoRepetido);

  /*Se restringen ciertos inputs a la edad, primero, que esté entre 18 y 100 años, segundo, que si se ingresan carácteres, se soporten ese tipo de inputs y mediante un try se muestre el error y siga en marcha el programa.*/
  bool rangoEdadValido, edadValida;
  do{
    try{
      cout << "\nIngrese la edad del empleado: ";
      cin >> edadPersona;

      if(cin.fail()){
        throw runtime_error("Se han ingresado datos que no son numéricos.");
      }
      else{
        edadValida = true;
      }

      if(edadPersona < 18 and edadPersona > 100){
        throw out_of_range("Se ha salido del rango permitido para la edad.");
      }
      else{
        rangoEdadValido = true;
      }
    }
    //Se hace catch cuando se ingrese un carácter.
    catch(runtime_error &ingresoDeCaracter){
      cin.clear();
      cin.ignore();
      cout << "\nError: " << ingresoDeCaracter.what() << endl;
      cout << "\nPor favor ingrese una edad válida que solo contenga dígitos." << endl;
      edadValida = false;
    }
    //Se hace catch cuando esté fuera del rango.
    catch(out_of_range &edadFueraDeRango){
      cout << "\nError: " << edadFueraDeRango.what() << endl;
      cout << "\nPor favor ingrese una edad válida entre 18 y 100 años." << endl;
      rangoEdadValido = false;
    }
  }
  //Mientras que alguno de los dos booleanos sea falso (con not sería true), el ciclo se sigue ejecutando.
  while(not edadValida or not rangoEdadValido);

  bool idEmpleadoValida, idEmpleadoRepetida = false;
  //Se agrega la restricción de carácteres a 3, este número puede ser mayor o menor dependiendo del cliente.
  do{
    cout << "\nIngrese la id del empleado: ";
    cin >> idEmpleado;

    for(Empleado* empleado: empleados){
      if(empleado->getIdEmpleado() == idEmpleado){
        idEmpleadoRepetida = true;
        break;
      }
    }

    if(idEmpleado.length() < 3 and idEmpleado.length() > 3){
      idEmpleadoValida = false;
      cout << "\nIngrese una id de 3 carácteres." << endl;
    }
    else{
      idEmpleadoValida = true;
    }
  }
  while(not idEmpleadoValida or idEmpleadoRepetida);

  cout << "\nIngrese el departamento del empleado: ";
  cin >> departamentoEmpleado;

  cout << "\nIngrese el puesto del empleado: ";
  cin >> puestoEmpleado;

  bool eleccionEmpleadoValida;
  //Se agrega lógica para que se ingrese un input válido y soportado.
  do{
    cout << "\n¿Que tipo de empleado es?" << endl << "1. Empleado Permanente" << endl << "2. Empleado Temporal" << endl;
    cout << "\nSu elección: ";
    cin >> eleccionTipoEmpleado;
    if(eleccionTipoEmpleado == 1){
      tipoEmpleado = "permanente";
      eleccionEmpleadoValida = true;
    }
    else if(eleccionTipoEmpleado == 2){
      tipoEmpleado = "temporal";
      eleccionEmpleadoValida = true;
    }
    else{
      eleccionEmpleadoValida = false;
      cout << "\nPor favor ingrese 1 o 2." << endl;
    }
  }
  while(not eleccionEmpleadoValida);

  //Una vez verificado lo anterior, se crea el objeto acorde a su tipo.
  if(tipoEmpleado == "permanente"){
    EmpleadoPermanente* empleadoPermanente = new EmpleadoPermanente(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado);
    empleadosPermanentes.push_back(empleadoPermanente);

    float salarioEmpleado, valorHoraEmpleado;
    bool salarioValido, valorHoraValido;
    do{
      try{
        //Se pregunta por el salario del empleado y el valor de su hora para las horas extras.
        cout << "\nIngrese el salario que tendrá el empleado: ";
        cin >> salarioEmpleado;
        empleadoPermanente->setSalario(salarioEmpleado);

        //Se verifica que no hayan habido fallos en el cin, si los hay se hace throw del respectivo error.
        if(cin.fail()){
          throw runtime_error("Se han ingresado carácteres al input de salario.");
        }
        else{
          salarioValido = true;
        }

        cout << "\nIngrese el valor por hora que tendrá el empleado: ";
        cin >> valorHoraEmpleado;
        empleadoPermanente->setValorHora(valorHoraEmpleado);

        if(cin.fail()){
          throw runtime_error("Se han ingresado carácteres al input de valor hora.");
        }
        else{
          valorHoraValido = true;
        }
      }
      //Se define como se procesan dichos throw.
      catch(runtime_error &inputNoValido){
        cin.clear();
        cin.ignore();
        if(inputNoValido.what() == "Se han ingresado carácteres al input de salario."){       
          cout << "\nError: " << inputNoValido.what() << endl;
          cout << "\nPor favor ingrese solo dígitos." << endl;
          salarioValido = false;
        }
        else{
          cout << "\nError: " << inputNoValido.what() << endl;
          cout << "\nPor favor ingrese solo dígitos." << endl;
          valorHoraValido = false;
        }
      }
    }
    while(not salarioValido or not valorHoraValido);
    cout << "\nEmpleado contratado con éxito." << endl;
  }
  else{
    EmpleadoTemporal* empleadoTemporal = new EmpleadoTemporal(nombrePersona, documentoPersona,  edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado);
    empleadosTemporales.push_back(empleadoTemporal);

    bool valorHoraValido;
    float valorHoraEmpleado;

    do{
      try{
        cout << "\nIngrese el valor por hora que tendrá el empleado: ";
        cin >> valorHoraEmpleado;
        empleadoTemporal->setValorHora(valorHoraEmpleado);

        if(cin.fail()){
          throw runtime_error("Se han ingresado carácteres al input de valor hora.");
        }
        else{
          valorHoraValido = true;
        }
      }
      catch(runtime_error &inputNoValido){
        cin.clear();
        cin.ignore();
        cout << "\nError: " << inputNoValido.what() << endl;
        cout << "\nPor favor ingrese solo dígitos." << endl;
        valorHoraValido = false;
      }
    }
    while(not valorHoraValido);
    cout << "\nEmpleado contratado con éxito." << endl;
  }
}

/*En el programa final este método no debería ser parte de él, solo fue creado para facilitar pruebas con el programa*/
void Empresa::agregarEmpleado(Empleado* unEmpleado){
  empleados.push_back(unEmpleado);

  //Se verifica el tipoEmpleado.
  if(unEmpleado->getTipoEmpleado() == "permanente"){
    //Se intenta realizar dynamic casting, si es exitoso retorna un puntero válido, si no lo es, retorna nullptr.
    EmpleadoPermanente* empleado = dynamic_cast<EmpleadoPermanente*>(unEmpleado);
    if(empleado != nullptr){
      empleadosPermanentes.push_back(empleado);
    }
    //Teóricamente este cout nunca debería ocurrir, pero si ocurre ya se sabría que error ocurrió,
    else{
      cout << "\nAcción no exitosa." << endl;
    }
  }
  if(unEmpleado->getTipoEmpleado() == "temporal"){
    EmpleadoTemporal* empleado = dynamic_cast<EmpleadoTemporal*>(unEmpleado);
    if(empleado != nullptr){
      empleadosTemporales.push_back(empleado);
    }
    else{
      cout << "\nAcción no exitosa." << endl;
    }
  }
}

//Función que "despide" un empleado.
void Empresa::despedirEmpleado(string idEmpleado){
  //Variables que contendrán la posición del objeto que concuerda con la id del parámetro.
  int it1 = -1;
  int it2 = -1;
  int it3 = -1;

  bool existeEmpleado = verificarEmpleado(idEmpleado);

  if(existeEmpleado){
    //Se busca el objeto que coincida con la id del parámetro.
    for(int i = 0; i < empleados.size(); i++){
      if(empleados[i]->getIdEmpleado() == idEmpleado){
        it1 = i;
        break;
      }
    }

    for(int i = 0; i < empleadosTemporales.size(); i++){
      if(empleadosTemporales[i]->getIdEmpleado() == idEmpleado){
        it2 = i;
        break;
      }
    }

    for(int i = 0; i < empleadosPermanentes.size(); i++){
      if(empleadosPermanentes[i]->getIdEmpleado() == idEmpleado){
        it3 = i;
        break;
      }
    }

    /*Nótese que los anteriores for nunca retornarán -1, además de que si no encuentran a un empleado con ese id dentro del respectivo vector, entonces no cambiarán el valor inicial de it1, it2 o it3 que es -1.*/
    if(it1 != -1 and it2 != -1){
      //Antes de proceder, se debe borrar el puntero para evitar fugas.
      delete empleados[it1];
      empleados[it1] = nullptr;
      delete empleadosPermanentes[it2];
      empleadosPermanentes[it2] = nullptr;

      //Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
      empleados.erase(empleados.begin() + it1);
      empleadosPermanentes.erase(empleadosPermanentes.begin() + it2);
      cout << "\nEmpleado despedido con éxito." << endl;
    }
    else if(it1 != -1 and it3 != -1){
      //Antes de proceder, se debe borrar el puntero para evitar fugas.
      delete empleados[it1];
      empleados[it1] = nullptr;
      delete empleadosTemporales[it3];
      empleadosTemporales[it3] = nullptr;

      //Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
      empleados.erase(empleados.begin() + it1);
      empleadosTemporales.erase(empleadosTemporales.begin() + it3);
      cout << "\nEmpleado despedido con éxito." << endl;
    }
  }
  else{
    cout <<"\nNo existe empleado con esa id." << endl;
  }
}

vector<EmpleadoTemporal*> Empresa::getEmpleadosTemporales(){
  return empleadosTemporales;
}

vector<EmpleadoPermanente*> Empresa::getEmpleadosPermanentes(){
  return empleadosPermanentes;
}

//Función que verifica si existe empleado con una id recibida como parámetro. Será de ayuda para informacionEmpleado.
bool Empresa::verificarEmpleado(string idEmpleado){
  bool empleadoExiste = false;
  //Se recorre empleados, si se encuentra retorna true, sino retorna false.
  for(Empleado* empleado: empleados){
    if(empleado->getIdEmpleado() == idEmpleado){
      empleadoExiste = true;
      break;
    }
  }

  return empleadoExiste;
}

//Método que imprime información de un empleado.
void Empresa::informacionEmpleado(string idEmpleado){
  //No se verifica si el empleado existe porque eso ya se verificará en el main.

  //Se recorre empleados.
  for(Empleado* empleado: empleados){
    //Se busca al empleado que coincida con la id.
    if(empleado->getIdEmpleado() == idEmpleado){
      //Si alguno coincide, ahora se verifica su tipo.
      if(empleado->getTipoEmpleado() == "permanente"){
        //Una vez verificado su tipo, se hace dynamic casting.
        EmpleadoPermanente* empleadoPermanente = dynamic_cast<EmpleadoPermanente*>(empleado);
        //Si el casting es exitoso, se procede a imprimir la información.
        if(empleadoPermanente != nullptr){
          cout << "\nInformación del empleado identificado con la id: " << idEmpleado << "." << endl;
          cout << "\nNombre: " << empleadoPermanente->getNombre() << "." << "\nEdad: " << empleadoPermanente->getEdad() << " años." << "\nDocumento: " << empleadoPermanente->getDocumento() << "." << "\nDepartamento: " << empleadoPermanente->getDepartamentoEmpleado() << "." << "\nPuesto: " << empleadoPermanente->getPuestoEmpleado() << "." << "\nTipo de contrato: " << empleadoPermanente->getTipoEmpleado() << "." << "\nSalario: " << empleadoPermanente->getSalario() << endl;
        }
      }
      else if(empleado->getTipoEmpleado() == "temporal"){
        EmpleadoTemporal* empleadoTemporal = dynamic_cast<EmpleadoTemporal*>(empleado);
        if(empleadoTemporal != nullptr){
          cout << "\nInformación del empleado identificado con la id: " << idEmpleado << "." << endl;
          cout << "\nNombre: " << empleadoTemporal->getNombre() << "." << "\nEdad: " << empleadoTemporal->getEdad() << " años." << "\nDocumento: " << empleadoTemporal->getDocumento() << "." << "\nDepartamento: " << empleadoTemporal->getDepartamentoEmpleado() << "." << "\nPuesto: " << empleadoTemporal->getPuestoEmpleado() << "." << "\nTipo de contrato: " << empleadoTemporal->getTipoEmpleado() << "." << "\nValor hora: " << empleadoTemporal->getValorHora() << endl;
        }
      }
      //Una vez terminado todo, se hace break.
      break;
    }
  }
}

void Empresa::editarEmpleado(string idEmpleado){

}

//Se imprime la información general de la empresa.
void Empresa::informeGeneral(){
  cout << "\nCantidad total de empleados: " << empleados.size() << endl;
  cout << "\nCantidad de empleados permanentes: " << empleadosPermanentes.size() << endl;
  cout << "\nCantidad de empleados temporales: " << empleadosTemporales.size() << endl;

  cout << "\nEstado financiero de cada empleado dividido por tipos de empleado:" << endl;
  calcularPagos();

  cout << "\nLo anterior dando un total de: " << totalPagos << " pesos" <<  endl;
}