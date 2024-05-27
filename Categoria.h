#pragma once
#include <iostream>
#include <vector>
#include "Subcategoria.h"
using namespace std;

class Categoria{
    private:
        string nombre;
        vector<Subcategoria*> subcategorias;
    
    public:
        Categoria(string nombre);
        string getNombre();
        void setNombre(string nombre);
        vector<Subcategoria*>& getSubcategorias();
        void setSubcategorias(vector<Subcategoria*> subcategorias);
        ~Categoria();
};