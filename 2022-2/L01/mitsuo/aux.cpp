/* Auxiliary/helper/reusable functions */

#include <iostream>
#include <iomanip>

#include "aux.h"

using namespace std;

/* "dd/mm/yyyy"  ->  yyyymmdd (int) */
int readdate(istream &is)
{
    char c;
    int d, m, y;

    is >> d >> c
       >> m >> c
       >> y;

    return y * 10000 + m * 100 + d;
}

/* yyyymmdd (int)  ->  "dd/mm/yyyy" */
void writedate(ostream &os, int intdate)
{
    int d, m, y;
    
    d = intdate % 100;
    intdate /= 100;
    m = intdate % 100;
    intdate /= 100;
    y = intdate;
    
    os << WR0(2, 2, y) << '/' 
       << WR0(2, 2, m) << '/' 
       << WR0(2, 2, d) << '\n';
}
