#pragma once
#include <iostream>
#include <vector>
#include "Producto.h"
using namespace std;

class Subcategoria{
    private:
        string nombre;
        vector<Producto> productos;
    
    public:
        Subcategoria(string nombre);
        string getNombre();
        void setNombre(string nombre);
        vector<Producto> getProductos();
        void setProductos(vector<Producto> productos);
};