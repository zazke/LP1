/* 
 * File:   Arbol.cpp
 * Author: mitsuo
 * 
 * Created on 02 December 2022, 12:40
 */

#include <iostream>
#include <iomanip>
#include "Arbol.h"

using namespace std;

Arbol::Arbol() {
    this->raiz = nullptr;
}

Arbol::Arbol(const Arbol& orig) {
}

Arbol::~Arbol() {
}


void Arbol::insert(Medicamento * m) {
    Nodo * nodo = new Nodo;
    Nodo ** walk = &this->raiz;

    nodo->med = m;
    
    while (*walk) {
        if (m->getCodigo() < (*walk)->med->getCodigo()) {
            walk = &(*walk)->izq;
        } else {
            walk = &(*walk)->der;
        }
    }
    *walk = nodo;
}

void Arbol::print(std::ostream &output) {
    this->print_rec(this->raiz, output);
}

void Arbol::print_rec(Nodo * nodo, std::ostream &output) {
    /* in order */
    if (!nodo) {
        return;
    }
    this->print_rec(nodo->izq, output);
    nodo->med->imprime(output);
    this->print_rec(nodo->der, output);
}


void Arbol::actualiza(std::istream &input) {
    this->actualiza_rec(this->raiz, input);
}

void Arbol::actualiza_rec(Nodo * nodo, std::istream &input) {
    /* in order */
    if (!nodo) {
        return;
    }
    this->actualiza_rec(nodo->izq, input);
    nodo->med->actualiza(input);
    this->actualiza_rec(nodo->der, input);
}
