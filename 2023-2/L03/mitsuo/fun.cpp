#include <iomanip>
#include <cstring>
#include <algorithm>    // find
#include "fun.hpp"

using namespace std;

void lecturaDeProductos(const char *archivo, char ***&productos, int *&stocks, double *&precios) {
    ifstream in(archivo);
    if (!in) {
        cerr << "Error: no se pudo abrir el archivo.\n";
        exit(1);
    }

    // read (stack memory)
    char code[MAXLEN];
    char description[MAXLEN];
    double price;
    int qty;

    productos = NULL;
    stocks = NULL;
    precios = NULL;
    size_t size = 0;       // size of the parallel arrays

    int i;
    for (i = 0; true; i++) {
        in.getline(code, MAXLEN, ',');
        in.getline(description, MAXLEN, ',');
        in >> price; in.get();
        in >> qty; in.get();
        if (!in) {
            break;
        }

        // memory allocation "por incrementos"
        if (i == size) {
            increase_size_productos(productos, stocks, precios, size);
        }
        productos[i] = crea_producto(code, description);    // "code" is the "Primary Key" of the parallel arrays
        stocks[i] = qty;
        precios[i] = price;
    }
}

void increase_size_productos(char ***& productos, int *& stocks, double *& precios, size_t &size) {
    if (!productos) {
        // init
        size = INCREMENTO;
        productos = new char ** [size];
        stocks = new int [size];
        precios = new double [size];
        
        productos[0] = NULL;
        return;
    }
    /* In LP1 increments are 5 by 5.  This has time complexity N^2 and space 
       complexity N.  On the other hand, exponential increase of array size
       has time complexity n*log(n), with space complexity of N.  Much better. */
    size *= 2;
    char *** productos_tmp = new char ** [size];
    int * stocks_tmp = new int [size];
    double * precios_tmp = new double [size];

    int i;    
    for (i = 0; i < size && productos[i]; i++) {
        productos_tmp[i] = productos[i];
        stocks_tmp[i] = stocks[i];
        precios_tmp[i] = precios[i];
    }
    productos_tmp[i] = NULL;

    delete [] productos;
    delete [] stocks;
    delete [] precios;
    productos = productos_tmp;
    stocks = stocks_tmp;
    precios = precios_tmp;
}

char **crea_producto(char * code, char * description) {
    char * field1 = new char [strlen(code) + 1];
    char * field2 = new char [strlen(description) + 1];

    strcpy(field1, code);
    strcpy(field2, description);

    return new char * [2] {field1, field2};
}

void pruebaDeLecturaDeProductos(const char *archivo, char ***productos, int *stock, double *precios) {
    ofstream out(archivo);
    if (!out) {
        cerr << "Error: no se pudo abrir archivo.\n";
        exit(1);
    }

    char ** producto;
    int i;
    for (i = 0; i < MAX && (producto = productos[i]); i++) {
        out << left;
        out << setw(12) << producto[0];
        out << setw(72) << producto[1];
        out << right << setprecision(2) << fixed;
        out << setw(8) << stock[i];
        out << setw(12) << precios[i];
        out << '\n';
    }
}

void lecturaDePedidos(const char *archivo, int *& fechas, char ***& grouped_producto, int ***& grouped_dniqty) {
    ifstream in(archivo);
    if (!in) {
        cerr << "Error: no se pudo abrir el archivo.\n";
        exit(1);
    }

    int date, dd, mm, yy;
    char code[MAXLEN];
    int dni;
    int qty;

    fechas = NULL;
    grouped_producto = NULL;
    grouped_dniqty = NULL;
    size_t size = 0;            // size of the parallel arrays
    size_t size2[MAX] = {};     // size of internal parallel arrays (level 2)

    int n, i = 0;
    while (true) {
        in.getline(code, MAXLEN, ',');
        in >> dni; in.get();
        in >> qty; in.get();
        in >> dd; in.get(); in >> mm; in.get(); in >> yy; in.get();
        date = yy*10000 + mm*100 + dd;
        if (!in) {
            break;
        }

        // memory allocation "por incrementos"
        if (i == size) {
            increase_size_pedidos(fechas, grouped_producto, grouped_dniqty, size);
        }

        int * dniqty = new int [2] {dni, qty};
        char * code_mem = new char [strlen(code) + 1]; strcpy(code_mem, code);

        insert_pedido(i, date, code_mem, dniqty, fechas, grouped_producto, grouped_dniqty, size2);
    }
    qsort_pedidos(fechas, grouped_producto, grouped_dniqty, 0, i - 1);
}

