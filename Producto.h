#pragma once
#include <iostream>
using namespace std;

class Producto{
    private:
        string nombre;
        int precio;
        int id;
    
    public:
        Producto(string nombre, int precio, int id);
        string getNombre();
        void setNombre(string nombre);
        int getPrecio();
        void setPrecio(int precio);
        int getId();
        void setId(int id);
        ~Producto();
};