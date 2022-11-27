#include <iostream>

void cargapila(void *&pila, void *arreglo);
void push(void *&pila, void *data);
void *pop(void *&pila);
int pilavacia(void *pila);
void imprimepila(
        void *pila, 
        void (*imprimenumero)(std::ostream &out, void *), 
        const char *filename
);
void muevepila(void *pilasrc, void *&piladest);

static void hanoi(int n, void *pila1, void *pila2, void *pila3);
