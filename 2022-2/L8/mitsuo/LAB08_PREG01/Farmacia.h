/* 
 * File:   Farmacia.h
 * Author: mitsuo
 *
 * Created on 27 November 2022, 11:43
 */

#ifndef FARMACIA_H
#define FARMACIA_H

#include "Medico.h"
#include "SinReceta.h"
#include "ConReceta.h"

#define MAXITEMS 1000

class Farmacia {
public:
    Farmacia();
    Farmacia(const Farmacia& orig);
    virtual ~Farmacia();
    
    void cargaMedico();
    void leeReceta();
    void imprimirReceta();
    
    void searchMedicamento(int idTarget, char *name_out);
    void searchMedico(int idTarget, char *name_out);
private:
    Medico lmedico[MAXITEMS];
    ConReceta lconreceta [MAXITEMS];
    SinReceta lsinreceta [MAXITEMS];
};

#endif /* FARMACIA_H */

