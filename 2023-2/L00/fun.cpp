#include <iostream>     // I/O basico (left, right, hex, oct, [no]uppercase, showbase)
#include <iomanip>      // manipuladores (setw, setprecision, setfill)
#include <iostream>
#include <cstring>
#include "fun.h"

#define MAXLEN 100

using namespace std;

void leer_datos_escribir_reporte(std::istream& in, std::ostream& out) {
    int sum_qty;
    double sum_price;   // (price * qty)

    char code[MAXLEN];
    char book_name[MAXLEN];
    char author_name[MAXLEN];
    int qty;
    double unit_price;
    char c;     // dummy

    sum_qty = 0;
    sum_price = 0.0;
    print_header(out);
    int i;
    for (i = 0; true; i++) {
        // read
        in.getline(code, MAXLEN, ',');
        in.getline(book_name, MAXLEN, ',');
        in.getline(author_name, MAXLEN, ',');
        in >> qty;
        in >> c;
        in >> unit_price;
        in.ignore(MAXLEN, '\n');
        if (!in) {
            break;
        }
        // process
        to_upper_cstring_inplace(book_name);
        sum_qty += qty;
        sum_price += qty * unit_price;

        // write
        out << setw(2) << right << setfill('0') << i + 1 << ") ";
        out << left << setfill(' ');
        out << setw(8) << code;
        out << setw(32) << uppercase << book_name;
        out << setw(32) << author_name;
        out << right << setprecision(2) << fixed;
        out << setw(4) << qty;
        out << setw(4) << ' ';
        out << setw(8) << unit_price;
        out << '\n';
    }

    out << "\n\n";
    out << "Total cantidad libros: " << sum_qty << '\n';
    out << "Total valor libros: " << sum_price << '\n';
}

void print_header(ostream& out) {
    // 8    32      32      4       8
    out <<    "No.  Codigo  Nombre                          Autor                           Cant.   Precio   \n";
    out <<    "----------------------------------------------------------------------------------------------\n";
}

void to_upper_cstring_inplace(char * s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = toupper(s[i]);
    }
}