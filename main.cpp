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
void leerClientes(string nombre_archivo, queue<Cliente*>& clientes){
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
    cout<<"\n----MENU----"<<endl;
    cout<<"1) Entregar números (llegada nuevo cliente)"<<endl;
    cout<<"2) Llamar a cliente"<<endl;
    cout<<"3) Gestionar bodega"<<endl;
    cout<<"4) Salir"<<endl;
    cout<<"Ingresa una opción: ";
}

//este método entrega el número de atención del cliente ingresado según su rut
int entregarNumero(queue<Cliente*> cola, string rut){
    int numero = 1;
    while(!cola.empty()){
        if (cola.front()->getRut() != rut){
            numero++;
            cola.pop();
        } else {
            return numero;
        }
    }
    return -1;
}

//ordena la cola en función del orden de prioridad de la fila (primero embarazadas, segundo discapacitados, 
//tercero tercera edad y cuarto normal) y orden de llegada
void ordenarCola(queue<Cliente*> &cola){
    queue<Cliente*> normales;
    queue<Cliente*> embarazadas;
    queue<Cliente*> discapacidades;
    queue<Cliente*> terceraEdades;

    while (!cola.empty()){
        if (cola.front()->getTipo() == "Normal"){
            normales.push(cola.front());
            cola.pop();
        } else if (cola.front()->getTipo() == "Embarazada"){
            embarazadas.push(cola.front());
            cola.pop();
        } else if (cola.front()->getTipo() == "Discapacidad"){
            discapacidades.push(cola.front());
            cola.pop();
        } else if (cola.front()->getTipo() == "Tercera Edad"){
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

//Agrega un cliente ingresado por pantalla a la fila de clientes, según su tipo
void agregarClienteCola(queue<Cliente*> &cola){
    string nombre;
    string rut;
    string tipo;

    Cliente* cliente = nullptr;

    cout<<"Ingrese su nombre y apellido: ";
    getline(cin >> ws, nombre);

    cout<<"Ingrese su rut: ";
    cin>>rut;

    cout<<"Ingrese su tipo (Normal, Embarazada, Discapacidad, Tercera Edad): ";
    getline(cin >> ws, tipo);
    while(tipo != "Normal" && tipo != "Embarazada" && tipo != "Discapacidad" && tipo != "Tercera Edad"){
        cout<<"Tipo invalido, ingrese nuevamente (Normal, Embarazada, Discapacidad, Tercera Edad): ";
        getline(cin >> ws, tipo);
    }

    cliente = new Cliente(nombre, rut, tipo);
    cola.push(cliente);
    ordenarCola(cola);

    cout<<"Estimado "<<nombre<<", su número de atención es: "<<entregarNumero(cola, rut)<<endl;

}


//Este método muestra el estado actual de la cola
void mostrarCola(queue<Cliente*> cola){
    while(!cola.empty()){
        cout<<cola.front()->getNombre()<<" |Tipo "<<cola.front()->getTipo()<<endl;
        cola.pop();
    }
}

//Este método se encarga de generar la venta del producto, actualizando la cantidad de este y calculando el precio a pagar
void generarVenta(Producto* &producto){
    int cantidad;
    int unidades_disponibles = producto->getCantidad();
    cout<<"Unidades disponibles: "<<unidades_disponibles<<endl;
    cout<<"Ingrese la cantidad que desea comprar: ";
    cin>>cantidad;
    while(cantidad > unidades_disponibles){
        cout<<"\nNo se dispone de esa cantidad de unidades."<<endl;
        cout<<"Ingrese la cantidad que desea comprar: ";
        cin>>cantidad;
    }
    producto->setCantidad(unidades_disponibles - cantidad);
    cout<<"\nAhora quedan "<<producto->getCantidad()<<" unidades"<<endl;
    cout<<"El precio a pagar por este producto es $"<<producto->getPrecio() * cantidad<<endl;
}

//Este método devuelve el producto buscado según el id del producto
Producto* buscarProducto(vector<Categoria*>& categorias, int id_producto){
    for (Categoria* categoriaPtr : categorias) {
        for (Subcategoria* subCategoriaPtr : categoriaPtr->getSubcategorias()){
            for (Producto* productoPtr : subCategoriaPtr->getProductos()){
                if (productoPtr->getId() == id_producto){
                    return productoPtr;
                }
            }
        }
    }
    return nullptr;
}

//Este método recibe la cola de clientes y el vector de categorías y llama al siguiente cliente para generar la venta
//(solo en caso de que hayan más clientes en la cola)
void llamarACliente(vector<Categoria*>& categorias, queue<Cliente*>& cola){
    int id_producto;

    if(!cola.empty()){
        Cliente* cliente = cola.front();
        cola.pop();
        string respuesta;
        cout<<"\nHola "<<cliente->getNombre()<<" bienvenido al local de ventas"<<endl;
        do{
            cout<<"\nIngrese el id del producto que desea comprar: ";
            cin>>id_producto;
            Producto* producto = buscarProducto(categorias, id_producto);
            while(producto == nullptr){
                cout<<"\nEl id ingresado no existe. Ingrese el id del producto que desea comprar: ";
                cin>>id_producto;
                producto = buscarProducto(categorias, id_producto);
            }

            while(producto->getCantidad() == 0){
                cout<<"\nEl producto"<<producto->getNombre()<<" no tiene unidades disponibles!. \nIngrese el id del producto que desea comprar: ";
                cin>>id_producto;
                producto = buscarProducto(categorias, id_producto);
            }

            cout<<"\nEl producto a comprar es "<<producto->getNombre()<<" que tiene un precio de $"<<producto->getPrecio()<<endl;
            
            generarVenta(producto);
            cout<<"Desea comprar otro producto?(Si/No): ";
            cin>>respuesta;
            while(respuesta != "Si" and respuesta != "No"){
                cout<<"\nRespuesta inválida, intente otra vez. Desea comprar otro producto?(Si/No): ";
                cin>>respuesta;
                }
        } while(respuesta == "Si");
        cout<<"\nVenta realizada con éxito!"<<endl;
    } else {
        cout<<"\nNo hay más gente en la cola!"<<endl;
    }

}

    

int main(){
    vector<Categoria*> categorias;
    queue<Cliente*> clientes;
    leerArchivoBodega("bodega.txt", categorias);
    leerClientes("clientes.txt", clientes);

    ordenarCola(clientes);
    int opcion = 0;
    while (opcion != 4){
        opciones();
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarClienteCola(clientes);
                break;
            case 2:
                llamarACliente(categorias, clientes);
                break;
            case 3:
                //gestionBodega();
                break;
            case 4:
                cout<<"Saliendo...."<<endl;
                break;
            default:
                cout<<"Opcion invalida, intente nuevamente."<<endl;
            
                
        }
    }

    return 0;
}

