/* 
 * File:   Almacen.h
 * Author: mitsuo
 *
 * Created on 02 December 2022, 12:40
 */

#ifndef ALMACEN_H
#define ALMACEN_H

#include "Arbol.h"

class Almacen {
public:
    Almacen();
    Almacen(const Almacen& orig);
    virtual ~Almacen();
    
    void carga();
    void actualiza();
    void imprime();
private:
    Arbol arbolalma;    // arbol que representa al almacen
};

#endif /* ALMACEN_H */

