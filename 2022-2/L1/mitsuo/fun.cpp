/* Functions are written in the in order as I write them 
 * (following "Diseño desendente"). */

#include <iostream>
#include <iomanip>
#include <cstring>  /* strlen, strcpy, strcmp, strcat */
#include <cctype>   /* toupper */

#include "fun.h"
#include "aux.h"


using namespace std;

/* Input 
 * ===== */

void readRecordsWriteReport() 
{
    char esp1[MAXLEN], esp2[MAXLEN];
    int curDate; // current date

    // (counters)
    int med1Qty, pac1Qty, medVen1Qty;
    int med2Qty, pac2Qty, medVen2Qty;
    med1Qty = pac1Qty = medVen1Qty = 0;
    med2Qty = pac2Qty = medVen2Qty = 0;

    // Header
    cin >> esp1 >> esp2;
    curDate = readdate(cin);
    writeHeader(esp1, esp2, curDate);

    // Medicos
    readWriteMedicos(curDate,
        esp1, med1Qty, pac1Qty, medVen1Qty,
        esp2, med2Qty, pac2Qty, medVen2Qty
    );

    // Resumen (counters)
    // (Hasta antes de agregar esta parte de los contadores el archivo era de
    // menos de 170 lineas, luego con el resumen y pasando LAS 10 VARIABLES
    // necesarias para contar, se incremento el numero de lineas a 267.  Esta
    // parte se puede dejar para el final, y sin pasar todas esas variables en
    // un inicio porque son tantas que marea y hace cualquier edicion mas
    // dificil.  Es dificil estimar pero todo esto de los contadores debe valer
    // unos 5 hasta 8 puntos.)
    writeformattedResumen(
            esp1, med1Qty, pac1Qty, medVen1Qty,
            esp2, med2Qty, pac2Qty, medVen2Qty
    );
}

/* Basic Output
 * ============
 * 
 * (mixed with more input, this is often the LP1 way processing text) */

void writeHeader(char *esp1, char *esp2, int curDate) 
{
    cout << 
"                                           EMPRESA PRESTADORA DE SALUD\n"
"========================================================================================================================\n"
"ESPECIALIDADES A VERIFICAR: " << esp1 << " Y " << esp2 << '\n' << 
"FECHA DEL PROCESO: "
        ;
    writedate(cout, curDate);
    cout << '\n';
}

void readWriteMedicos(
        int curDate,
        char *esp1, int &med1Qty, int &pac1Qty, int &medVen1Qty,
        char *esp2, int &med2Qty, int &pac2Qty, int &medVen2Qty
) {
    char id[MAXLEN], name[MAXLEN], esp[MAXLEN];
    for (int i = 0; cin >> id >> name; i++) {
        separateNameEsp(name, esp);
        writeformattedMedico(id, name, esp);

        // Pacientes
        readWritePacientes(
                curDate,
                esp,
                esp1, pac1Qty, medVen1Qty,
                esp2, pac2Qty, medVen2Qty
        );

        // (counters)
        if (strcmp(esp1, esp) == 0) {
            med1Qty++;
        } else if (strcmp(esp2, esp) == 0) {
            med2Qty++;
        }
    }
}

void readWritePacientes(
        int curDate,
        char *esp,
        char *esp1, int &pac1Qty, int &medVen1Qty,
        char *esp2, int &pac2Qty, int &medVen2Qty
) {
    /* The trick here is that every Paciente begins with a number.  So input
     * will fail when there is no more Pacientes.  Then clear the fail flag to
     * resume with next Medico */
    char name[MAXLEN];
    int dni, qty;
    int medVenCnt;      // medVenCnt

    medVenCnt = 0;
    for (int i = 0; cin >> dni >> name >> qty; i++) {
        writeformattedPaciente(i+1, dni, name);

        // Medicina
        readWriteMedicinas(qty,
                medVenCnt,
                curDate,
                esp,
                esp1, medVen1Qty,
                esp2, medVen2Qty
        );

        // (counters)
        if (strcmp(esp1, esp) == 0) {
            pac1Qty++;
        } else if (strcmp(esp2, esp) == 0) {
            pac2Qty++;
        }
    }
    cin.clear();

    // (almost hidden mini summary)
    cout << WL(4 + 12 + 20 + 12) << "";
    cout << "Cantidad de medicamentos vencidos: " << medVenCnt
        << '\n';
}

