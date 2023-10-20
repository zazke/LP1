#ifndef FUN_HPP
#define FUN_HPP

#include <iostream>

#define MAXLEN      100
#define INCREMENTO  5

void cargarProductos(void *& productos, const char * archivo);
void pruebaDeCargaDeProductos(void * productos);

int cmp_productos(const void *lhs, const void *rhs);
void increase_size_productos(void **& ps, size_t &size);

#endif /* FUN_HPP */