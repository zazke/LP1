/* 
 * File:   Marca.h
 * Author: mitsuo
 *
 * Created on 02 December 2022, 12:36
 */

#ifndef MARCA_H
#define MARCA_H

#include "Medicamento.h"

class Marca : public Medicamento {
public:
    Marca();
    Marca(const Marca& orig);
    virtual ~Marca();
    
    int lee(std::istream &input);
    void imprime(std::ostream &output);
    void actualiza(std::istream &input);
private:
    int lote;
    char * laboratorio;
};

#endif /* MARCA_H */