void readWriteMedicinas(int n,
        int &medVenCnt,
        int curDate,
        char *esp,
        char *esp1, int &medVen1Qty,
        char *esp2, int &medVen2Qty
) {
    char name[MAXLEN];
    int id, venDate;

    for (int i = 0; i < n; i++) {
        cin >> id >> name; 
        venDate = readdate(cin);

        writeformattedMedicina(i, id, name, venDate, n, curDate);

        // (counters)
        if (curDate > venDate) {
            medVenCnt++;

            if (strcmp(esp1, esp) == 0) {
                medVen1Qty++;
            } else if (strcmp(esp2, esp) == 0) {
                medVen2Qty++;
            }
        }
    }
}

/* Formatted output 
 * ================ */

// Una vez con los datos leidos. Verificando que el ultimo medico y medicina se
// leen bien.  Se procede a tratar de formatear la salida.

// I usually like the output being 80 columns (characters) wide, with "tabstops"
// every 4 columns.  But this output is huge so I'll go with 120 columns.
// Defining and sticking with some kind of standard makes the process more
// straightforward and faster.
// https://en.wikipedia.org/wiki/Tab_stop

void writeformattedMedico(char *id, char *name, char *esp)
{
    cout << 
"========================================================================================================================\n"
"Medico: " << name << " [" << id << "]             Especialidad: " << esp << '\n' <<
"------------------------------------------------------------------------------------------------------------------------\n"
"       Pacientes atendidos                                 Medicinas recibidas\n"
"------------------------------------------------------------------------------------------------------------------------\n"
// a small offset "to center" the table headers
"  " 

// 4 12         20                  12          8       32                              12          12       (col)
// 1 3          5                   3           2       8                               3           3        (tabstops)
"    DNI         Nombre              Cantidad    Codigo  Descripcion                     FV          Observacion \n"
"------------------------------------------------------------------------------------------------------------------------\n"
    ;
}

void writeformattedPaciente(int i, int id, char *name)
{
    cout << WR0(3, 2, i) << ")" 
         << WR(12) << id
         << WL(20) << name;
}

void writeformattedMedicina(int i, int id, char *name, int venDate, int qty,
        int curDate
) {
    char obs[MAXLEN] = "";

    if (curDate > venDate)
        strcpy(obs, "VENCIDO");

    if (i == 0) {
        cout << WL(12) << qty;
    } else {
        cout << WL(4 + 12 + 20 + 12) << "";
    }

    cout << WR(8) << id
         << WL(32) << name
         << WL(12) << venDate
         << WL(12) << obs
         << '\n';
}

// Resumen final

void writeformattedResumen(
        char *esp1, int med1Qty, int pac1Qty, int medVen1Qty,
        char *esp2, int med2Qty, int pac2Qty, int medVen2Qty)
{
    cout << 
"========================================================================================================================\n"
         << "RESUMEN\n";
    writeformattedResumenLine(esp1, med1Qty, pac1Qty, medVen1Qty);
    writeformattedResumenLine(esp2, med2Qty, pac2Qty, medVen2Qty);
    cout << 
"========================================================================================================================\n"
        ;
}

void writeformattedResumenLine(
        char *esp, int medQty, int pacQty, int medVenQty)
{
    strcat(esp, ": ");
    cout << "Especialidad" 
         << WL(16) << esp
         << WR0(2, 2, medQty) << " medicos, "
         << WR0(2, 2, pacQty) << " pacientes, "
         << WR0(2, 2, medVenQty) << " medicinas vencidas."
         << '\n';
}

/* Problem specific helper functions 
 * =================================*/

void separateNameEsp(char *name, char *esp)
{
    int i;

    for (i = strlen(name); i > 0; i--) {
        if (name[i] == '_')
            break;
    }
    name[i] = '\0';

    strcpy(esp, &name[i+1]);
    for (i = 0; esp[i] != '\0'; i++) {
        esp[i] = toupper(esp[i]);
    }
}
