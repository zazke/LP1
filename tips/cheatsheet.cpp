/* Cheatsheet.  Useful basic code to have around for this course. */

// -----------------------------------------------------------------------------

#ifndef FUN_HPP /* fun.hpp */
#define FUN_HPP

#define MAX     1000
#define MAXLEN  100

void qsort(int * v, int left, int right);
void swap(int * v, int left, int right);

#endif /* FUN_HPP */

// -----------------------------------------------------------------------------

#include <iostream>
#include <fstream>

using namespace std;

/* qsort: sort v[left]...v[right] into increasing order 

   Quicksort.
   Ref.:
   * The C Programming Language (ANSI C) - pg. 87)
   * https://en.wikipedia.org/wiki/Quicksort
*/
void qsort(int * v, int left, int right) {
    int i, last;

    /* do nothing if array has less than 2 elements */
    if (left >= right)
        return;

    swap(v, left, (left + right) / 2); 
    last = left;

    /* partition */
    for (i = left + 1; i <= right; i++) {
        if (v[i] < v[left]) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);        /* reset partition element */
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(int * v, int left, int right) {
    int t = v[left];
    v[left] = v[right];
    v[right] = t;
}


/* insertion sort (optional) */

/* memoria dinamica, metodo exacto */

/* memoria dinamica, metodo por incrementos */
/* UNTESTED*/
void lectura_pedidos_metodo_incrementos(void * pedidos) {
    // open file stream

    // read in "buffers" (stack memory)

    // write to heap memory
}

int main() {
    return 0;
}