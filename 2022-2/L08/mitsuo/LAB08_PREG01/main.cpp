/* 
 * File:   main.cpp
 * Author: mitsuo
 * timestamps: 
 * - 11:15 (start)
 * - 11:35 read enunciado
 * - 11:58 boilerplate classes done
 * - 12:23 read medicos (slow)
 * - 13:24 read sinreceta and conreceta (also print test)
 * - 13:28 print report
 * - 13:40 search medicamento name
 * - 13:43 search medico specialty (end pregunta1)
 * - 13:48 copy project (end pregunta2) (literally the same)
 * 
 * total time: 2h 33m
 *
 * Created on 27 November 2022, 11:32
 */

#include <iostream>
#include <cstdlib>
#include "Farmacia.h"

using namespace std;

/* - Leer medicos
 * - Leer recetas (dependiendo del primer digito del medicamento, 
 *   sera con receta o sin receta)
 *   - Buscar nombre de medicamento en medicamentos.csv
 *   - Si es con receta busca en lmedicos (medicoId, medicoEsp)
 * - Imprimir sinreceta y luego conreceta.
 */
int main(int argc, char** argv) {
    Farmacia ofarma;
    
    ofarma.cargaMedico();
    ofarma.leeReceta();
    ofarma.imprimirReceta();
    return 0;
}

