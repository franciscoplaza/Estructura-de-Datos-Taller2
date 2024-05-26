#include <iostream>
#include "Categoria.h"
#include "Subcategoria.h"
using namespace std;

Categoria::Categoria(string nombre){
    this->nombre = nombre;
    this->subcategorias = vector<Subcategoria>();
}

string Categoria::getNombre() {
    return nombre;
}

void Categoria::setNombre(string nombre) {
    this->nombre = nombre;
}

vector<Subcategoria> Categoria::getSubcategorias() {
    return subcategorias;
}

void Categoria::setSubcategorias(vector<Subcategoria> subcategorias) {
    this->subcategorias = subcategorias;
}