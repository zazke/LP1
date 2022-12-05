/* 
 * File:   Nodo.cpp
 * Author: mitsuo
 * 
 * Created on 02 December 2022, 12:38
 */

#include <iostream>
#include <iomanip>
#include "Nodo.h"

using namespace std;

Nodo::Nodo() {
    this->med = nullptr;
    this->izq = nullptr;
    this->der = nullptr;
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::~Nodo() {
}

