/* 
 * File:   Medicamento.h
 * Author: mitsuo
 *
 * Created on 27 November 2022, 11:49
 */

#ifndef MEDICAMENTO_H
#define MEDICAMENTO_H

class Medicamento {
public:
    Medicamento();
    Medicamento(const Medicamento& orig);
    virtual ~Medicamento();
    void SetCantidad(int cantidad);
    int GetCantidad() const;
    void SetNombre(const char* nombre);
    char* GetNombre() const;
    void SetCodigo(int codigo);
    int GetCodigo() const;
    
private:
    int codigo;
    char *nombre;
    int cantidad;
    double precio;
    int fecha;
};

#endif /* MEDICAMENTO_H */

