#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include "fun.hpp"

using namespace std;

void cargaproductos(void *& productos) {
    ifstream in("../Productos2.csv");
    if (!in) {
        cerr << "Error: no se puedo abrir archivo\n";
    }
    char code[MAXLEN];
    char desc[MAXLEN];
    double price;
    char uses_credit;   // S|N (yes or no)

    // "metodo exacto"
    void * productos_tmp[MAX];

    int i;
    for (i = 0; true; i++) {
        in.getline(code, MAXLEN, ',');
        in.getline(desc, MAXLEN, ',');
        in >> price; in.get();
        in >> uses_credit; in.get();
        if (!in) {
            break;
        }
        void ** producto = new void * [4];
        // 0: code, 1: desc, 2: price, 3: uses_credit
        producto[0] = new char [strlen(code) + 1]; strcpy((char *) producto[0], code);
        producto[1] = new char [strlen(desc) + 1]; strcpy((char *) producto[1], desc);
        producto[2] = new double {price};
        producto[3] = new char {uses_credit};
        productos_tmp[i] = producto;
    }
    productos_tmp[i++] = NULL;
    int n = i;
    productos = new void * [n]; 
    for (i = 0; i < n; i++) {
        ((void **) productos)[i] = productos_tmp[i];
    }
}

void imprimeproductos(void * productos) {
    cout << "PRODUCTOS: \n";
    void ** ps = (void **) productos;
    for (int i = 0; ps[i]; i++) {
        void ** p = (void **) ps[i];
        cout << left;
        cout << setw(12) << (char *) p[0];
        cout << setw(64) << (char *) p[1];
        cout << right << fixed << setprecision(2);
        cout << setw(8) << * (double *) p[2];
        cout << setw(8) << * (char *) p[3];
        cout << '\n';
    }
}

void cargaclientes(void *& clientes) {
    ifstream in("../Clientes2.csv");
    if (!in) {
        cerr << "Error: no se puedo abrir archivo\n";
    }
    int     dni;
    char    name[MAXLEN];
    char    phonenumber[MAXLEN];    // not used
    void *  pedidos = NULL;
    double  credit;

    // "metodo exacto"
    void * clientes_tmp[MAX];

    int i;
    for (i = 0; true; i++) {
        in >> dni; in.get();
        in.getline(name, MAXLEN, ',');
        in.getline(phonenumber, MAXLEN, ',');
        in >> credit; in.get();
        if (!in) {
            break;
        }
        void ** cliente = new void * [4];
        // 0: dni, 1: name, 2: pedidos, 3: credit
        cliente[0] = new int {dni};
        cliente[1] = new char [strlen(name) + 1]; strcpy((char *) cliente[1], name);
        cliente[2] = new void * {NULL};
        cliente[3] = new double {credit};
        clientes_tmp[i] = cliente;
    }
    clientes_tmp[i++] = NULL;
    int n = i;
    clientes = new void * [n]; 
    for (i = 0; i < n; i++) {
        ((void **) clientes)[i] = clientes_tmp[i];
    }
}

void imprimeclientes(void * clientes) {
    cout << "CLIENTES: \n";
    void ** cs = (void **) clientes;
    for (int i = 0; cs[i]; i++) {
        void ** c = (void **) cs[i];
        cout << left;
        cout << setw(12) << * (int *) c[0];
        cout << setw(64) << (char *) c[1];

        // void ** pedidos = (void **) c[2];

        cout << right << fixed << setprecision(2);
        cout << setw(8) << * (double *) c[3];
        cout << '\n';
    }
}

void cargapedidos(void *& productos, void * clientes) {
    ifstream in("../Pedidos2.csv");
    if (!in) {
        cerr << "Error: no se puedo abrir archivo\n";
    }
    char    code[MAXLEN];           // product code
    int     dni;
    int     qty;

    int i;
    for (i = 0; true; i++) {
        in.getline(code, MAXLEN, ',');
        in >> dni; in.get();
        in >> qty; in.get();
        if (!in) {
            break;
        }

        // 1. Search the client
        void ** c = busca_cliente(clientes, dni);
        // 0: dni, 1: name, 2: pedidos, 3: credit
        double & credit = * (double *) c[3];
        void *& pedidos = c[2];
        if (!pedidos) {
            // "metodo exacto": first use a buffer of certain size, then trim it.
            pedidos = new void * [MAX];
            ((void **) pedidos)[0] = NULL;
        }

        // 2. Before adding the pedido, a check must be done
        void ** p = busca_producto(productos, code);
        // 0: code, 1: desc, 2: price, 3: uses_credit
        double price = * (double *) p[2];
        char uses_credit = * (char *) p[3];
        double total_cost = qty * price;
        if (uses_credit == 'S') {
            if (credit < total_cost) {
                // not enough credit
                continue;
            }
            credit -= total_cost;
        }
        
        void ** pedido = new void * [3];
        // 0: product code, 1: order qty, 2: total (qty * price)
        pedido[0] = new char [strlen(code) + 1]; strcpy((char *) pedido[0], code);
        pedido[1] = new int {qty};
        pedido[2] = new double {total_cost};
        agrega_pedido(pedidos, pedido);        // appends pedido to the list
    }

    // trim extra spaces ("metodo exacto")
    trim_cliente_pedidos(clientes);
}

