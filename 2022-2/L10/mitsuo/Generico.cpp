/* 
 * File:   Generico.cpp
 * Author: mitsuo
 * 
 * Created on 02 December 2022, 12:35
 */

#include <iostream>
#include <iomanip>
#include "Generico.h"
#include "aux.h"

using namespace std;

Generico::Generico() {
    this->pais = new char [MAXLEN];
}

Generico::Generico(const Generico& orig) {
}

Generico::~Generico() {
    delete [] this->pais;
}

int Generico::lee(std::istream &input) {
    this->Medicamento::lee(input);
    input.getline(this->pais, MAXLEN, '\n');
    
    return !input.eof();
}

void Generico::imprime(std::ostream &output) {
    this->Medicamento::imprime(output);
    output << WL(40) << this->pais;
    output << '\n';
}
