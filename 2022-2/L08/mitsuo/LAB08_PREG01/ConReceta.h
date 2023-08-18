/* 
 * File:   ConReceta.h
 * Author: mitsuo
 *
 * Created on 27 November 2022, 11:51
 */

#ifndef CONRECETA_H
#define CONRECETA_H

#include <iostream>
#include "Medicamento.h"

class ConReceta : public Medicamento {
public:
    ConReceta();
    ConReceta(const ConReceta& orig);
    virtual ~ConReceta();
    void SetEspecialidad(const char* especialidad);
    char* GetEspecialidad() const;
    void SetCodmed(int codmed);
    int GetCodmed() const;
    void write(std::ostream &);
private:
    int codmed;         // medicoId
    char *especialidad; // medicoEsp
};

#endif /* CONRECETA_H */

