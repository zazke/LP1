/* Static libraries are not portable, and I'm using a Linux system, so I wont
   be using the supplied static library.

   clang++ -std=c++11 -g *.cpp
*/

#include "fun.hpp"
// #include "MuestraPunteros.h"

int main(int argc, char ** argv) {
    void * productos, * clientes;
    cargaproductos(productos);
    imprimeproductos(productos);

    cargaclientes(clientes);
    imprimeclientes(clientes);

    cargapedidos(productos, clientes);
    imprimereporte(clientes);
    return 0;
}

