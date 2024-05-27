#pragma once
#include <iostream>
using namespace std;

class Cliente{
    private:
        string nombre;
        string rut;
        string tipo;
    
    public:
        Cliente(string nombre, string rut, string tipo);
        string getNombre();
        void setNombre(string nombre);
        string getRut();
        void setRut(string rut);
        string getTipo();
        void setTipo(string tipo);
        ~Cliente();
};