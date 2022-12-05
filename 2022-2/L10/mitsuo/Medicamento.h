/* 
 * File:   Medicamento.h
 * Author: mitsuo
 *
 * Created on 02 December 2022, 12:31
 */

#ifndef MEDICAMENTO_H
#define MEDICAMENTO_H

#include <iostream>

class Medicamento {
public:
    Medicamento();
    Medicamento(const Medicamento& orig);
    virtual ~Medicamento();
    void setPrecio(double precio);
    double getPrecio() const;
    
    int getCodigo() const;
    
    virtual int lee(std::istream &input);
    virtual void imprime(std::ostream &output);
    virtual void actualiza(std::istream &input);
private:
    int codigo;
    char * nombre;
    int stock;
    double precio;
};

#endif /* MEDICAMENTO_H */

