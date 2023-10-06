#ifndef FUN_HPP
#define FUN_HPP

#define MAX     1000
#define MAXLEN  100

void cargaproductos(void *& productos);
void cargaclientes(void *& clientes);
void cargapedidos(void *& productos, void * clientes);
void imprimereporte(void * clientes);

void imprimeproductos(void * productos);
void imprimeclientes(void * clientes);
void ** busca_cliente(void * clientes, int dni);
void ** busca_producto(void * productos, char * code);
void agrega_pedido(void * pedidos, void * pedido);
void trim_cliente_pedidos(void * clientes);

#endif  /* FUN_HPP */