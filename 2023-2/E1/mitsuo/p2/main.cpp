#include "fun.hpp"

int main(int argc, char** argv) {
    void *productos;
    cargarProductos(productos, "../../Productos.csv");
    pruebaDeCargaDeProductos(productos);
    return 0;
}