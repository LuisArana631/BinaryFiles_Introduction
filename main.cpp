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

struct estudiante{
    int tipo;
    char apellido1[21];
    char apellido2[21];
    char nombre[21];
    char codigo[11];
    int nota;
};

struct profesor{
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
        menu_Inicial();
        break;
    case 3:
        //Reporte
        reporte_Registro();
        menu_Inicial();
        break;
    default:
        cout<<"-------------Opcion no existe--------------"<<endl;
        cout<<"-------------------------------------------"<<endl;
        getchar();
        menu_Inicial();
    }
}

void editar_Registro(){
    estudiante auxRecorrer;
    estudiante estudianteStruct;
    profesor profesorStruct;
    FILE* archivo;

    char apellido1[21], apellido2[21], nombre[21];
    int tipo, seccion, existe = 0;
    string codigo;

    if ((archivo = fopen("alumnos_201700988.bin","rb+")) == NULL){
           cout<<"Error al abrir el archivo"<<endl;
           exit(1);
    }

    cout<<"Ingrese el codigo del registro a editar: ";
    getline(cin,codigo);

    fread(&auxRecorrer, sizeof(estudiante), 1, archivo);
    while(!feof(archivo)){

        if(codigo==auxRecorrer.codigo){
            cout<<"-------------------------------------------"<<endl;

            cout<<"apellido 1: ";
            cin>>apellido1;
            cout<<"apellido 2: ";
            cin>>apellido2;
            cout<<"nombre: ";
            cin>>nombre;

            if(auxRecorrer.tipo==1){
                cout<<"seccion: ";
            }else if(auxRecorrer.tipo==0){
                cout<<"nota: ";
            }
            cin>>seccion;

            int pos=ftell(archivo)-sizeof(estudiante);
            fseek(archivo,pos,SEEK_SET);


            if(auxRecorrer.tipo==1){
                profesorStruct.tipo = auxRecorrer.tipo;
                strcpy(profesorStruct.apellido1, apellido1);
                strcpy(profesorStruct.apellido2, apellido2);
                strcpy(profesorStruct.nombre, nombre);
                strcpy(profesorStruct.codigo, auxRecorrer.codigo);
                profesorStruct.seccion =  seccion;

                fwrite(&profesorStruct, sizeof(profesor),1,archivo);
            }else if(auxRecorrer.tipo==0){
                estudianteStruct.tipo = auxRecorrer.tipo;
                strcpy(estudianteStruct.apellido1,  apellido1);
                strcpy(estudianteStruct.apellido2, apellido2);
                strcpy(estudianteStruct.nombre, nombre);
                strcpy(estudianteStruct.codigo, auxRecorrer.codigo);
                estudianteStruct.nota = seccion;

                fwrite(&estudianteStruct, sizeof(estudiante),1,archivo);
            }

            cout<<"-------------------------------------------"<<endl;
            printf("Registro modificado.");
            existe = 1;
            break;
        }

        fread(&auxRecorrer, sizeof(estudiante), 1, archivo);
    }

    if (existe==0){
        cout<<"-------------------------------------------"<<endl;
        printf("No existe registro con ese codigo.");
    }

    getchar();
    fclose(archivo);


}

void ingresar_Registro(){
    estudiante estudianteStruct;
    profesor profesorStruct;
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
    cout<<"apellido 1: ";
    cin>>apellido1;    
    cout<<"apellido 2: ";
    cin>>apellido2;    
    cout<<"nombre: ";
    cin>>nombre;    
    cout<<"codigo: ";
    cin>>codigo;    

    if(tipo==1){
        cout<<"seccion: ";
    }else if(tipo==0){
        cout<<"nota: ";
    }
    cin>>seccion;    

    if(tipo==1){
        profesorStruct.tipo = tipo;
        strcpy(profesorStruct.apellido1, apellido1);
        strcpy(profesorStruct.apellido2, apellido2);
        strcpy(profesorStruct.nombre, nombre);
        strcpy(profesorStruct.codigo, codigo);
        profesorStruct.seccion =  seccion;

        fseek(archivo,0,SEEK_END);
        fwrite(&profesorStruct, sizeof(profesor),1,archivo);
    }else if(tipo==0){
        estudianteStruct.tipo = tipo;
        strcpy(estudianteStruct.apellido1,  apellido1);
        strcpy(estudianteStruct.apellido2, apellido2);
        strcpy(estudianteStruct.nombre, nombre);
        strcpy(estudianteStruct.codigo, codigo);
        estudianteStruct.nota = seccion;

        fseek(archivo,0,SEEK_END);
        fwrite(&estudianteStruct, sizeof(estudiante),1,archivo);
    }

    getchar();
    fclose(archivo);
}

void reporte_Registro(){
    estudiante estudianteStruct;
    FILE* archivo;

    if ((archivo = fopen("alumnos_201700988.bin","rb")) == NULL){
           cout<<"Error al abrir el archivo"<<endl;
           exit(1);
    }

    fread(&estudianteStruct, sizeof(estudiante), 1, archivo);

    while(!feof(archivo)){
        cout<<"tipo: "<< estudianteStruct.tipo<<endl;
        cout<<"apellido1: "<<estudianteStruct.apellido1<<endl;
        cout<<"apellido2: "<<estudianteStruct.apellido2<<endl;
        cout<<"nombre: "<<estudianteStruct.nombre<<endl;
        cout<<"codigo: "<<estudianteStruct.codigo<<endl;
        if(estudianteStruct.tipo  == 0){
            cout<<"nota: "<<estudianteStruct.nota<<endl;
        }else if(estudianteStruct.tipo == 1){
            cout<<"seccion: "<<estudianteStruct.nota<<endl;
        }
        cout<<"-------------------------------------------"<<endl;

        fread(&estudianteStruct, sizeof(estudiante), 1, archivo);
    }

    fclose(archivo);
    getchar();
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
