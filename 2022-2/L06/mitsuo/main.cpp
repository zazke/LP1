/* Mitsuo Tokumori 20170895 */

#include <iostream>

#include "BibliotecaPilaGenerica.h"
#include "PilaConEnteros.h"
#include "PilaConRegistros.h"
#include "fun.h"

using namespace std;

int main(int argc, char **argv) 
{
  void *arreglo, *pilaini, *pilafin;

  cargaarreglo(arreglo, cmpnumero, leenumero, "numeros.txt");
  cargapila(pilaini, arreglo);
  muevepila(pilaini, pilafin);
  imprimepila(pilafin, imprimenumero, "repnumeros.txt");
//   imprimepila(pilafin, imprimenumero, "repnumeros.txt");

//   cargaarreglo(arreglo, cmpregistro, leeregistro, "medicinas.csv");
//   cargapila(pilaini, arreglo);
//   muevepila(pilaini, pilafin);
//   imprimepila(pilafin, imprimeregistro, "repmedicinas.txt");
  return 0;
}