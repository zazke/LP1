#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "fun.h"

using namespace std;

void cargaarreglo(void *&arreglo,
    int (*cmpnumero)(const void *, const void *), 
    int *leenumero(istream &in), 
    const char *filename) 
{
    ifstream in(filename);

    if (!in) {
        cerr << "Error, no se pudo abrir archivo\n";
        return;
    }

    int **numbers;
    int *data;
    int *buffer[MAXLEN];
    int i;
    /* load buffer */
    for (i = 0; (data = leenumero(in)); i++) {
        buffer[i] = data;
    }
    buffer[i] = nullptr;

    /* create "exact" array of pointers to int */
    numbers = new int * [i + 1];
    for (i = 0; buffer[i]; i++) {
        numbers[i] = buffer[i];
    }
    numbers[i] = nullptr;

    /* sort array */

    qsort(numbers, i, sizeof(void *), cmpnumero);

    // for (i = 0; numbers[i]; i++) {
    //     cout << *numbers[i] << '\n';
    // }

    /* modify parameter reference */
    arreglo = numbers;
}

/* qsort comparisong function.  Descending order */
int cmpnumero(const void *p1, const void *p2) 
{
    return - (** (int **) p1 - ** (int **) p2);
}

/* allocates memory */
int *leenumero(istream &in) 
{
    int n;
    if (in >> n)
        return new int{n};
    else
        return nullptr;
}

void imprimenumero(ostream &out, void *data) 
{
    cout << * (int *) data << '\n';
}
