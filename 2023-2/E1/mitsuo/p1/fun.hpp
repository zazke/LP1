#ifndef FUN_HPP
#define FUN_HPP

#include <iostream>

void cargarPedidos(int **&fechaClienteCantidad, char **&codigoDelProducto, const char *nombArch);
char *leeCad(std::istream &arch, char delim);
void aumentaEspacios(int **&fechaClienteCantidad, char **&codigoDelProducto, int &nd, int &cap);
void guardaPed(std::istream &arch, int *&fechaClienteCantidad, char *&codigoDelProducto, char *cod);
int leeFecha(std::istream &arch);
void qSort(int **fechaClienteCantidad, char **codigoDelProducto, int izq, int der);
void cambiar(int *&fechaClienteI,char *&codigoDelProductoI,int *&fechaClienteK,char *&codigoDelProductoK);
bool desorden(int *fechaClienteCantidadI, int *fechaClienteCantidadK);
void pruebaDeCargaDePedidos(int **fechaClienteCantidad, char **codigoDelProducto, const  char *nombArch);
void imprimeLinea(std::ostream &arch,char c);
void imprimePedido(std::ostream &arch,int *fechaClienteCantidad, char *codigoDelProducto);
void imprimeFecha(std::ostream &arch,int fecha);

#endif /* FUN_HPP */