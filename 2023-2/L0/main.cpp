// Just an example of I/O with files for INF281
// Compile with: clang++ -g main.cpp fun.cpp && ./a.out
// Mitsuo 2023-08-17

#include <iostream>
#include <fstream>      // archivos

#include "fun.h"

using namespace std;

int main(int argc, char ** argv) {
    ifstream in("Libros.csv");
    if (!in) {
        cerr << "Error: No se pudo abrir archivo\n";
    }
    ofstream out("reporte.txt");
    leer_datos_escribir_reporte(in, out);
    return 0;
}

