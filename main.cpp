#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include "Categoria.h"
#include "Subcategoria.h"
#include "Producto.h"
#include "Cliente.h"
using namespace std;


// Este metodo recibe por metodo el nombre del archivo y un vector, y llena el vector con los datos del txt.
void leerArchivoBodega(string nombre_archivo, vector<Categoria*> &categorias){
    ifstream archivo(nombre_archivo.c_str());
    string linea;
    string parte;
    Categoria* categoriaActual = nullptr;
    Subcategoria* subcategoriaActual = nullptr;
    Producto* productoActual = nullptr;

    while(getline(archivo, linea)){
        int iterador = 0;
        int iterador2 = 0;
        string nombre_producto;
        int id_producto;
        int cantidad_producto;
        int precio_producto;
        stringstream input_stringstream(linea);
        string tipo;
        string parte2;
        while(getline(input_stringstream, parte, ':')){
            iterador++;
            if(iterador == 1){
                tipo = parte;
                //cout<<tipo<<endl;
            }
            if(iterador == 2){
                if (tipo == "Categoria"){
                    //cout<<parte<<endl;
                    categoriaActual = new Categoria(parte);
                    categorias.push_back(categoriaActual);
                } else if (tipo == "Subcategoria"){
                    subcategoriaActual = new Subcategoria(parte);
                    categoriaActual->getSubcategorias().push_back(subcategoriaActual);
                } else if (tipo == "Producto"){
                    stringstream input_stringstream_2(parte);
                    while(getline(input_stringstream_2, parte2, ' ')){
                        iterador2++;
                        if(iterador2 == 1){
                            nombre_producto = parte2;
                        } else if (iterador2 == 2){
                            id_producto = stoi(parte2);
                        } else if (iterador2 == 3){
                            cantidad_producto = stoi(parte2);
                        } else if (iterador2 = 4){
                            precio_producto = stoi(parte2);
                        }
                        //cout<<parte2<<endl;
                    }
                    productoActual = new Producto(nombre_producto, precio_producto, id_producto, cantidad_producto);
                    subcategoriaActual->getProductos().push_back(productoActual);
                }
            }
            
        }
    }
    archivo.close();
}

// este metodo recibe el nombre del archivo y una fila de clientes, y llena la fila con los clientes.
void leerClientes(string nombre_archivo, queue<Cliente*> clientes){
    ifstream archivo(nombre_archivo.c_str());
    string linea;
    string parte;
    Cliente* clienteActual = nullptr;
    
    while(getline(archivo, linea)){
        int iterador = 0;
        stringstream input_stringstream(linea);
        string nombre;
        string rut;
        string tipo;
        while(getline(input_stringstream, parte, ',')){
            iterador++;
            if (iterador == 1){
                nombre = parte;
            } else if (iterador == 2){
                rut = parte;
            } else if (iterador == 3){
                tipo = parte;
            }
        }
        clienteActual = new Cliente(nombre, rut, tipo);
        clientes.push(clienteActual);
    }
}

// este metodo muestra las opciones disponibles en el menu.
void opciones(){
    cout<<"----MENU----"<<endl;
    cout<<"1) Entregar números"<<endl;
    cout<<"2) Llamar a cliente"<<endl;
    cout<<"3) Gestionar bodega"<<endl;
    cout<<"4) Salir"<<endl;
    cout<<"Ingresa una opción"<<endl;
}

//Este método recibe la cola de clientes y la reordena según el orden de prioridades y llegada según tipo
void ordenarCola(queue<string> &cola){
    queue<string> normales;
    queue<string> embarazadas;
    queue<string> discapacidades;
    queue<string> terceraEdades;

    while (!cola.empty()){
        if (cola.front() == "normal"){
            normales.push(cola.front());
            cola.pop();
        } else if (cola.front() == "embarazada"){
            embarazadas.push(cola.front());
            cola.pop();
        } else if (cola.front() == "discapacidad"){
            discapacidades.push(cola.front());
            cola.pop();
        } else if (cola.front() == "tercera edad"){
            terceraEdades.push(cola.front());
            cola.pop();
        }
        
    }

    while (!embarazadas.empty()){
        cola.push(embarazadas.front());
        embarazadas.pop();
    }

    while (!discapacidades.empty()){
        cola.push(discapacidades.front());
        discapacidades.pop();
    }

    while (!terceraEdades.empty()){
        cola.push(terceraEdades.front());
        terceraEdades.pop();
    }

    while (!normales.empty()){
        cola.push(normales.front());
        normales.pop();
    }
}

int main(){
    vector<Categoria*> categorias;
    queue<Cliente*> clientes;
    leerArchivoBodega("bodega.txt", categorias);
    leerClientes("clientes.txt", clientes);

    int opcion = 0;
    while (opcion != 4){
        opciones();
        cin >> opcion;
        switch (opcion) {
            case 1:
                //entregarNumero();
                break;
            case 2:
                //llamarACliente();
                break;
            case 3:
                //gestionBodega();
                break;
            case 4:
                break;
                cout<<"Saliendo...."<<endl;
            default:
                cout<<"Opcion invalida, intente nuevamente."<<endl;
            
                
        }
    }

    return 0;
}

