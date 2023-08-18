/* 
 * File:   Medico.h
 * Author: mitsuo
 *
 * Created on 27 November 2022, 11:46
 */

#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>

class Medico {
public:
    Medico();
    Medico(const Medico& orig);
    virtual ~Medico();
    char* getEspecialidad() const;
    int getCodigo() const;
    
    int read(std::istream & input);
    void write(std::ostream & output);
private:
    int codigo;
    char *nombre;
    char *especialidad;
};

#endif /* MEDICO_H */

