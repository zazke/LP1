/* Notes:
   Igual que L02 pero esta vez con asignacion de memoria por incrementos

   Arreglos paralelos con data de productos y pedidos de clientes.  Se usan
   "pseudo estructuras" (arreglos o matrices) para evaluar manejo de punteros
   con doble y triple indireccion (Ver 
   https://en.wikipedia.org/wiki/Pointer_(computer_programming)#Multiple_indirection).
   Lo que convierte esta tarea relativamente simple (e.g., usando SQL o Python), 
   mucho mas compleja de implementar.

   $ clang++ -std=c++11 -g *.cpp && lldb a.out
*/

#include "fun.hpp"

int main(int argc, char** argv) {
    char ***productos, ***codigoPedidos;
    int *stock, *fechaPedidos, ***dniCantPedidos;
    double *precios;
    
    lecturaDeProductos("../Productos.csv", productos, stock, precios);
    pruebaDeLecturaDeProductos("ReporteDeProductos.txt", productos, stock, precios);

    lecturaDePedidos("../Pedidos.csv", fechaPedidos, codigoPedidos, dniCantPedidos);
    pruebaDeLecturaDePedidos("ReporteDePedidos.txt", fechaPedidos, codigoPedidos, dniCantPedidos);
    reporteDeEnvioDePedidos("ReporteDeEntregaDePedisos.txt", productos, stock, precios, fechaPedidos, codigoPedidos, dniCantPedidos);

    pruebaDeLecturaDeProductos("ReporteDeProductosFinal.txt", productos, stock, precios);
    
    return 0;
}

