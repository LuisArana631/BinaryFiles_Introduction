#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <curses.h>
#include <fstream>

using namespace std;

void menu_Inicial();
bool validar_Entrada(string);
void ingresar_Registro();
void reporte_Registro();
void editar_Registro();

struct registroStruct{
    int tipo;
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
        menu_Inicial();
        break;
    case 2:
        //Editar
        editar_Registro();
        break;
    case 3:
        //Reporte
        reporte_Registro();
        break;
    default:
        cout<<"-------------Opcion no existe--------------"<<endl;
        cout<<"-------------------------------------------"<<endl;
        getchar();
        menu_Inicial();
    }
}

void editar_Registro(){
    registroStruct registro;
    FILE* archivo;

    char apellido1[21], apellido2[21], nombre[21], codigo[11];
    int tipo, seccion;

    if ((archivo = fopen("alumnos_201700988.bin","rb+")) == NULL){
           cout<<"Error al abrir el archivo"<<endl;
           exit(1);
    }

}

void ingresar_Registro(){
    registroStruct registro;
    FILE* archivo;

    char apellido1[21], apellido2[21], nombre[21], codigo[11];
    int tipo, seccion;

    if ((archivo = fopen("alumnos_201700988.bin","rb+")) == NULL){
           cout<<"Error al abrir el archivo"<<endl;
           exit(1);
    }

    cout<<"Ingrese los datos del registro: "<<endl;
    cout<<"tipo: ";
    cin>>tipo;
    registro.tipo = tipo;
    cout<<"apellido 1: ";
    cin>>apellido1;
    strcpy(registro.apellido1,apellido1);
    cout<<"apellido 2: ";
    cin>>apellido2;
    strcpy(registro.apellido2,apellido2);
    cout<<"nombre: ";
    cin>>nombre;
    strcpy(registro.nombre, nombre);
    cout<<"codigo: ";
    cin>>codigo;
    strcpy(registro.codigo, codigo);
    cout<<"seccion: ";
    cin>>seccion;
    registro.seccion = seccion;

    fseek(archivo,0,SEEK_END);
    fwrite(&registro, sizeof(registroStruct),1,archivo);
    fclose(archivo);
}

void reporte_Registro(){
    registroStruct registro;
    FILE* archivo;

    if ((archivo = fopen("alumnos_201700988.bin","rb")) == NULL){
           cout<<"Error al abrir el archivo"<<endl;
           exit(1);
    }


}

void crear_Archivo(){
    ofstream archivo;
    archivo.open("alumnos_201700988.bin",ios::binary);

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
