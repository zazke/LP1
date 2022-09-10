/* Functions are written in the in order as I implement them. 
 * "Diseño desendente" */

#include <iostream>
#include <iomanip>
#include <cstring>      // strcmp
                       
#include "fun.h"

using namespace std;

void readRecordsWriteReport() 
{
    char esp1[MAXLEN], esp2[MAXLEN], strfecha[MAXLEN];

    // Header
    cin >> esp1 >> esp2 >> strfecha;
    writeHeader(esp1, esp2, strfecha);

    // Medicos
    readWriteMedicos();
}

void writeHeader(char *esp1, char *esp2, char *strfecha) 
{
    cout << 
"                       EMPRESA PRESTADORA DE SALUD\n"
"================================================================================\n"
"ESPECIALIDADES A VERIFICAR: " << esp1 << " Y " << esp2 << '\n' << 
"FECHA DEL PROCESO: " << strfecha << '\n' << 
"================================================================================\n"
        ;
    // Note: formatting strfecha to (dd/mm/yyyy) is a lot of work for little
    //       benefit.  Do later.
}

void readWriteMedicos()
{
    char id[MAXLEN], name[MAXLEN];
    while (cin >> id >> name) {
        //cout << "Medico: " << id << name << '\n';
        writeformattedMedico(id, name);

        // Pacientes
        readWritePacientes();
    }
}

void readWritePacientes() 
{
    /* The trick here is that every Paciente begins with a number.  So input
     * will fail when there is no more Pacientes.  Then clear the fail flag to
     * resume with next Medico */
    char name[MAXLEN];
    int dni, qty;
    while (cin >> dni >> name >> qty) {
        //cout << " Paciente: " << dni << name << qty << '\n';
        writeformattedPaciente(10, dni, name);

        // Medicina
        readWriteMedicinas(qty);
    }
    cin.clear();
}

void readWriteMedicinas(int n) 
{
    char name[MAXLEN], strfecha[MAXLEN];
    int id;
    while (n--) {
        cin >> id >> name >> strfecha;

        //cout << "  Medicina: " << id << name << strfecha <<  '\n';
        writeformattedMedicina(2, id, name, strfecha, n);
    }
}

// Una vez con los datos leidos. Verificando que el ultimo medico y medicina se
// leen bien.  Se procede a tratar de formatear bien la salida.

void writeformattedMedico(char *id, char *name)
{
    char esp[MAXLEN] = "Ginecologia";
    cout << 
"Medico: " << name << "[" << id << "]             Especialidad: " << esp << '\n' <<
"--------------------------------------------------------------------------------\n"
"   Pacientes atendidos                             Mediciinas recibidas\n"
"--------------------------------------------------------------------------------\n"
"   DNI      Nombre         Cantidad Codigo     Descripcion       FV        Obs. \n"
"--------------------------------------------------------------------------------\n"
    ;
}

void writeformattedPaciente(int i, int id, char *name)
{
    cout << i << ") " << id << " " << name << " ";
}

void writeformattedMedicina(int i, int id, char *name, char *strfecha, int qty)
{
    char obs[MAXLEN] = "VENCIDO";

    if (i != 0) {
        cout << 
"                                   ";
    } else {
        cout << qty << " ";
    }

    cout << id << " " << name << " " << strfecha << " " << obs << '\n';
}

// TODO: formatting + resumen
