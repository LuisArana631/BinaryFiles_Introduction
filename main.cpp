#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <curses.h>
#include <fstream>

using namespace std;

void menu_Inicial();
bool validar_Entrada(string);
void ingresar_Registro();

struct estudianteStruct{
    char tipo[1];
    char apellido1[21];
    char apellido2[21];
    char nombre[21];
    char codigo[11];
    int seccion;
};

struct profersorStruct{
    char tipo[1];
    char apellido1[21];
    char apellido2[21];
    char nombre[21];
    char codigo[11];
    int seccion;
};

void menu_Inicial(){
    string opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try {
            system("clear");
            cout<<"-------------------------------------------"<<endl;
            cout<<"-----------------CONSOLA-------------------"<<endl;
            cout<<"-------------------------------------------"<<endl;
            cout<<"0.Exit | 1.Ingresar | 2.Editar | 3.Reportes"<<endl;
            cout<<"-------------------------------------------"<<endl;
            cout<<"Opcion: ";
            getline(cin, opcion);
            entradaValida = validar_Entrada(opcion);
            cout<<"-------------------------------------------"<<endl;
            if(!entradaValida)
                throw opcion;
        } catch (string error) {
            cout<<"-------------Opcion no existe--------------"<<endl;
            cout<<"-------------------------------------------"<<endl;
            getchar();
        }
    }

    int opcionEntera =  atoi(opcion.c_str());

    switch(opcionEntera){
    case 0:
        exit(0);
        break;
    case 1:
        //Ingresar
        ingresar_Registro();
        break;
    case 2:
        //Editar

        break;
    case 3:
        //Eliminar

        break;
    default:
        cout<<"-------------Opcion no existe--------------"<<endl;
        cout<<"-------------------------------------------"<<endl;
        getchar();
        menu_Inicial();
    }
}

void ingresar_Registro(){

}

void crear_Archivo(){
    ofstream archivo;
    archivo.open("alumnos_201700988.dat",ios::binary);

    if(archivo.fail()){
        cout<<"No se pudo crear el archivo."<<endl;
        exit(1);
    }
}

bool validar_Entrada(string opcion){
    int i;
    int inicio = 0;

    if(opcion.length()==0)
        return false;

    for(i=inicio; i < (int)opcion.length(); i++){
        if(!isdigit(opcion[i])){
            return false;
        }
    }

    return true;

}

int main(){
    crear_Archivo();
    menu_Inicial();
    return 0;
}
