#include <iostream>
#include "Cliente.h"
using namespace std;

Cliente::Cliente(string nombre, string rut, string tipo) {
    this->nombre = nombre;
    this->rut = rut;
    this->tipo = tipo;
}

string Cliente::getNombre() {
    return nombre;
}

void Cliente::setNombre(string nombre) {
    this->nombre = nombre;
}

string Cliente::getRut() {
    return rut;
}

void Cliente::setRut(string rut) {
    this->rut = rut;
}

string Cliente::getTipo() {
    return tipo;
}

void Cliente::setTipo(string tipo) {
    this->tipo = tipo;
}

Cliente::~Cliente() {}