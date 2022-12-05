/* 
 * File:   Arbol.h
 * Author: mitsuo
 *
 * Created on 02 December 2022, 12:40
 */

#ifndef ARBOL_H
#define ARBOL_H

#include "Nodo.h"
#include "Medicamento.h"
#include <iostream>

class Arbol {
public:
    Arbol();
    Arbol(const Arbol& orig);
    virtual ~Arbol();
    
    void insert(Medicamento * m);
    void print(std::ostream &output);
    void actualiza(std::istream &input);
private:
    Nodo * raiz;        // BST sorted by codigo (Medicamento)
    
    void print_rec(Nodo * nodo, std::ostream &output);
    void actualiza_rec(Nodo * nodo, std::istream &input);
};

#endif /* ARBOL_H */

