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

using namespace std;
char * leeCad(ifstream &arch, char delim='\n');
void cargaCodNomProducto(ifstream &arch, char **&buffProd, char *codProd);
void imprimePedidos(ofstream &arch, char **producto, double stock, double precio);
void leeDatos(ifstream &arch, int &dni, int &cant, int &fecha);
int buscaFecha(int *buffFecha, int fecha);
void cargaPedido(char **buffCodPed, char *codPed, int **&buffdniCant, 
        int dni, int cant, int &numPed);
int buscaPedido(char **buffCodPed, char *codPed);
void sumaCantidad(int *buffdniCant, int cant);
void guardaCliente(int *buffdniCant, int dni, int cant);
void espaciosExactos(char **&codigoPedidos, int numPed);
void espaciosExactos(int **&dniCantPed, int numPed);
void imprimePedidos(ofstream &arch, char **codPed, int **dniCant);
void imprimeCliente(ofstream &arch, int *cliente);
void imprimeRepPedidos(ofstream &arch, char **codigoPedidos, int **dniCantPedidos,char ***prod, int *stock, 
        double *precios, double &parcialIng, double &parcialFalta);
void imprimePedido(ofstream &arch, char *codPed, char **prod, int &stock,
                double precio, int *dniCantPed, double &parcialIng, double &parcialFalta);
void imprimeLinea(ofstream &arch, char c);
int buscaProd(char ***prod, char *codProd);

#endif /* FUN_HPP */