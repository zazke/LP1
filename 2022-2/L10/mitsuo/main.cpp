/* 
 * File:   main.cpp
 * Author: Mitsuo Tokumori - 20170895
 * timestamps: 
 * - 12:30 start
 * - 12:45 classes
 * - 13:00 basic I/O (lee and imprime Medicamento)
 * - 13:08 polymorphism (lee and imprime in derived classes)
 * - 13:15 friend class Arbol (for Nodo) (had issue with friend and "forward declaration error")
 * - 13:38 BST (insert and traverse) (preg1 done)
 * - 13:43 add headers in imprime()
 * - 14:10 actualiza()  (issue with EOF bit set after rewind with seekg()) (preg2 done)
 * totaltime: 1h 40m
 * Created on 02 December 2022, 12:28
 */

#include <cstdlib>
#include <iostream>
#include "Almacen.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Almacen alma;
    
    alma.carga();
    alma.actualiza();       // (preg 2)
    alma.imprime();
    return 0;
}

