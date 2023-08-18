#include <iostream>

#define MAXLEN      100

int cmpnumero(const void *p1, const void *p2);
int *leenumero(std::istream &in);
void cargaarreglo(void *&arreglo,
    int (*cmpnumero)(const void *, const void *), 
    int *leenumero(std::istream &in), 
    const char *filename);
void imprimenumero(std::ostream &out, void *data);