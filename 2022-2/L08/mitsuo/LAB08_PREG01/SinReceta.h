/* 
 * File:   SinReceta.h
 * Author: mitsuo
 *
 * Created on 27 November 2022, 11:53
 */

#ifndef SINRECETA_H
#define SINRECETA_H

#include <iostream>
#include "Medicamento.h"

class SinReceta : public Medicamento {
public:
    SinReceta();
    SinReceta(const SinReceta& orig);
    virtual ~SinReceta();
    void SetPacienteNombre(const char* nombre);
    char* GetPacienteNombre() const;
    void SetDni(int dni);
    int GetDni() const;
    void write(std::ostream & output);
private:
    int dni;        // pacienteDni
    char *nombre;   // pacienteNombre
};

#endif /* SINRECETA_H */

