/* 
 * File:   Marca.cpp
 * Author: mitsuo
 * 
 * Created on 02 December 2022, 12:36
 */

#include <iostream>
#include <iomanip>
#include "Marca.h"
#include "aux.h"

using namespace std;

Marca::Marca() {
    this->laboratorio = new char [MAXLEN];
}

Marca::Marca(const Marca& orig) {
}

Marca::~Marca() {
    delete [] this->laboratorio;
}

int Marca::lee(std::istream &input) {
    this->Medicamento::lee(input);
    input.getline(this->laboratorio, MAXLEN, ',');
    input >> this->lote;
    
    return !input.eof();
}

void Marca::imprime(std::ostream &output) {
    this->Medicamento::imprime(output);
    output << WL(40) << this->laboratorio;
    output << WL(8) << this->lote;
    output << '\n';
}

void Marca::actualiza(std::istream &input) {
    input.clear();
    input.seekg(0);  // rewind
   
    int codigo;
    while (input >> codigo) {
        if (codigo == this->getCodigo()) {
            this->setPrecio(this->getPrecio() * 1.2);
        }
    }
}
