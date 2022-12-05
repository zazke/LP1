/* 
 * File:   Generico.h
 * Author: mitsuo
 *
 * Created on 02 December 2022, 12:35
 */

#ifndef GENERICO_H
#define GENERICO_H

#include "Medicamento.h"

class Generico : public Medicamento {
public:
    Generico();
    Generico(const Generico& orig);
    virtual ~Generico();
    
    int lee(std::istream &input);
    void imprime(std::ostream &output);
private:
    char * pais;
};

#endif /* GENERICO_H */

