#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "fun.hpp"

using namespace std;

void cargarProductos(void *& productos, const char * archivo) {
    ifstream in(archivo);
    if (!in) {
        cout << "Error: no se pudo abrir archivo\n";
        exit(1);
    }
    void ** ps = NULL;
    size_t size = 0;

    char code[MAXLEN];
    char desc[MAXLEN];
    double price;
    int stock;

    int i;
    for (i = 0; true; i++) {
        in.getline(code, MAXLEN, ',');
        in.getline(desc, MAXLEN, ',');
        in >> price; in.get();
        in >> stock; in.get();
        if (!in) {
            break;
        }

        if (i + 1 >= size) {
            increase_size_productos(ps, size);
        }

        char * code_mem = new char [strlen(code) + 1]; strcpy(code_mem, code);
        char * desc_mem = new char [strlen(desc) + 1]; strcpy(desc_mem, desc);
        
        void ** p1 = new void * [4] {code_mem, desc_mem, new double {price}, new int {stock}};
        void ** p2 = new void * [2] {p1, NULL};

        ps[i] = p2;
        ps[i + 1] = NULL;
    }
    
// at the end of the iteration ps[i] == NULL
    qsort(ps, i - 1, sizeof(void *), cmp_productos);
    productos = ps;
}

int cmp_productos(const void *lhs, const void *rhs) {
    // (nasty)
    char * s1 = (char *)(*(void ****) lhs)[0][0];
    char * s2 = (char *)(*(void ****) rhs)[0][0];
    return strcmp(s1, s2);
}

void increase_size_productos(void **& ps, size_t &size) {
    if (!ps) {
        // init
        size = INCREMENTO;
        ps = new void * [size];

        ps[0] = NULL;
        return;
    }

    // this has O(n^2) time complexity (not good)
    size += INCREMENTO;
    void ** ps_tmp = new void * [size];

    int i;
    for (i = 0; i < size && ps[i]; i++) {
        ps_tmp[i] = ps[i];
    }
    ps_tmp[i] = NULL;

    delete [] ps;
    ps = ps_tmp;
}

void pruebaDeCargaDeProductos(void * productos) {
    ofstream out("PruebaProductos.txt");
    if (!out) {
        cout << "Error: no se pudo abrir archivo\n";
        exit(1);
    }

    void ** ps = (void **) productos;

    out << "Codigo      Descripcion                                                         Precio          Stock\n";
    for (int i = 0; ps[i]; i++) {
        void ** p2 = (void **) ps[i];
        void ** p1 = (void **) p2[0];
        char * code = (char *) p1[0];
        char * desc = (char *) p1[1];
        double * price = (double *) p1[2];
        int * stock = (int *) p1[3];

        out << left;
        out << setw(12) << code;
        out << setw(64) << desc;
        out << right << fixed << setprecision(2);
        out << setw(12) << *price;
        out << setw(12) << *stock;
        out << '\n';
    }
}