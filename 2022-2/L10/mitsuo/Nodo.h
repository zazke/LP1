/* 
 * File:   Nodo.h
 * Author: mitsuo
 *
 * Created on 02 December 2022, 12:38
 */

#ifndef NODO_H
#define NODO_H

#include "Medicamento.h"

class Nodo {
public:
    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
private:
    Medicamento * med;
    Nodo * izq;
    Nodo * der;
    
    friend class Arbol;
};

#endif /* NODO_H */

