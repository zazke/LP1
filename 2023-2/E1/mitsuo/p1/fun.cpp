#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

#include "fun.hpp"

#define INCREMENTO 5

using namespace std;

void cargarPedidos(int **&fechaClienteCantidad, char **&codigoDelProducto, const char *nombArch){
    int nd=0, cap=0;
    char *cod;
    ifstream arch(nombArch,ios::in);
    if(not arch.is_open()){
        cout<<"error al abrir "<<nombArch<<endl;
        exit(1);
    }
    fechaClienteCantidad = nullptr;
    codigoDelProducto = nullptr;
    while (1) {
        cod = leeCad(arch, ',');
        if (cod==nullptr) break;
        if (nd == cap) aumentaEspacios(fechaClienteCantidad, codigoDelProducto, nd, cap);
        guardaPed(arch, fechaClienteCantidad[nd - 1], codigoDelProducto[nd - 1], cod);
        nd++;
        arch.get();
    }
    qSort(fechaClienteCantidad, codigoDelProducto, 0, nd-2);
}

char *leeCad(istream &arch, char delim){
    char *cad, buff[80];
    arch.getline(buff,80,delim);
    if(arch.eof()) return nullptr;
    cad = new char [strlen(buff)+1];
    strcpy(cad,buff);
    return cad;
}

void aumentaEspacios(int **&fechaClienteCantidad, char **&codigoDelProducto, int &nd, int &cap){
    int **auxF;
    char **auxC;
    cap += INCREMENTO;
    if(fechaClienteCantidad==nullptr){
        fechaClienteCantidad = new int * [cap]{};
        codigoDelProducto = new char * [cap]{};
        nd=1;
    }
    else{
        auxF = new int * [cap]{};
        auxC = new char * [cap]{};
        for(int i=0;i<nd;i++){
            auxF[i] = fechaClienteCantidad[i];
            auxC[i] = codigoDelProducto[i];
        }
        delete fechaClienteCantidad;
        delete codigoDelProducto;
        fechaClienteCantidad = auxF;
        codigoDelProducto = auxC;
    }
}

void guardaPed(istream &arch, int *&fechaClienteCantidad, char *&codigoDelProducto, char *cod){
    int fecha, dni, cant;
    arch>>dni;
    arch.get();
    arch>>cant;
    arch.get();
    fecha = leeFecha(arch);
    fechaClienteCantidad = new int [3] {};
    fechaClienteCantidad[0] = fecha;
    fechaClienteCantidad[1] = dni;
    fechaClienteCantidad[2] = cant;
    codigoDelProducto = cod;
}

int leeFecha(istream &arch){
    int dd,mm,aa;
    char c;
    arch>>dd>>c>>mm>>c>>aa;
    return dd+mm*100+aa*10000;
}

void qSort(int **fechaClienteCantidad, char **codigoDelProducto, int izq, int der){
    int limite;
    if (izq>=der) return;
    cambiar(fechaClienteCantidad[izq],codigoDelProducto[izq],fechaClienteCantidad[(izq+der)/2],codigoDelProducto[(izq+der)/2]);
    limite = izq;
    for(int i=izq+1;i<=der;i++){
        if(desorden(fechaClienteCantidad[i], fechaClienteCantidad[izq])){
            limite++;
            cambiar(fechaClienteCantidad[i],codigoDelProducto[i],fechaClienteCantidad[limite],codigoDelProducto[limite]);
        }
    }
    cambiar(fechaClienteCantidad[izq],codigoDelProducto[izq],fechaClienteCantidad[limite],codigoDelProducto[limite]);
    qSort(fechaClienteCantidad,codigoDelProducto,izq,limite-1);
    qSort(fechaClienteCantidad,codigoDelProducto,limite+1,der);
}

void cambiar(int *&fechaClienteI,char *&codigoDelProductoI,int *&fechaClienteK,char *&codigoDelProductoK){
    int *auxI = fechaClienteI;
    char *auxC = codigoDelProductoI;
    fechaClienteI = fechaClienteK;
    codigoDelProductoI = codigoDelProductoK;
    fechaClienteK = auxI;
    codigoDelProductoK = auxC;
}

bool desorden(int *fechaClienteCantidadI, int *fechaClienteCantidadK){
    return fechaClienteCantidadI[0] < fechaClienteCantidadK[0];
}

void pruebaDeCargaDePedidos(int **fechaClienteCantidad, char **codigoDelProducto, const  char *nombArch){
    ofstream arch(nombArch,ios::out);
    if(not arch.is_open()){
        cout<<"error al abrir "<<nombArch<<endl;
        exit(1);
    }
    arch.precision(2);
    arch<<fixed;
    arch<<setw(43)<<"REPORTE DE PRUEBA DE PEDIDOS"<<endl;
    imprimeLinea(arch,'=');
    arch<<right<<setw(7)<<"FECHA";
    arch<<right<<setw(12)<<"DNI"<<setw(16)<<"CANTIDAD"<<setw(5)<<" "<<left<<setw(20)<<"CODIGO PRODUCTO"<<endl;
    for(int i=0;fechaClienteCantidad[i];i++){
        imprimePedido(arch,fechaClienteCantidad[i], codigoDelProducto[i]);
    }
}

void imprimeLinea(ostream &arch,char c){
    for(int i=0;i<58;i++) arch<<c;
    arch<<endl;
}

void imprimePedido(ostream &arch,int *fechaClienteCantidad, char *codigoDelProducto){
    imprimeFecha(arch,fechaClienteCantidad[0]);
    arch<<right<<setw(12)<<fechaClienteCantidad[1]<<setw(10)<<fechaClienteCantidad[2]<<setw(11)<<" "<<left<<setw(10)<<codigoDelProducto<<endl;
}

void imprimeFecha(ostream &arch,int fecha){
    int dd,mm,aa=fecha;
    dd = aa%100;
    aa/=100;
    mm = aa%100;
    aa/=100;
    arch.fill('0');
    arch<<right<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa;
    arch.fill(' ');
}