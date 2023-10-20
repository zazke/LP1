#ifndef FUN_HPP
#define FUN_HPP

#include <iostream>

#define MAXLEN      100
#define INCREMENTO  5

void cargarPedidos(int **&fechaClienteCantidad, char **&codigoDelProducto, const char *archivo);
void increase_size_productos(int **&fechaClienteCantidad, char **&codigoDelProducto, size_t &size);

void qsort_pedidos(int ** v1, char ** v2, int left, int right);
void swap_pedidos(int ** v1, char ** v2, int left, int right);

void pruebaDeCargaDePedidos(int **fechaClienteCantidad, char **codigoDelProducto, const char *archivo);
void print_date(std::ostream &out, int date);

#endif /* FUN_HPP */