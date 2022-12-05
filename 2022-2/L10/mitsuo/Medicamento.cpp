/* 
 * File:   Medicamento.cpp
 * Author: mitsuo
 * 
 * Created on 02 December 2022, 12:31
 */

#include <iostream>
#include <iomanip>
#include "Medicamento.h"
#include "aux.h"

using namespace std;

Medicamento::Medicamento() {
    this->codigo = -1;
    this->nombre = new char [MAXLEN];
}

Medicamento::Medicamento(const Medicamento& orig) {
}

Medicamento::~Medicamento() {
    delete [] this->nombre;
}

void Medicamento::setPrecio(double precio) {
    this->precio = precio;
}

double Medicamento::getPrecio() const {
    return precio;
}

int Medicamento::getCodigo() const {
    return codigo;
}

int Medicamento::lee(std::istream &input) {
    char c;
    input >> this->codigo >> c;
    input.getline(this->nombre, MAXLEN, ',');
    input >> this->stock >> c;
    input >> this->precio >> c;
    
//    char s[MAXLEN];
//    input.getline(s, MAXLEN);
    
    return !input.eof();
}

void Medicamento::imprime(std::ostream &output) {
    output << WL(8) << this->codigo;
    output << WL(40) << this->nombre;
    output << WR(8) << this->stock;
    output << WR(8) << this->precio;
//    output << '\n';
}


void Medicamento::actualiza(std::istream &input) {
    
}
