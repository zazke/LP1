#include "fun.hpp"

int main(int argc, char** argv) {
    char** codigoDelProducto;
    int** fechaClienteCantidad;

    cargarPedidos(fechaClienteCantidad, codigoDelProducto, "../../Pedidos.csv");
    pruebaDeCargaDePedidos(fechaClienteCantidad, codigoDelProducto, "PruebaPedidos.txt");
    return 0;
}