/* 
 * File:   Almacen.cpp
 * Author: mitsuo
 * 
 * Created on 02 December 2022, 12:40
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Almacen.h"
#include "Marca.h"
#include "Generico.h"

using namespace std;

Almacen::Almacen() {
}

Almacen::Almacen(const Almacen& orig) {
}

Almacen::~Almacen() {
}


void Almacen::carga() {
    ifstream f("../medicamentos.csv");
    if (!f) {
        cerr << "Error: can't open file medicamentos.csv\n";
        return;
    }
    
    Medicamento * m;
    int tipo; // 0: generico, 1: marca
    
    while (f >> tipo) {
        f.get();
        if (tipo == 0) {
            m = new Generico();
        } else {
            m = new Marca();
        }
        m->lee(f);
        this->arbolalma.insert(m);
//        m->imprime(cout);
    }
}

void Almacen::actualiza() {
    /* incrementar precio si codigo en `recarga.csv` y es de marca */
    
    ifstream f("../recarga.csv");
    if (!f) {
        cerr << "Error: can't open file recarga.csv\n";
        return;
    }
    this->arbolalma.actualiza(f);
}

void Almacen::imprime() {
    ofstream f("report.txt");
    if (!f) {
        cerr << "Error: can't open file report.txt\n";
        return;
    }
    f << 
"                              REPORTE DE MEDICAMENTOS\n"
"=============================================================================================================\n"
" Codigo  Nombre del Medicamento                    Stock  Precio Pais/Laboratorio                       Lote\n"
"=============================================================================================================\n"
//"94459   VALPROATO DE MAGNESIO SUSP                 1980   53.55 ABBOT LABORATORIOS S.A.                 1420"
            ;
    this->arbolalma.print(f);
}

