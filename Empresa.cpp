#include <iostream>
#include "Empresa.h"
#include <algorithm>
#include <cctype>
using namespace std;

Empresa::Empresa(string nombreEmpresa)
{
  this->nombreEmpresa = nombreEmpresa;
}

// Destructor.
Empresa::~Empresa()
{
  // El for elimina cada puntero para liberar la memoria usada. Al final se hace clear a los vectores.
  for (Empleado *empleado : empleados)
  {
    delete empleado;
    empleado = nullptr;
  }
  empleados.clear();
  empleadosPermanentes.clear();
  empleadosTemporales.clear();
}

string Empresa::getNombreEmpresa()
{
  return nombreEmpresa;
}

vector<Empleado *> Empresa::getEmpleados()
{
  return empleados;
}

vector<EmpleadoTemporal *> Empresa::getEmpleadosTemporales()
{
  return empleadosTemporales;
}

vector<EmpleadoPermanente *> Empresa::getEmpleadosPermanentes()
{
  return empleadosPermanentes;
}

void Empresa::setNombreEmpresa(string nombreEmpresa)
{
  this->nombreEmpresa = nombreEmpresa;
}

// Método para "contratar" un empleado.
void Empresa::contratarEmpleado()
{
  string nombrePersona, documentoPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado;
  int edadPersona;

  bool nombrePersonaValido;
  // Ciclo do-while para verificar datos ingresados.
  do
  {
    nombrePersonaValido = true;
    cout << "\nIngrese el nombre del empleado: ";
    cin.ignore();
    cin >> nombrePersona;
    // Se verifica si es dígito carácter a carácter.
    for (char caracter : nombrePersona)
    {
      if (isdigit(caracter))
      {
        cout << "\nPor favor ingrese el nombre sin dígitos." << endl;
        nombrePersonaValido = false;
        break;
      }
    }
  }
  // Se repite el ciclo hasta que no sea válido el nombre ingresado.
  while (not(nombrePersonaValido));

  // Se verifica que no hayan empleados con el mismo documento y que el documento no sea mayor o menor a 10 dígitos.
  bool documentoRepetido, documentoValidoLength, documentoValidoCaracteres;
  do
  {
    documentoValidoLength = true;
    documentoValidoCaracteres = true;
    documentoRepetido = false;
    cout << "\nIngrese el documento del empleado: ";
    cin >> documentoPersona;

    // Se verifica que no esté repetido el documento.
    for (Empleado *empleado : empleados)
    {
      // Se verifica el tipo del empleado para aplicar el dynamic cast correspondiente. Es necesario porque Empleado no hereda de Persona.
      if (empleado->getTipoEmpleado() == "permanente")
      {
        EmpleadoPermanente *empleadoPermanente = dynamic_cast<EmpleadoPermanente *>(empleado);

        // Se verifica si el documento ingresado es igual a alguno ya existente.
        if (empleadoPermanente->getDocumento() == documentoPersona)
        {
          cout << "\nDocumento repetido." << endl;
          documentoRepetido = true;
          break;
        }
      }
      // Si no es permanente, se asume que es temporal.
      else if (empleado->getTipoEmpleado() == "temporal")
      {
        EmpleadoTemporal *empleadoTemporal = dynamic_cast<EmpleadoTemporal *>(empleado);

        if (empleadoTemporal->getDocumento() == documentoPersona)
        {
          cout << "\nDocumento repetido." << endl;
          documentoRepetido = true;
          break;
        }
      }
    }

    // Se verifica si solo hay dígitos en el input.
    for (char caracter : documentoPersona)
    {
      // Se verifica si el carácter es dígito.
      if (not(isdigit(caracter)))
      {
        cout << "\nPor favor ingrese el nombre sin carácteres." << endl;
        documentoValidoCaracteres = false;
        break;
      }
    }

    // Se verifica el length del input acorde a la restricción puesta.
    if (documentoPersona.length() < 10 or documentoPersona.length() > 10)
    {
      cout << "\nEl documento ingresado debe tener 10 dígitos, no más, no menos." << endl;
      documentoValidoLength = false;
    }
    // Se repite hasta que el input cumpla con las condiciones pedidas.
  } while ((documentoRepetido) or (not(documentoValidoLength)) or (not(documentoValidoCaracteres)));

  /*Se restringen ciertos inputs a la edad, primero, que esté entre 18 y 100 años, segundo, que si se ingresan carácteres, se soporten ese tipo de inputs y mediante un try se muestre el error y siga en marcha el programa.*/
  bool rangoEdadValido, edadValidaNoCaracter;
  do
  {
    try
    {
      cout << "\nIngrese la edad del empleado: ";
      cin >> edadPersona;

      // Si se ingresa un input incorrecto a un cin este puede fallar, cin.fail() capta eso y retorna true o false si ha sucedido.
      if (cin.fail())
      {
        // Como efectivamente va a haber un cin.fail si se ingresa una letra, se abre este if.
        throw runtime_error("Se han ingresado datos que no son numéricos.");
      }
      // Si no sucede un cin.fail, se procede.
      else
      {
        edadValidaNoCaracter = true;
      }

      if (edadPersona < 18 or edadPersona > 100)
      {
        throw out_of_range("Se ha salido del rango permitido para la edad.");
      }
      else
      {
        rangoEdadValido = true;
      }
    }
    // Se hace catch cuando se ingrese un carácter.
    catch (runtime_error &ingresoDeCaracter)
    {
      // Se hace clear de cualquier cin fail anterior, luego un ignore para evitar inputs raros.
      cin.clear();
      cin.ignore();
      cout << "\nError: " << ingresoDeCaracter.what() << endl;
      cout << "\nPor favor ingrese una edad válida que solo contenga dígitos." << endl;
      edadValidaNoCaracter = false;
    }
    // Se hace catch cuando esté fuera del rango.
    catch (out_of_range &edadFueraDeRango)
    {
      cout << "\nError: " << edadFueraDeRango.what() << endl;
      cout << "\nPor favor ingrese una edad válida entre 18 y 100 años." << endl;
      rangoEdadValido = false;
    }
  }
  // Mientras que alguno de los dos booleanos sea falso (con not sería true), el ciclo se sigue ejecutando.
  while ((not(edadValidaNoCaracter)) or (not(rangoEdadValido)));

  bool idEmpleadoValida, idEmpleadoRepetida;
  // Se agrega la restricción de carácteres a 3, este número puede ser mayor o menor dependiendo del cliente.
  do
  {
    idEmpleadoRepetida = false;

    cout << "\nIngrese la id del empleado: ";
    cin >> idEmpleado;

    // Se revisa empleado a empleado si el id no está repetida.
    for (Empleado *empleado : empleados)
    {
      if (empleado->getIdEmpleado() == idEmpleado)
      {
        cout << "\nId repetida." << endl;
        idEmpleadoRepetida = true;
        break;
      }
    }

    // La restricción específica ideada por nosotros es esta, puede cambiar dependiendo de la empresa.
    if (idEmpleado.length() < 1 or idEmpleado.length() > 1)
    {
      idEmpleadoValida = false;
      cout << "\nIngrese una id de 1 carácter." << endl;
    }
    else
    {
      idEmpleadoValida = true;
    }
  } while (((not idEmpleadoValida)) or (idEmpleadoRepetida));

  // No hay restricciones para este apartado.
  cout << "\nIngrese el departamento del empleado: ";
  cin.ignore();
  cin >> departamentoEmpleado;

  cout << "\nIngrese el puesto del empleado: ";
  cin >>puestoEmpleado;

  int eleccionTipoEmpleado;
  bool eleccionEmpleadoValida;
  // Se agrega lógica para que se ingrese un input válido y soportado.
  do
  {
    cout << "\n¿Que tipo de empleado es?" << endl
         << "1. Empleado Permanente" << endl
         << "2. Empleado Temporal" << endl;
    cout << "\nSu elección: ";
    cin >> eleccionTipoEmpleado;
    if (eleccionTipoEmpleado == 1)
    {
      tipoEmpleado = "permanente";
      eleccionEmpleadoValida = true;
    }
    else if (eleccionTipoEmpleado == 2)
    {
      tipoEmpleado = "temporal";
      eleccionEmpleadoValida = true;
    }
    else
    {
      eleccionEmpleadoValida = false;
      cout << "\nPor favor ingrese 1 o 2." << endl;
    }
  } while (not(eleccionEmpleadoValida));

  // Una vez verificado lo anterior, se crea el objeto acorde a su tipo.
  if (tipoEmpleado == "permanente")
  {
    EmpleadoPermanente *empleadoPermanente = new EmpleadoPermanente(nombrePersona, documentoPersona, edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado);
    empleados.push_back(empleadoPermanente);
    empleadosPermanentes.push_back(empleadoPermanente);

    float salarioEmpleado, valorHoraEmpleado;
    bool salarioValido, valorHoraValido;
    do
    {
      try
      {
        // Se pregunta por el salario del empleado y el valor de su hora para las horas extras.
        cout << "\nIngrese el salario que tendrá el empleado: ";
        cin >> salarioEmpleado;
        empleadoPermanente->setSalario(salarioEmpleado);

        // Se verifica que no hayan habido fallos en el cin, si los hay se hace throw del respectivo error.
        if (cin.fail())
        {
          throw runtime_error("Se han ingresado carácteres al input de salario.");
        }
        else
        {
          salarioValido = true;
        }

        cout << "\nIngrese el valor por hora que tendrá el empleado: ";
        cin >> valorHoraEmpleado;
        empleadoPermanente->setValorHora(valorHoraEmpleado);

        if (cin.fail())
        {
          throw runtime_error("Se han ingresado carácteres al input de valor hora.");
        }
        else
        {
          valorHoraValido = true;
        }
      }
      // Se define como se procesan dichos throw.
      catch (runtime_error &inputNoValido)
      {
        cin.clear();
        cin.ignore();
        /* Como tenemos dos runtime_error del mismo tipo, los diferenciamos mediante su mensaje de error.
        what() retorna el mensaje de error.*/
        if (inputNoValido.what() == "Se han ingresado carácteres al input de salario.")
        {
          cout << "\nError: " << inputNoValido.what() << endl;
          cout << "\nPor favor ingrese solo dígitos." << endl;
          salarioValido = false;
        }
        else
        {
          cout << "\nError: " << inputNoValido.what() << endl;
          cout << "\nPor favor ingrese solo dígitos." << endl;
          valorHoraValido = false;
        }
      }
    } while (((not salarioValido)) or ((not valorHoraValido)));
    cout << "\nEmpleado contratado con éxito." << endl;
  }
  else
  {
    EmpleadoTemporal *empleadoTemporal = new EmpleadoTemporal(nombrePersona, documentoPersona, edadPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado);
    empleados.push_back(empleadoTemporal);
    empleadosTemporales.push_back(empleadoTemporal);

    bool valorHoraValido;
    float valorHoraEmpleado;

    do
    {
      try
      {
        cout << "\nIngrese el valor por hora que tendrá el empleado: ";
        cin >> valorHoraEmpleado;
        empleadoTemporal->setValorHora(valorHoraEmpleado);

        if (cin.fail())
        {
          throw runtime_error("Se han ingresado carácteres al input de valor hora.");
        }
        else
        {
          valorHoraValido = true;
        }
      }
      catch (runtime_error &inputNoValido)
      {
        cin.clear();
        cin.ignore();
        cout << "\nError: " << inputNoValido.what() << endl;
        cout << "\nPor favor ingrese solo dígitos." << endl;
        valorHoraValido = false;
      }
    } while (not(valorHoraValido));
    cout << "\nEmpleado contratado con éxito." << endl;
  }
}

