#ifndef FUN_HPP
#define FUN_HPP

#include <cstdint>
#include <iostream>
#include <fstream>

#define MAX             1000
#define MAXLEN          100
#define INCREMENTO      10


void lecturaDeProductos(const char *archivo, char ***&productos, int *&stock, double *&precios);
void pruebaDeLecturaDeProductos(const char *archivo, char ***productos, int *stock, double *precios);
void lecturaDePedidos(const char *archivo, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos);
void pruebaDeLecturaDePedidos(const char *archivo, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);
void reporteDeEnvioDePedidos(const char *archivo, char ***productos, int *stocks, double *precios, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);

void increase_size_productos(char ***& productos, int *& stocks, double *& precios, size_t &size);
void increase_size_pedidos(int *& fechas, char ***& grouped_producto, int ***& grouped_dniqty, size_t &size);
void increase_size_pedidos_fecha(char **& productos, int **& dniqtys, size_t &size);
char **crea_producto(char * code, char * description);
int busca_producto(char *** productos, char * producto);
void insert_pedido(
        int & n,
        int date, char * code_mem, int * dniqty, 
        int * fechas, char *** grouped_producto, int *** grouped_dniqty,
        size_t * size2
);
void qsort_pedidos(int * v1, char *** v2, int *** v3, int left, int right);
void swap_pedidos(int * v1, char *** v2, int *** v3, int left, int right);

#endif /* FUN_HPP */