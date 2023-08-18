/* 
 * File:   Medico.cpp
 * Author: mitsuo
 * 
 * Created on 27 November 2022, 11:46
 */

#include <iomanip>
#include <iostream>
#include "Medico.h"
#include "aux.h"

using namespace std;

Medico::Medico() {
    this->codigo = -1;
    this->especialidad = new char [MAXLEN];
    this->nombre = new char [MAXLEN];
}

Medico::Medico(const Medico& orig) {
}

Medico::~Medico() {
    delete [] this->especialidad;
    delete [] this->nombre;
}

char* Medico::getEspecialidad() const {
    return especialidad;
}

int Medico::getCodigo() const {
    return codigo;
}

int Medico::read(std::istream & input) {
    char c;
    
    input >> this->codigo >> c;
    input.getline(this->nombre, MAXLEN, ',');
    input.getline(this->especialidad, MAXLEN, '\n');
    return !input.eof();
}

void Medico::write(std::ostream & output) {
    output << WL(8) << this->codigo;
    output << WL(16) << this->especialidad;
}