/*En el programa final este método no debería ser parte de él, solo fue creado para facilitar pruebas con el programa*/
void Empresa::agregarEmpleado(Empleado *unEmpleado)
{
  empleados.push_back(unEmpleado);

  /*Se verifica el tipoEmpleado. Además, nótese que no se verifican realmente los datos del empleado desde afuera, esto debido a que como dijimos antes, esta función NO debería estar en el programa final, solo está para facilitar pruebas a nostros y al profesor.*/
  if (unEmpleado->getTipoEmpleado() == "permanente")
  {
    // Se intenta realizar dynamic casting, si es exitoso retorna un puntero válido, si no lo es, retorna nullptr.
    EmpleadoPermanente *empleado = dynamic_cast<EmpleadoPermanente *>(unEmpleado);
    if (empleado != nullptr)
    {
      empleadosPermanentes.push_back(empleado);
    }
    // Teóricamente este cout nunca debería ocurrir, pero si ocurre ya se sabría que error ocurrió,
    else
    {
      cout << "\nAcción no exitosa." << endl;
    }
  }
  if (unEmpleado->getTipoEmpleado() == "temporal")
  {
    EmpleadoTemporal *empleado = dynamic_cast<EmpleadoTemporal *>(unEmpleado);
    if (empleado != nullptr)
    {
      empleadosTemporales.push_back(empleado);
    }
    else
    {
      cout << "\nAcción no exitosa." << endl;
    }
  }
}

