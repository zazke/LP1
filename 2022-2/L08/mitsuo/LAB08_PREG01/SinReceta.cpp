/* 
 * File:   SinReceta.cpp
 * Author: mitsuo
 * 
 * Created on 27 November 2022, 11:53
 */

#include <cstring>
#include <iomanip>
#include "SinReceta.h"
#include "aux.h"

using namespace std;

SinReceta::SinReceta() {
    this->nombre = new char [MAXLEN];
}

SinReceta::SinReceta(const SinReceta& orig) {
}

SinReceta::~SinReceta() {
    delete [] this->nombre;
}

void SinReceta::SetPacienteNombre(const char* nombre) {
    strcpy(this->nombre, nombre);
}

char* SinReceta::GetPacienteNombre() const {
    return nombre;
}

void SinReceta::SetDni(int dni) {
    this->dni = dni;
}

int SinReceta::GetDni() const {
    return dni;
}

void SinReceta::write(std::ostream & output) {
    output << WL(12) << this->GetCodigo();
    output << WL(40) << this->GetNombre();
    output << WR(8) << this->GetCantidad();
    output << WL(12) << this->dni;
    output << WL(20) << this->nombre;
    output << '\n';
}