void trim_cliente_pedidos(void * clientes) {
    int i, j;
    void ** cs = (void **) clientes;
    for (i = 0; cs[i]; i++) {
        void ** c = (void **) cs[i];
        void ** pedidos = (void **) c[2];
        if (!pedidos) {
            continue;
        }
        // get length
        for (j = 0; pedidos[j]; j++)
            ;
        int n = j;
        // create new array and transfer items
        void ** pedidos_tmp = new void * [n + 1];
        for (j = 0; pedidos[j]; j++) {
            pedidos_tmp[j] = pedidos[j];
        }
        pedidos_tmp[j] = NULL;
        // delete old array and update cliente
        // delete [] pedidos;
        /* NOTE: crashes while freeing memory of pedidos of client with i=16 (dni=71984468), 
                 I have no idea why.  Idk, using `void *` in this way is so
                 tedious to debug that I'll just leave this comment here and
                 move on.  If somebody every figures this out please let me know. */
        c[2] = pedidos_tmp;
    }
}

void ** busca_cliente(void * clientes, int dni) {
    void ** cs = (void **) clientes;
    for (int i = 0; cs[i]; i++) {
        void ** c = (void **) cs[i];
        int c_dni = * (int *) c[0];
        if (c_dni == dni) {
            return c;
        }
    }
    return NULL;
}

void ** busca_producto(void * productos, char * code) {
    void ** ps = (void **) productos;
    for (int i = 0; ps[i]; i++) {
        void ** p = (void **) ps[i];
        char * p_code = (char *) p[0];
        if (strcmp(p_code, code) == 0) {
            return p;
        }
    }
    return NULL;
}

void agrega_pedido(void * pedidos, void * pedido) {
    void ** peds = (void **) pedidos;
    int i;
    for (i = 0; i < MAX && peds[i]; i++)
        ;
    if (i == MAX) {
        cerr << "ERROR: STACK OVERFLOW\n";
    }
    peds[i++] = pedido;
    peds[i] = NULL;
}

void imprimereporte(void * clientes) {
    ofstream out("ReporteDePedidos.txt");
    if (!out) {
        cerr << "Error: no se pudo abrir archivo para reporte\n";
    }
    void ** cs = (void **) clientes;
    for (int i = 0; cs[i]; i++) {
        void ** c = (void **) cs[i];
        // 0: dni, 1: name, 2: pedidos, 3: credit
        int dni = * (int *) c[0];
        char * name = (char *) c[1];
        void ** pedidos = (void **) c[2];
        double credit = * (double *) c[3];
        out << 
            "===========================================================================================================\n"
            "DNI         Nombre                                                          Credito\n"
            ;
        out << left;
        out << setw(12) << dni;
        out << setw(64) << name;
        out << right << fixed << setprecision(2);
        out << setw(8) << credit;
        out << '\n';

        out << 
            "-----------------------------------------------------------------------------------------------------------\n"
            "Pedidos atendidos:\n"
            "-----------------------------------------------------------------------------------------------------------\n"
            "Codigo      Cantidad    Total\n"
            "-----------------------------------------------------------------------------------------------------------\n"
            ;
        for (int j = 0; pedidos[j]; j++) {
            void ** pedido = (void **) pedidos[j];
            // 0: product code, 1: order qty, 2: total (qty * price)
            char * code = (char *) pedido[0];
            int qty = * (int *) pedido[1];
            double total_cost = * (double *) pedido[2];

            out << left;
            out << setw(12) << code;
            out << setw(12) << qty;
            out << setw(12) << total_cost;
            out << '\n';
        }
    }
}