// Función que verifica si existe empleado con una id recibida como parámetro. Será de ayuda para informacionEmpleado.
bool Empresa::verificarEmpleado(string idEmpleado)
{
  bool empleadoExiste = false;
  // Se recorre empleados, si se encuentra retorna true, sino retorna false.
  for (Empleado *empleado : empleados)
  {
    if (empleado->getIdEmpleado() == idEmpleado)
    {
      empleadoExiste = true;
      break;
    }
  }

  return empleadoExiste;
}

// Método que imprime información de un empleado.
void Empresa::informacionEmpleado()
{
  string idEmpleado;
  bool idEmpleadoValida, existeEmpleado;
  // Ciclo do-while para verificar ciertos requisitos.
  do
  {
    cout << "\nIngrese la id del empleado: ";
    cin >> idEmpleado;

    // La restricción específica ideada por nosotros es esta, puede cambiar dependiendo de la empresa.
    if (idEmpleado.length() < 1 or idEmpleado.length() > 1)
    {
      idEmpleadoValida = false;
      cout << "\nIngrese una id de 1 carácter." << endl;
    }
    else
    {
      idEmpleadoValida = true;
    }

    if (idEmpleadoValida)
    {
      // Se verifica que exista.
      existeEmpleado = verificarEmpleado(idEmpleado);

      if (not(existeEmpleado))
      {
        cout << "\nNo existe empleado con esa id." << endl;
      }
    }

  } while ((not(idEmpleadoValida)) or (not(existeEmpleado)));

  // Se recorre empleados.
  for (Empleado *empleado : empleados)
  {
    // Se busca al empleado que coincida con la id.
    if (empleado->getIdEmpleado() == idEmpleado)
    {
      // Si alguno coincide, ahora se verifica su tipo.
      if (empleado->getTipoEmpleado() == "permanente")
      {
        // Una vez verificado su tipo, se hace dynamic casting. Es necesario porque empleado carece de ciertos atributos y métodos de sus subclases.
        EmpleadoPermanente *empleadoPermanente = dynamic_cast<EmpleadoPermanente *>(empleado);
        // Si el casting es exitoso, se procede a imprimir la información.
        if (empleadoPermanente != nullptr)
        {
          cout << "\nInformación del empleado identificado con la id: " << idEmpleado << "." << endl;
          cout << "\nNombre: " << empleadoPermanente->getNombre() << "."
               << "\nEdad: " << empleadoPermanente->getEdad() << " años."
               << "\nDocumento: " << empleadoPermanente->getDocumento() << "."
               << "\nDepartamento: " << empleadoPermanente->getDepartamentoEmpleado() << "."
               << "\nPuesto: " << empleadoPermanente->getPuestoEmpleado() << "."
               << "\nTipo de contrato: " << empleadoPermanente->getTipoEmpleado() << "."
               << "\nSalario: " << empleadoPermanente->getSalario() << endl;
        }
      }
      else if (empleado->getTipoEmpleado() == "temporal")
      {
        EmpleadoTemporal *empleadoTemporal = dynamic_cast<EmpleadoTemporal *>(empleado);
        if (empleadoTemporal != nullptr)
        {
          cout << "\nInformación del empleado identificado con la id: " << idEmpleado << "." << endl;
          cout << "\nNombre: " << empleadoTemporal->getNombre() << "."
               << "\nEdad: " << empleadoTemporal->getEdad() << " años."
               << "\nDocumento: " << empleadoTemporal->getDocumento() << "."
               << "\nDepartamento: " << empleadoTemporal->getDepartamentoEmpleado() << "."
               << "\nPuesto: " << empleadoTemporal->getPuestoEmpleado() << "."
               << "\nTipo de contrato: " << empleadoTemporal->getTipoEmpleado() << "."
               << "\nValor hora: " << empleadoTemporal->getValorHora() << endl;
        }
      }
      // Una vez terminado todo, se hace break.
      break;
    }
  }
}

