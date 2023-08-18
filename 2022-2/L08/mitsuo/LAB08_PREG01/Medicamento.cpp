/* 
 * File:   Medicamento.cpp
 * Author: mitsuo
 * 
 * Created on 27 November 2022, 11:49
 */

#include <cstring>
#include "Medicamento.h"
#include "aux.h"

Medicamento::Medicamento() {
    this->codigo = -1;
    this->nombre = new char [MAXLEN];
}

Medicamento::Medicamento(const Medicamento& orig) {
}

Medicamento::~Medicamento() {
    delete [] this->nombre;
}

void Medicamento::SetCantidad(int cantidad) {
    this->cantidad = cantidad;
}

int Medicamento::GetCantidad() const {
    return cantidad;
}

void Medicamento::SetNombre(const char* nombre) {
    strcpy(this->nombre, nombre);
}

char* Medicamento::GetNombre() const {
    return nombre;
}

void Medicamento::SetCodigo(int codigo) {
    this->codigo = codigo;
}

int Medicamento::GetCodigo() const {
    return codigo;
}
