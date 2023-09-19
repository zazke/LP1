#include <iomanip>
#include <cstring>
#include <algorithm>    // find
#include "fun.hpp"

using namespace std;

void lecturaDeProductos(const char *archivo, char ***&productos, int *&stock, double *&precios) {
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

    char **productos_tmp[MAX];
    int stock_tmp[MAX];
    double precio_tmp[MAX];

    int i;
    for (i = 0; i < MAX; i++) {
        in.getline(code, MAXLEN, ',');
        in.getline(description, MAXLEN, ',');
        in >> price; in.get();
        in >> qty; in.get();
        if (!in) {
            break;
        }

        productos_tmp[i] = crea_producto(code, description);    // this is the "Primary Key" of the parallel arrays
        stock_tmp[i] = qty;
        precio_tmp[i] = price;
    }

    // write (heap memory)
    int n = i + 1;      // "null terminated list"
    productos = new char ** [n];
    stock = new int [n];
    precios = new double [n];

    for (i = 0; i < n; i++) {
        productos[i] = productos_tmp[i];
        stock[i] = stock_tmp[i];
        precios[i] = precio_tmp[i];
    }
    productos[i] = NULL;
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

void lecturaDePedidos(const char *archivo, int *&fechaPedidos, char ***&codigoPedidos, int ***&dniCantPedidos) {
    ifstream in(archivo);
    if (!in) {
        cerr << "Error: no se pudo abrir el archivo.\n";
        exit(1);
    }

    int date, dd, mm, yy;
    char code[MAXLEN];
    int dni;
    int qty;

    // read (stack memory)
    int fechas[MAX];
    char * productos[MAX];  // code array
    int * dniqtys[MAX];   // dni + qty array

    int n, i;
    for (i = 0; i < MAX; i++) {
        in.getline(code, MAXLEN, ',');
        in >> dni; in.get();
        in >> qty; in.get();
        in >> dd; in.get(); in >> mm; in.get(); in >> yy; in.get();
        date = yy*10000 + mm*100 + dd;
        if (!in) {
            break;
        }

        // First load data in arrays.  Then group by date.
        fechas[i] = date;        // "PK"
        productos[i] = new char [strlen(code) + 1]; strcpy(productos[i], code);
        dniqtys[i] = new int [2] {dni, qty};
    }
    n = i;

    // aggregate by date
    int grouped_fecha_tmp[MAX];
    char ** grouped_producto_tmp[MAX];
    int ** grouped_dniqty_tmp[MAX];

    /* Loop over the dates, then look for all occurrences of a date in 
       `agrega_pedidos_fecha`.  Store already processed dates.
       (this is required because you need to know how many orders are in a 
       specific date, in order to allocate memory)
       
       Another strategy could be to first sort the 3 parallel arrays. And then
       Add the products to a date, until the date changes.

       On second thought, the report only makes sence if the dates are sorted
       (doesn't make much serve the orders in seaminly random order, but
       it also doesn't make sence that the Pedidos.csv is randomly shuffled,
       should come in-order).  Lab 3 is exactly the same but now with 
       "metodo por incrementos", and the professors commented that they 
       made a similar exercise in class and they grouped by dates "in-order"
       (insertion sort).
    */
    int fechas_procesadas[MAX];       // ignore already processed dates
    int n_procesadas = 0;
    int i_grouped = 0;
    for (i = 0; i < n; i++) {
        int fecha = fechas[i];
        if (find(fechas_procesadas, fechas_procesadas + n_procesadas, fecha) != fechas_procesadas + n_procesadas) {
            // already processed date
            continue;
        }

        grouped_fecha_tmp[i_grouped] = fecha;
        agrega_pedidos_fecha(fecha, 
                grouped_producto_tmp[i_grouped], grouped_dniqty_tmp[i_grouped], 
                fechas, productos, dniqtys, n);
        i_grouped += 1;

        fechas_procesadas[n_procesadas++] = fecha;
    }

    // write (heap memory)
    n = i_grouped;
    fechaPedidos = new int [n + 1];
    codigoPedidos = new char ** [n + 1];
    dniCantPedidos = new int ** [n + 1];

    for (i = 0; i < n; i++) {
        fechaPedidos[i] = grouped_fecha_tmp[i];
        codigoPedidos[i] = grouped_producto_tmp[i];
        dniCantPedidos[i] = grouped_dniqty_tmp[i];
    }
    fechaPedidos[i] = 0;
}

/* agrega todos los pedidos de una determinada fecha en los arreglos paralelos */
void agrega_pedidos_fecha(
        int fecha, char **& pedido_producto, int **& pedido_dniqty, 
        int * fechas, char ** productos, int ** dniqtys, 
        int n)
{
    int i;
    char * productos_tmp[MAX];
    int * dniqtys_tmp[MAX];
    int j = 0;      // numero de pedidos para una fecha
    for (i = 0; i < n; i++) {
        if (fecha == fechas[i]) {
            productos_tmp[j] = productos[i];
            dniqtys_tmp[j] = dniqtys[i];
            j += 1;
        }
    }
    int n_pedidos = j;
    pedido_producto = new char * [n_pedidos + 1];
    pedido_dniqty = new int * [n_pedidos + 1];

    for (i = 0; i < n_pedidos; i++) {
        pedido_producto[i] = productos_tmp[i];
        pedido_dniqty[i] = dniqtys_tmp[i];
    }
    pedido_producto[i] = NULL;
    pedido_dniqty[i] = NULL;
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
                qty_served = max(*stock - qty, 0);
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
            out << setw(12) << qty;
            out << setw(12) << price;
            if (*stock == 0) {
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