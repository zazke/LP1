#include <iostream>
#include <fstream>
#include "BibliotecaPilaGenerica.h"

using namespace std;

/* NEXT: (void *), DATA: (int *) */
enum nodeIndices { NEXT, DATA };

void cargapila(void *&pila, void *arreglo)
{
    int i;
    int **numbers = (int **) arreglo;
    pila = nullptr;
    for (i = 0; numbers[i]; i++) {
        push(pila, numbers[i]);
    }
}

void push(void *&pila, void *data)
{
    void **node = new void * [2];
    node[NEXT] = pila;
    node[DATA] = data;
    pila = node;
}

void *pop(void *&pila)
{
    void **node;
    if (pila == nullptr) {
        return nullptr;
    } else {
        node = (void **) pila;
        pila = node[NEXT];
        return node[DATA];
    }
}

int pilavacia(void *pila)
{
    return pila == nullptr;
}

void imprimepila(
        void *pila, 
        void (*imprimenumero)(ostream &out, void *), 
        const char *filename
) {
    ofstream out(filename);
    if (!out) {
        cerr << "Error: no se pudo abrir archivo\n";
    }
    void **next;
    void **node;
    int data;

    next = (void **) pila;
    while (next) {
        node = (void **) next;
        imprimenumero(out, node[DATA]);

        next = (void **) node[NEXT];
    }
}

/* hanoi */
void muevepila(void *pilasrc, void *&piladest)
{
    void *pilaaux = nullptr;

    /* count elements */
    int i = 0;
    void **next = (void **) pilasrc;
    while (next) {
        next = (void **) *next;
        i++;
    }
    // cout << "n = " << i << '\n';
    hanoi(i, pilasrc, nullptr, piladest);
}

static void hanoi(int n, void *pila1, void *pila2, void *pila3)
{
    /* FIXME: I don't know where it's the bug.  Here or in pop().  Also the stack
     * representation different from what is asked in the problem statement */
    void *data;
    if (n == 0) {
        return;
    } else if (n == 1) {
        data = pop(pila1);
        push(pila3, data);
    } else {
        hanoi(n - 1, pila1, pila3, pila2);
        data = pop(pila1);
        push(pila3, data);
        hanoi(n - 1, pila2, pila1, pila3);
    }
}