void increase_size_pedidos(int *& fechas, char ***& grouped_producto, int ***& grouped_dniqty, size_t &size) {
    if (!fechas) {
        // init
        size = INCREMENTO;
        fechas = new int [size];
        grouped_producto = new char ** [size];
        grouped_dniqty = new int ** [size];
        
        fechas[0] = 0;
        return;
    }
    /* In LP1 increments are 5 by 5.  This has time complexity N^2 and space 
       complexity N.  On the other hand, exponential increase of array size
       has time complexity n*log(n), with space complexity of N.  Much better. */
    size *= 2;
    int * f = new int [size];
    char *** gp = new char ** [size];
    int *** gd = new int ** [size];

    int i;    
    for (i = 0; i < size && fechas[i]; i++) {
        f[i] = fechas[i];
        gp[i] = grouped_producto[i];
        gd[i] = grouped_dniqty[i];
    }
    f[i] = 0;

    delete [] fechas;
    delete [] grouped_producto;
    delete [] grouped_dniqty;
    fechas = f;
    grouped_producto = gp;
    grouped_dniqty = gd;
}

void insert_pedido (
        int & n,
        int date, char * code_mem, int * dniqty, 
        int * fechas, char *** grouped_producto, int *** grouped_dniqty,
        size_t * size2
) {
    // find if date is already in the list
    int i;
    for (i = 0; i < n; i++) {
        if (fechas[i] == date) {
            break;
        }
    }
    if (i == n) {
        // new date
        fechas[i] = date;
        grouped_producto[i] = NULL;
        grouped_dniqty[i] = NULL;
        size2[i] = 0;
        fechas[++n] = 0;        // update reference (n) and list terminator (0)
    } 

    // make sure there is space for the product (in the nested list (#2)) before adding it to the date (at `fechas[i]`)
    int i2;
    for (i2 = 0; grouped_producto[i] && grouped_producto[i][i2]; i2++)
        ;
    if (i2 == size2[i]) {
        increase_size_pedidos_fecha(grouped_producto[i], grouped_dniqty[i], size2[i]);
    }
    grouped_producto[i][i2] = code_mem;
    grouped_dniqty[i][i2] = dniqty;
    i2 += 1;
    grouped_producto[i][i2] = NULL;
}

/* qsort: sort v[left]...v[right] into increasing order 

   Quicksort.
   Ref.:
   * The C Programming Language (ANSI C) - pg. 87)
   * https://en.wikipedia.org/wiki/Quicksort
*/
void qsort_pedidos(int * v1, char *** v2, int *** v3, int left, int right) {
    int i, last;

    /* do nothing if array has less than 2 elements */
    if (left >= right)
        return;

    swap_pedidos(v1, v2, v3, left, (left + right) / 2); 
    last = left;

    /* partition */
    for (i = left + 1; i <= right; i++) {
        if (v1[i] < v1[left]) {
            swap_pedidos(v1, v2, v3, ++last, i);
        }
    }

    swap_pedidos(v1, v2, v3, left, last);        /* reset partition element */
    qsort_pedidos(v1, v2, v3, left, last - 1);
    qsort_pedidos(v1, v2, v3, last + 1, right);
}

void swap_pedidos(int * v1, char *** v2, int *** v3, int left, int right) {
    int     t1 = v1[left];
    char ** t2 = v2[left];
    int **  t3 = v3[left];

    v1[left] = v1[right];
    v2[left] = v2[right];
    v3[left] = v3[right];

    v1[right] = t1;
    v2[right] = t2;
    v3[right] = t3;
}

