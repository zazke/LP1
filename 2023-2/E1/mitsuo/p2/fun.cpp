#include <iostream>
#include <fstream>
#include <iomanip>

#include <cstdlib>
#include <cstring>
#include "fun.hpp"

using namespace std;

enum Reg {COD, NOM, PRECIO, STOCK};

void cargarProductos(void *&prod, const char *nombArch){
    ifstream in(nombArch);
    if(!in) {
        cerr << "Error: no se pudo abrir archivo\n";
        exit(1);
    }
    void **productos=nullptr;    
    char *cod;
    int nd=0, cap=0;
    while(1){
        cod = leeCad(in,',');
        if(in.eof()) break;
        if(nd==cap) aumentaEspacios(productos,nd,cap);
        guardaProd(in, productos[nd-1], cod);
        nd++;
    }
    prod = productos;
    qsort(prod, nd-1, sizeof(void *), cmpProducto);
}

void aumentaEspacios(void**&productos, int &nd, int &cap){
    void **aux;
    cap += INCREMENTO;
    if(productos==nullptr){
        productos = new void * [cap]{};
        nd=1;
    }
    else{
        aux = new void * [cap]{};
        for(int i=0;i<nd;i++){
            aux[i] = productos[i];
        }
        delete productos;
        productos = aux;
    }
}

char *leeCad(istream &arch, char delim){
    char *cad, buff[80];
    arch.getline(buff,80,delim);
    if(arch.eof()) return nullptr;
    cad = new char [strlen(buff)+1];
    strcpy(cad,buff);
    return cad;
}

void guardaProd(istream &arch, void *&prod, char *cod){
    void **producto = new void *[2]{};
    producto[0] = creaRegProd(arch, cod);
    producto[1] = nullptr;
    prod = producto;
}

void *creaRegProd(istream &arch, char *cod){
    char *nomb;
    double precio;
    int stock;
    void **reg;
    nomb = leeCad(arch,',');
    arch>>precio;
    arch.get();
    arch>>stock;
    arch>>ws;
    reg = new void * [4] {};
    reg[COD] = cod;
    reg[NOM] = nomb;
    reg[PRECIO] = new double (precio);
    reg[STOCK] = new int (stock);
    return reg;
}

int cmpProducto(const void *a, const void *b){
    void **ai = (void**)a, **bi = (void**)b;
    void **duplaA = (void**)(*ai), **duplaB = (void**)(*bi);
    void **regA = (void**)(duplaA[0]), **regB = (void**)(duplaB[0]);
    char *codA = (char *)(regA[0]), *codB = (char*)(regB[0]);
    return strcmp(codA, codB);
}

void pruebaDeCargaDeProductos(void *prod){
    void **productos = (void**)prod;
    ofstream out("PruebaProductos.txt");
    if(!out){
        cout<<"error al abrir archivo PruebaProductos.txt"<<endl;
        exit(1);
    }
    out.precision(2);
    out<<fixed;
    out<<setw(70)<<"REPORTE DE PRUEBA DE PRODUCTOS"<<endl;
    imprimeLinea(out,'=');
    out<<left<<setw(10)<<"CODIGO"<<setw(70)<<"NOMBRE"<<right<<setw(10)<<"PRECIO"
            <<setw(10)<<"STOCK"<<endl;
    for(int i=0;productos[i];i++){
        imprimeProducto(out,productos[i]);
    }
}

void imprimeLinea(ostream &arch,char c){
    for(int i=0;i<110;i++) arch<<c;
    arch<<endl;
}

void imprimeProducto(ostream &arch,void *prod){
    void **producto = (void**)prod;
    imprimeRegistroProducto(arch,producto[0]);
}

void imprimeRegistroProducto(ostream &arch,void *prod){
    void **producto = (void**)prod;
    char *cod = (char*)producto[COD],*nom = (char*)producto[NOM];
    double *precio = (double*)producto[PRECIO];
    int *stock = (int*)producto[STOCK];
    arch<<left<<setw(10)<<cod<<setw(70)<<nom<<right<<setw(10)<<*precio<<setw(9)<<*stock<<endl;
}
