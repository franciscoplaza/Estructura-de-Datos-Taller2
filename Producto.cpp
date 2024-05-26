#include <iostream>
#include "Producto.h"
using namespace std;

Producto::Producto(string nombre, int precio, int id){
    this->nombre = nombre;
    this->precio = precio;
    this->id = id;
}

string Producto::getNombre() {
    return nombre;
}

void Producto::setNombre(string nombre) {
    this->nombre = nombre;
}

int Producto::getPrecio() {
    return precio;
}

void Producto::setPrecio(int precio) {
    this->precio = precio;
}

int Producto::getId() {
    return id;
}

void Producto::setId(int id) {
    this->id = id;
}

Producto::~Producto(){};