// Método para editar información de un empleado existente.
void Empresa::editarEmpleado()
{
  string idEmpleado;
  bool idEmpleadoValida, existeEmpleado;
  // Ciclo do-while para verificar ciertos requisitos.
  do
  {
    cout << "\nIngrese la id del empleado: ";
    cin >> idEmpleado;

    // La restricción específica ideada por nosotros es esta, puede cambiar dependiendo de la empresa.
    if (idEmpleado.length() < 1 or idEmpleado.length() > 1)
    {
      idEmpleadoValida = false;
      cout << "\nIngrese una id de 1 carácter." << endl;
    }
    else
    {
      idEmpleadoValida = true;
    }

    if (idEmpleadoValida)
    {
      // Se verifica que exista.
      existeEmpleado = verificarEmpleado(idEmpleado);

      if (not(existeEmpleado))
      {
        cout << "\nNo existe empleado con esa id." << endl;
      }
    }

  } while ((not(idEmpleadoValida)) or (not(existeEmpleado)));

  int opcion;
  // No habrá documentación para esta parte del código, mucho de lo que está acá ya fue documentado en su respectivo sitio.
  for (Empleado *empleado : empleados)
  {
    if (empleado->getIdEmpleado() == idEmpleado)
    {
      if (empleado->getTipoEmpleado() == "permanente")
      {
        do
        {
          EmpleadoPermanente *empleadoPermanente = dynamic_cast<EmpleadoPermanente *>(empleado);
          cout << "\n1. Editar nombre."
               << "\n2. Editar documento."
               << "\n3. Editar edad."
               << "\n4. Editar id."
               << "\n5. Editar departamento."
               << "\n6. Editar puesto."
               << "\n7. Editar salario y valor por hora."
               << "\n8. Editar horas extra trabajadas."
               << "\n9. Salir." << endl;
          cout << "\nDígite la opción a elegir: ";
          cin >> opcion;
          string nombrePersona, documentoPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado;
          int edadPersona;
          if (opcion == 1)
          {
            bool nombrePersonaValido;
            // Ciclo do-while para verificar datos ingresados.
            do
            {
              nombrePersonaValido = true;
              cout << "\nIngrese el nombre nuevo del empleado: ";
              cin >> nombrePersona;

              // Se verifica carácter por carácter si hay dígitos.
              for (char caracter : nombrePersona)
              {
                if (isdigit(caracter))
                {
                  cout << "\nPor favor ingrese el nombre sin dígitos." << endl;
                  nombrePersonaValido = false;
                  break;
                }
              }
            } while (not(nombrePersonaValido));
            empleadoPermanente->setNombre(nombrePersona);
            cout << "\nEl nombre fue editado con éxito." << endl;
          }

          if (opcion == 2)
          {
            bool documentoRepetido, documentoValidoLength, documentoValidoCaracteres;
            do
            {
              documentoValidoLength = true;
              documentoValidoCaracteres = true;
              documentoRepetido = false;
              cout << "\nIngrese el documento del empleado: ";
              cin >> documentoPersona;

              for (Empleado *empleado : empleados)
              {
                if (empleado->getTipoEmpleado() == "permanente")
                {
                  EmpleadoPermanente *empleadoPermanente = dynamic_cast<EmpleadoPermanente *>(empleado);

                  if (empleadoPermanente->getDocumento() == documentoPersona)
                  {
                    cout << "\nDocumento repetido." << endl;
                    documentoRepetido = true;
                    break;
                  }
                }
                else if (empleado->getTipoEmpleado() == "temporal")
                {
                  EmpleadoTemporal *empleadoTemporal = dynamic_cast<EmpleadoTemporal *>(empleado);

                  if (empleadoTemporal->getDocumento() == documentoPersona)
                  {
                    cout << "\nDocumento repetido." << endl;
                    documentoRepetido = true;
                    break;
                  }
                }
              }

              for (char caracter : documentoPersona)
              {
                if (not(isdigit(caracter)))
                {
                  cout << "\nPor favor ingrese el nombre sin carácteres." << endl;
                  documentoValidoCaracteres = false;
                  break;
                }
              }

              if (documentoPersona.length() < 10 or documentoPersona.length() > 10)
              {
                cout << "\nEl documento ingresado debe tener 10 dígitos, no más, no menos." << endl;
                documentoValidoLength = false;
              }
            } while ((documentoRepetido) or (not(documentoValidoLength)) or (not(documentoValidoCaracteres)));
            empleadoPermanente->setDocumento(documentoPersona);
            cout << "\nEl documento fue editado con éxito." << endl;
          }

          if (opcion == 3)
          {
            bool rangoEdadValido, edadValida;
            do
            {
              try
              {
                cout << "\nIngrese la edad del empleado: ";
                cin >> edadPersona;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado datos que no son numéricos.");
                }
                else
                {
                  edadValida = true;
                }

                if (edadPersona < 18 or edadPersona > 100)
                {
                  throw out_of_range("Se ha salido del rango permitido para la edad.");
                }
                else
                {
                  rangoEdadValido = true;
                }
              }
              catch (runtime_error &ingresoDeCaracter)
              {
                cin.clear();
                cin.ignore();
                cout << "\nError: " << ingresoDeCaracter.what() << endl;
                cout << "\nPor favor ingrese una edad válida que solo contenga dígitos." << endl;
                edadValida = false;
              }
              catch (out_of_range &edadFueraDeRango)
              {
                cout << "\nError: " << edadFueraDeRango.what() << endl;
                cout << "\nPor favor ingrese una edad válida entre 18 y 100 años." << endl;
                rangoEdadValido = false;
              }
            } while ((not(edadValida)) or (not(rangoEdadValido)));
            empleadoPermanente->setEdad(edadPersona);
            cout << "\nLa edad fue editada con éxito." << endl;
          }

          if (opcion == 4)
          {
            bool idEmpleadoValida, idEmpleadoRepetida;
            do
            {
              idEmpleadoRepetida = false;

              cout << "\nIngrese la nueva id del empleado: ";
              cin >> idEmpleado;

              for (Empleado *empleado : empleados)
              {
                if (empleado->getIdEmpleado() == idEmpleado)
                {
                  cout << "\nId repetida." << endl;
                  idEmpleadoRepetida = true;
                  break;
                }
              }

              if (idEmpleado.length() < 1 or idEmpleado.length() > 1)
              {
                idEmpleadoValida = false;
                cout << "\nIngrese una id de 1 carácter." << endl;
              }
              else
              {
                idEmpleadoValida = true;
              }
            } while (((not idEmpleadoValida)) or (idEmpleadoRepetida));
            empleadoPermanente->setIdEmpleado(idEmpleado);
            cout << "\nEl id fue editado con éxito." << endl;
          }

          if (opcion == 5)
          {
            cout << "\nIngrese el departamento del empleado: ";
            cin >> departamentoEmpleado;
            empleadoPermanente->setDepartamentoEmpleado(departamentoEmpleado);
            cout << "\nEl departamento fue editado con éxito." << endl;
          }
          if (opcion == 6)
          {
            cout << "\nIngrese el puesto del empleado: ";
            cin >> puestoEmpleado;
            empleadoPermanente->setPuestoEmpleado(puestoEmpleado);
            cout << "\nEl puesto fue editado con éxito." << endl;
          }
          if (opcion == 7)
          {
            float salarioEmpleado, valorHoraEmpleado;
            bool salarioValido, valorHoraValido;
            do
            {
              try
              {
                cout << "\nIngrese el nuevo salario que tendrá el empleado: ";
                cin >> salarioEmpleado;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado carácteres al input de salario.");
                }
                else
                {
                  salarioValido = true;
                }

                cout << "\nIngrese el nuevo valor por hora que tendrá el empleado: ";
                cin >> valorHoraEmpleado;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado carácteres al input de valor hora.");
                }
                else
                {
                  valorHoraValido = true;
                }
              }

              catch (runtime_error &inputNoValido)
              {
                cin.clear();
                cin.ignore();
                if (inputNoValido.what() == "Se han ingresado carácteres al input de salario.")
                {
                  cout << "\nError: " << inputNoValido.what() << endl;
                  cout << "\nPor favor ingrese solo dígitos." << endl;
                  salarioValido = false;
                }
                else
                {
                  cout << "\nError: " << inputNoValido.what() << endl;
                  cout << "\nPor favor ingrese solo dígitos." << endl;
                  valorHoraValido = false;
                }
              }
            } while (((not salarioValido)) or ((not valorHoraValido)));

            empleadoPermanente->setSalario(salarioEmpleado);
            cout << "\nEl salario fue editado con éxito." << endl;
            empleadoPermanente->setValorHora(valorHoraEmpleado);
            cout << "\nEl valor por hora fue editado con éxito." << endl;
          }
          if (opcion == 8)
          {
            int horasExtraTrabajadas;
            bool horasValido;

            do
            {
              try
              {
                cout << "\nIngrese la nueva cantidad de horas: ";
                cin >> horasExtraTrabajadas;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado carácteres al input de horas trabajadas.");
                }
                else
                {
                  horasValido = true;
                }
              }
              catch (runtime_error &inputNoValido)
              {
                cin.clear();
                cin.ignore();
                cout << "\nError: " << inputNoValido.what() << endl;
                cout << "\nPor favor ingrese solo dígitos." << endl;
                horasValido = false;
              }
            } while (not(horasValido));

            empleadoPermanente->setHorasExtra(horasExtraTrabajadas);
            cout << "\nLa cantidad de horas fue editada con éxito." << endl;
          }
          if (opcion == 9)
          {
            cout << "\nSaliendo..." << endl;
          }
        } while (opcion != 9);
      }
      else
      {
        do
        {
          EmpleadoTemporal *empleadoTemporal = dynamic_cast<EmpleadoTemporal *>(empleado);
          cout << "\n1. Editar nombre."
               << "\n2. Editar documento."
               << "\n3. Editar edad."
               << "\n4. Editar id."
               << "\n5. Editar departamento."
               << "\n6. Editar puesto."
               << "\n7. Editar valor hora."
               << "\n8. Editar horas trabajadas."
               << "\n9. Salir." << endl;
          cout << "\nDígite la opción a elegir: ";
          cin >> opcion;
          string nombrePersona, documentoPersona, idEmpleado, departamentoEmpleado, puestoEmpleado, tipoEmpleado;
          int edadPersona;
          if (opcion == 1)
          {
            bool nombrePersonaValido;
            do
            {
              nombrePersonaValido = true;
              cout << "\nIngrese el nombre nuevo del empleado: ";
              cin >> nombrePersona;
              for (char caracter : nombrePersona)
              {
                if (isdigit(caracter))
                {
                  cout << "\nPor favor ingrese el nombre sin dígitos." << endl;
                  nombrePersonaValido = false;
                  break;
                }
              }
            } while (not(nombrePersonaValido));
            empleadoTemporal->setNombre(nombrePersona);
            cout << "\nEl nombre fue editado con éxito." << endl;
          }

          if (opcion == 2)
          {
            bool documentoRepetido, documentoValidoLength, documentoValidoCaracteres;
            do
            {
              documentoValidoLength = true;
              documentoValidoCaracteres = true;
              documentoRepetido = false;
              cout << "\nIngrese el documento del empleado: ";
              cin >> documentoPersona;

              for (Empleado *empleado : empleados)
              {
                if (empleado->getTipoEmpleado() == "permanente")
                {
                  EmpleadoPermanente *empleadoPermanente = dynamic_cast<EmpleadoPermanente *>(empleado);

                  if (empleadoPermanente->getDocumento() == documentoPersona)
                  {
                    cout << "\nDocumento repetido." << endl;
                    documentoRepetido = true;
                    break;
                  }
                }
                else if (empleado->getTipoEmpleado() == "temporal")
                {
                  EmpleadoTemporal *empleadoTemporal = dynamic_cast<EmpleadoTemporal *>(empleado);

                  if (empleadoTemporal->getDocumento() == documentoPersona)
                  {
                    cout << "\nDocumento repetido." << endl;
                    documentoRepetido = true;
                    break;
                  }
                }
              }

              for (char caracter : documentoPersona)
              {
                if (not(isdigit(caracter)))
                {
                  cout << "\nPor favor ingrese el nombre sin carácteres." << endl;
                  documentoValidoCaracteres = false;
                  break;
                }
              }

              if (documentoPersona.length() < 10 or documentoPersona.length() > 10)
              {
                cout << "\nEl documento ingresado debe tener 10 dígitos, no más, no menos." << endl;
                documentoValidoLength = false;
              }
            } while ((documentoRepetido) or (not(documentoValidoLength)) or (not(documentoValidoCaracteres)));
            empleadoTemporal->setDocumento(documentoPersona);
            cout << "\nEl documento fue editado con éxito." << endl;
          }

          if (opcion == 3)
          {
            bool rangoEdadValido, edadValida;
            do
            {
              try
              {
                cout << "\nIngrese la edad del empleado: ";
                cin >> edadPersona;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado datos que no son numéricos.");
                }
                else
                {
                  edadValida = true;
                }

                if (edadPersona < 18 or edadPersona > 100)
                {
                  throw out_of_range("Se ha salido del rango permitido para la edad.");
                }
                else
                {
                  rangoEdadValido = true;
                }
              }
              catch (runtime_error &ingresoDeCaracter)
              {
                cin.clear();
                cin.ignore();
                cout << "\nError: " << ingresoDeCaracter.what() << endl;
                cout << "\nPor favor ingrese una edad válida que solo contenga dígitos." << endl;
                edadValida = false;
              }
              catch (out_of_range &edadFueraDeRango)
              {
                cout << "\nError: " << edadFueraDeRango.what() << endl;
                cout << "\nPor favor ingrese una edad válida entre 18 y 100 años." << endl;
                rangoEdadValido = false;
              }
            } while ((not(edadValida)) or (not(rangoEdadValido)));
            empleadoTemporal->setEdad(edadPersona);
            cout << "\nLa edad fue editada con éxito." << endl;
          }

          if (opcion == 4)
          {
            bool idEmpleadoValida, idEmpleadoRepetida;
            do
            {
              idEmpleadoRepetida = false;

              cout << "\nIngrese la nueva id del empleado: ";
              cin >> idEmpleado;

              for (Empleado *empleado : empleados)
              {
                if (empleado->getIdEmpleado() == idEmpleado)
                {
                  cout << "\nId repetida." << endl;
                  idEmpleadoRepetida = true;
                  break;
                }
              }

              if (idEmpleado.length() < 1 or idEmpleado.length() > 1)
              {
                idEmpleadoValida = false;
                cout << "\nIngrese una id de 1 carácter." << endl;
              }
              else
              {
                idEmpleadoValida = true;
              }
            } while (((not idEmpleadoValida)) or (idEmpleadoRepetida));
            empleadoTemporal->setIdEmpleado(idEmpleado);
            cout << "\nEl id fue editado con éxito." << endl;
          }

          if (opcion == 5)
          {
            cout << "\nIngrese el departamento del empleado: ";
            cin >> departamentoEmpleado;
            empleadoTemporal->setDepartamentoEmpleado(departamentoEmpleado);
            cout << "\nEl departamento fue editado con éxito." << endl;
          }
          if (opcion == 6)
          {
            cout << "\nIngrese el puesto del empleado: ";
            cin >> puestoEmpleado;
            empleadoTemporal->setPuestoEmpleado(puestoEmpleado);
            cout << "\nEl puesto fue editado con éxito." << endl;
          }
          if (opcion == 7)
          {
            bool valorHoraValido;
            float valorHoraEmpleado;

            do
            {
              try
              {
                cout << "\nIngrese el valor por hora que tendrá el empleado: ";
                cin >> valorHoraEmpleado;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado carácteres al input de valor hora.");
                }
                else
                {
                  valorHoraValido = true;
                }
              }
              catch (runtime_error &inputNoValido)
              {
                cin.clear();
                cin.ignore();
                cout << "\nError: " << inputNoValido.what() << endl;
                cout << "\nPor favor ingrese solo dígitos." << endl;
                valorHoraValido = false;
              }
            } while (not(valorHoraValido));

            empleadoTemporal->setValorHora(valorHoraEmpleado);
            cout << "\nEl valor por hora del empleado fue editado con éxito." << endl;
          }
          if (opcion == 8)
          {
            int horasTrabajadas;
            bool horasValido;

            do
            {
              try
              {
                cout << "\nIngrese la nueva cantidad de horas: ";
                cin >> horasTrabajadas;

                if (cin.fail())
                {
                  throw runtime_error("Se han ingresado carácteres al input de horas trabajadas.");
                }
                else
                {
                  horasValido = true;
                }
              }
              catch (runtime_error &inputNoValido)
              {
                cin.clear();
                cin.ignore();
                cout << "\nError: " << inputNoValido.what() << endl;
                cout << "\nPor favor ingrese solo dígitos." << endl;
                horasValido = false;
              }
            } while (not(horasValido));

            empleadoTemporal->setHorasTrabajadas(horasTrabajadas);
            cout << "\nLa cantidad de horas fue editada con éxito." << endl;
          }
          if (opcion == 9)
          {
            cout << "\nSaliendo..." << endl;
          }
        } while (opcion != 9);
      }
    }
  }
}

