#include <iostream>
#include "Subcategoria.h"
#include "Producto.h"
using namespace std;

Subcategoria::Subcategoria(string nombre){
    this->nombre = nombre;
    this->productos = vector<Producto>();
}

string Subcategoria::getNombre() {
    return nombre;
}

void Subcategoria::setNombre(string nombre) {
    this->nombre = nombre;
}

vector<Producto> Subcategoria::getProductos() {
    return productos;
}

void Subcategoria::setProductos(vector<Producto> productos) {
    this->productos = productos;
}

Subcategoria::~Subcategoria(){}