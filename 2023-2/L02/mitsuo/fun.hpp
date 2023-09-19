#ifndef FUN_HPP
#define FUN_HPP

#include <iostream>
#include <fstream>

#define MAX             1000
#define MAXLEN          100

void lecturaDeProductos(const char *archivo, char ***&productos, int *&stock, double *&precios);
void pruebaDeLecturaDeProductos(const char *archivo, char ***productos, int *stock, double *precios);
void lecturaDePedidos(const char *archivo, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos);
void pruebaDeLecturaDePedidos(const char *archivo, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);
void reporteDeEnvioDePedidos(const char *archivo, char ***productos, int *stocks, double *precios, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos);
void agrega_pedidos_fecha(
        int fecha, char **& pedido_producto, int **& pedido_dniqty, 
        int * fechas, char ** productos, int ** dniqtys, 
        int n);

char **crea_producto(char * code, char * description);
int busca_producto(char *** productos, char * producto);

#endif /* FUN_HPP */