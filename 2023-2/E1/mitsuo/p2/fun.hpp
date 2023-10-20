#ifndef FUN_HPP
#define FUN_HPP

#include <iostream>

#define MAX         1000
#define MAXLEN      100
#define INCREMENTO  5

void cargarProductos(void *&prod, const char *nombArch);
void aumentaEspacios(void**&productos, int &nd, int &cap);
char *leeCad(std::istream &arch, char delim);
void guardaProd(std::istream &arch, void *&prod, char *cod);
void *creaRegProd(std::istream &arch, char *cod);
int cmpProducto(const void *a, const void *b);
void pruebaDeCargaDeProductos(void *prod);
void imprimeLinea(std::ostream &arch,char c);
void imprimeProducto(std::ostream &arch,void *prod);
void imprimeRegistroProducto(std::ostream &arch,void *prod);

#endif /* FUN_HPP */