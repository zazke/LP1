/* 
 * File:   ConReceta.cpp
 * Author: mitsuo
 * 
 * Created on 27 November 2022, 11:51
 */

#include <cstring>
#include <iomanip>
#include "ConReceta.h"
#include "aux.h"

using namespace std;

ConReceta::ConReceta() {
    this->especialidad = new char [MAXLEN];
}

ConReceta::ConReceta(const ConReceta& orig) {
}

ConReceta::~ConReceta() {
    delete [] this->especialidad;
}

void ConReceta::SetEspecialidad(const char* especialidad) {
    strcpy(this->especialidad, especialidad);
}

char* ConReceta::GetEspecialidad() const {
    return especialidad;
}

void ConReceta::SetCodmed(int codmed) {
    this->codmed = codmed;
}

int ConReceta::GetCodmed() const {
    return codmed;
}

void ConReceta::write(std::ostream & output) {
    output << WL(12) << this->GetCodigo();
    output << WL(40) << this->GetNombre();
    output << WR(8) << this->GetCantidad();
    output << WL(12) << this->codmed;
    output << WL(20) << this->especialidad;
    output << '\n';
}