// Función que "despide" un empleado.
void Empresa::despedirEmpleado()
{
  string idEmpleado;
  bool idEmpleadoValida, existeEmpleado;
  // Ciclo do-while para verificar ciertos requisitos.
  do
  {
    cout << "\nIngrese la id del empleado: ";
    cin >> idEmpleado;

    // La restricción específica ideada por nosotros es esta, puede cambiar dependiendo de la empresa.
    if (idEmpleado.length() < 1 or idEmpleado.length() > 1)
    {
      idEmpleadoValida = false;
      cout << "\nIngrese una id de 1 carácter." << endl;
    }
    else
    {
      idEmpleadoValida = true;
    }

    if (idEmpleadoValida)
    {
      // Se verifica que exista.
      existeEmpleado = verificarEmpleado(idEmpleado);

      if (not(existeEmpleado))
      {
        cout << "\nNo existe empleado con esa id." << endl;
      }
    }

  } while ((not(idEmpleadoValida)) or (not(existeEmpleado)));

  // Variables que contendrán la posición del objeto que concuerda con la id del parámetro.
  int it1 = -1;
  int it2 = -1;
  int it3 = -1;

  // Se busca el objeto que coincida con la id del parámetro.
  for (int i = 0; i < empleados.size(); i++)
  {
    if (empleados[i]->getIdEmpleado() == idEmpleado)
    {
      it1 = i;
      break;
    }
  }

  for (int i = 0; i < empleadosTemporales.size(); i++)
  {
    if (empleadosTemporales[i]->getIdEmpleado() == idEmpleado)
    {
      it2 = i;
      break;
    }
  }

  for (int i = 0; i < empleadosPermanentes.size(); i++)
  {
    if (empleadosPermanentes[i]->getIdEmpleado() == idEmpleado)
    {
      it3 = i;
      break;
    }
  }

  /*Nótese que los anteriores for nunca retornarán -1, además de que si no encuentran a un empleado con ese id dentro del respectivo vector, entonces no cambiarán el valor inicial de it1, it2 o it3 que es -1.*/
  if (it1 != -1 and it2 != -1)
  {
    // Antes de proceder, se debe borrar el puntero para evitar fugas.
    delete empleados[it1];
    empleados[it1] = nullptr;
    delete empleadosPermanentes[it2];
    empleadosPermanentes[it2] = nullptr;

    // Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
    empleados.erase(empleados.begin() + it1);
    empleadosPermanentes.erase(empleadosPermanentes.begin() + it2);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
  else if (it1 != -1 and it3 != -1)
  {
    // Antes de proceder, se debe borrar el puntero para evitar fugas.
    delete empleados[it1];
    empleados[it1] = nullptr;
    delete empleadosTemporales[it3];
    empleadosTemporales[it3] = nullptr;

    // Debido a que erase toma como parámetro un iterador, se "convierte" it1 o it2 a uno.
    empleados.erase(empleados.begin() + it1);
    empleadosTemporales.erase(empleadosTemporales.begin() + it3);
    cout << "\nEmpleado despedido con éxito." << endl;
  }
}

// Método que calcula cuanto se le debe pagar a cada empleado.
void Empresa::calcularPagos()
{
  float pago;
  totalPagos = 0;
  // Se recorre el vector y se aplica el método.
  for (Empleado *empleado : empleados)
  {
    pago = empleado->calcularPago();
    totalPagos += pago;
    cout << "\nAl empleado identificado con id de empleado: " << empleado->getIdEmpleado() << ", se le debe pagar: " << pago << " pesos" << endl;
  } 
}

// Se imprime la información general de la empresa.
void Empresa::informeGeneral()
{
  cout << "\nCantidad total de empleados: " << empleados.size() << "." << endl;
  cout << "\nCantidad de empleados permanentes: " << empleadosPermanentes.size() << "." << endl;
  cout << "\nCantidad de empleados temporales: " << empleadosTemporales.size() << "." << endl;

  cout << "\nEstado financiero de cada empleado:" << endl;

  calcularPagos();

  cout << "\nLo anterior dando un total de: " << totalPagos << " pesos." << endl;
}