void increase_size_pedidos_fecha(char **& productos, int **& dniqtys, size_t &size) {
    if (!productos) {
        // init
        size = INCREMENTO;
        productos = new char * [size];
        dniqtys = new int * [size];

        productos[0] = NULL;
        return;
    }
    /* In LP1 increments are 5 by 5.  This has time complexity N^2 and space 
       complexity N.  On the other hand, exponential increase of array size
       has time complexity n*log(n), with space complexity of N.  Much better. */
    size *= 2;
    char ** p = new char * [size];
    int ** d = new int * [size];

    int i;    
    for (i = 0; i < size && productos[i]; i++) {
        p[i] = productos[i];
        d[i] = dniqtys[i];
    }
    p[i] = NULL;

    delete [] productos;
    delete [] dniqtys;
    productos = p;
    dniqtys = d;
}

void pruebaDeLecturaDePedidos(const char *archivo, int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos) {
    ofstream out(archivo);
    if (!out) {
        cerr << "Error: no se pudo abrir archivo.\n";
        exit(1);
    }

    int fecha;
    int i, j;
    for (i = 0; i < MAX && (fecha = fechaPedidos[i]); i++) {
        out << "FECHA: " << fecha << '\n';
        char ** productos = codigoPedidos[i];
        int ** dniqtys = dniCantPedidos[i];
        for (j = 0; j < MAX && productos[j]; j++) {
            int dni = dniqtys[j][0];
            int qty = dniqtys[j][1];
            char * code = productos[j];

            out << right << setprecision(2) << fixed;
            out << setw(2) << j + 1 << ") ";
            out << left;
            out << setw(12) << dni;
            out << setw(12) << code;
            out << setw(12) << qty;
            out << '\n';
        }
    }
}

void reporteDeEnvioDePedidos(const char *archivo, 
        char ***productos, int *stocks, double *precios,                     // productos parallel arrays
        int *fechaPedidos, char ***codigoPedidos, int ***dniCantPedidos     // pedidos parallel arrays
) {
    ofstream out(archivo);
    if (!out) {
        cerr << "Error: no se pudo abrir archivo.\n";
        exit(1);
    }

    int fecha;
    int i, j;
    for (i = 0; i < MAX && (fecha = fechaPedidos[i]); i++) {
        int dd = fecha % 100;
        int mm = fecha / 100 % 100;
        int yy = fecha / 10000;
        out << "                                                               REPORTE DE ENTREGA DE PEDIDOS\n"
               "=====================================================================================================================================\n"
        ;
        out << "FECHA: " << dd << "/" << mm << "/" << yy << '\n';
        out << "=====================================================================================================================================\n"
               "No. DNI             Producto                                                                    Cantidad    Precio  Total de ingresos\n"
               "-------------------------------------------------------------------------------------------------------------------------------------\n"
        ;

        char ** pedido_productos = codigoPedidos[i];
        int ** dniqtys = dniCantPedidos[i];

        double served_income = 0;
        double not_served_income = 0;
        for (j = 0; j < MAX && pedido_productos[j]; j++) {
            int dni = dniqtys[j][0];
            int qty = dniqtys[j][1];
            char * code = pedido_productos[j];

            int i_product = busca_producto(productos, code);
            char * name = productos[i_product][1];
            int * stock = &stocks[i_product];
            double price = precios[i_product];

            int qty_served;
            if (*stock >= qty) {
                qty_served = qty;
                *stock -= qty;
            } else {
                qty_served = *stock;
                *stock = 0;
            }
            served_income += qty_served * price;
            not_served_income += (qty - qty_served) * price;

            out << right << setprecision(2) << fixed;
            out << setw(2) << j + 1 << ") ";
            out << left;
            out << setw(12) << dni;
            out << setw(12) << code;
            out << setw(64) << name;
            out << right << setprecision(2) << fixed;
            out << setw(12) << qty_served;
            out << setw(12) << price;
            if (qty_served == 0) {
                out << left;
                out << setw(12) << "  SIN STOCK";
            } else {
                out << setw(12) << price * qty_served;
            }
            out << '\n';
        }
        out << right << setprecision(2) << fixed;
        out << "-------------------------------------------------------------------------------------------------------------------------------------\n";
        out << "Total ingresado: " << served_income << '\n';
        out << "Total perdido por falta de stock: " << not_served_income << '\n';
    }
}

int busca_producto(char *** productos, char * producto) {
    for (int i = 0; productos[i]; i++) {
        if (strcmp(productos[i][0], producto) == 0) {
            return i;
        }
    }
    return -1;

}