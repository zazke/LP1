#include "fun.hpp"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

void cargarPedidos(int **&fechaClienteCantidad, char **&codigoDelProducto,
                   const char *archivo) {
    ifstream in(archivo);
    if (!in) {
        cout << "Error: no se pudo abrir archivo\n";
        exit(1);
    }

    fechaClienteCantidad = NULL;
    codigoDelProducto = NULL;
    size_t size = 0;

    char code[MAXLEN];
    int dni, qty, date, dd, mm, yy;

    int i;
    for (i = 0; true; i++) {
        in.getline(code, MAXLEN, ',');
        in >> dni; in.get();
        in >> qty; in.get();
        in >> dd; in.get(); in >> mm; in.get(); in >> yy; in.get();
        date = yy*10000 + mm*100 + dd;
        if (!in) {
            break;
        }

        if (i + 1 >= size) {
            increase_size_productos(fechaClienteCantidad, codigoDelProducto, size);
        }
        
        fechaClienteCantidad[i] = new int [3] {date, dni, qty};
        char * code_mem = new char [strlen(code) + 1]; strcpy(code_mem, code);
        codigoDelProducto[i] = code_mem;

        fechaClienteCantidad[i + 1] = NULL;
    }
    
    qsort_pedidos(fechaClienteCantidad, codigoDelProducto, 0, i - 1);
}

void increase_size_productos(int **&fechaClienteCantidad, char **&codigoDelProducto, size_t &size) {
    if (!fechaClienteCantidad) {
        // init
        size = INCREMENTO;
        fechaClienteCantidad = new int * [size];
        codigoDelProducto = new char * [size];

        fechaClienteCantidad[0] = NULL;
        return;
    }

    // this has O(n^2) time complexity (not good)
    size += INCREMENTO;
    int ** tmp1 = new int * [size];
    char ** tmp2 = new char * [size];

    int i;
    for (i = 0; i < size && fechaClienteCantidad[i]; i++) {
        tmp1[i] = fechaClienteCantidad[i];
        tmp2[i] = codigoDelProducto[i];
    }
    tmp1[i] = NULL;

    delete [] fechaClienteCantidad;
    delete [] codigoDelProducto;
    fechaClienteCantidad = tmp1;
    codigoDelProducto = tmp2;
}
    
void qsort_pedidos(int ** v1, char ** v2, int left, int right) {
    int i, last;

    /* do nothing if array has less than 2 elements */
    if (left >= right)
        return;

    swap_pedidos(v1, v2, left, (left + right) / 2); 
    last = left;

    /* partition */
    for (i = left + 1; i <= right; i++) {
        if (v1[i][0] < v1[left][0]) {
            swap_pedidos(v1, v2, ++last, i);
        }
    }

    swap_pedidos(v1, v2, left, last);        /* reset partition element */
    qsort_pedidos(v1, v2, left, last - 1);
    qsort_pedidos(v1, v2, last + 1, right);

}
void swap_pedidos(int ** v1, char ** v2, int left, int right) {
    int  * t1 = v1[left];
    char * t2 = v2[left];

    v1[left] = v1[right];
    v2[left] = v2[right];

    v1[right] = t1;
    v2[right] = t2;
}

void pruebaDeCargaDePedidos(int **fechaClienteCantidad,
                            char **codigoDelProducto, const char *archivo) {
    ofstream out(archivo);
    if (!out) {
        cout << "Error: no se pudo abrir archivo\n";
        exit(1);
    }
    out << "Fecha           DNI                Cant.    Código producto\n";
    for (int i = 0; fechaClienteCantidad[i]; i++) {
        int date = fechaClienteCantidad[i][0];
        int dni = fechaClienteCantidad[i][1];
        int qty = fechaClienteCantidad[i][2];
        char * code = codigoDelProducto[i];

        out << right << fixed << setprecision(2);
        print_date(out, date);
        out << setw(12) << dni;
        out << setw(12) << qty;
        out << left << "        ";
        out << setw(12) << code;
        out << '\n';
    }
}

void print_date(ostream &out, int date) {
    int yy = date / 10000;
    int mm = date / 100 % 100;
    int dd = date % 100;
    out << setfill('0') << right;
    out << setw(2) << dd << '/';
    out << setw(2) << mm << '/';
    out << setw(4) << yy << "  ";
    out << setfill(' ');
}
