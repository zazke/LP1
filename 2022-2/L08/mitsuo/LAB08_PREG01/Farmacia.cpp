/* 
 * File:   Farmacia.cpp
 * Author: mitsuo
 * 
 * Created on 27 November 2022, 11:43
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Farmacia.h"
#include "aux.h"

using namespace std;

Farmacia::Farmacia() {
}

Farmacia::Farmacia(const Farmacia& orig) {
}

Farmacia::~Farmacia() {
}


void Farmacia::cargaMedico() {
    ifstream file("../../medicos.csv");
    if (!file) {
        cerr << "Error: can't open file\n";
        return;
    }
    
    int i;
    for (i = 0; this->lmedico[i].read(file); i++)
        ;
}

void Farmacia::leeReceta() {
    ifstream file("../../recetas.csv");
    if (!file) {
        cerr << "Error: can't open file\n";
        return;
    }
    
    int i_sin = 0;
    int i_con = 0;
    char s[MAXLEN];
    char c;
    // paciente
    int pacienteDni;
    char pacienteNombre[MAXLEN];
    // medico
    int medicoId;
    char medicoEsp[MAXLEN];  // to search in lmedico
    // medicamento
    int medicamentoId;
    int medicamentoQty;
    char medicamentoName[MAXLEN];
    while (true) {
        /* needs to "peek" line to determine if medicamento is conreceta or 
         * sinreceta */
        file.getline(s, MAXLEN, ','); // ignore date
        if (file.eof()) break;
        file >> pacienteDni >> c;
        file.getline(pacienteNombre, MAXLEN, ',');
        file >> medicoId;
        this->searchMedico(medicoId, medicoEsp);
        while (file.get() != '\n') {
            /* read medicamentos until '\n' */
            file >> medicamentoId >> c;
            file >> medicamentoQty;
            this->searchMedicamento(medicamentoId, medicamentoName);
            /* (medicamentoId is always 5 digits long */
            if (medicamentoId / 10000 % 2 == 0) {
                /* con receta */
                this->lconreceta[i_con].SetCodigo(medicamentoId);
                this->lconreceta[i_con].SetNombre(medicamentoName);
                this->lconreceta[i_con].SetCantidad(medicamentoQty);
                this->lconreceta[i_con].SetCodmed(medicoId);
                this->lconreceta[i_con].SetEspecialidad(medicoEsp);
                i_con++;
            } else {
                /* sin receta */
                this->lsinreceta[i_sin].SetCodigo(medicamentoId);
                this->lsinreceta[i_sin].SetNombre(medicamentoName);
                this->lsinreceta[i_sin].SetCantidad(medicamentoQty);
                this->lsinreceta[i_sin].SetDni(pacienteDni);
                this->lsinreceta[i_sin].SetPacienteNombre(pacienteNombre);
                i_sin++;
            }
        }
    }
}

void Farmacia::imprimirReceta() {
    ofstream file("reporte.txt");
    if (!file) {
        cerr << "Error: can't open file\n";
        return;
    }
    file << 
"Codigo         Descripcion del Med.                    Cant.   DNI           Nombre\n"
"============================================================================================\n";
    for (int i = 0; this->lsinreceta[i].GetCodigo() != -1; i++) {
        this->lsinreceta[i].write(file);
    }
    
    file << "\n\n\n";
    file << 
"Codigo         Descripcion del Med.                    Cant.   Cod. Medico   Especialidad\n"
"============================================================================================\n";
    for (int i = 0; this->lconreceta[i].GetCodigo() != -1; i++) {
        this->lconreceta[i].write(file);
    }
}

/* return name through `name_out` parameter */
void Farmacia::searchMedicamento(int idTarget, char *name_out) {
    ifstream file("../../medicamentos.csv");
    if (!file) {
        cerr << "Error: can't open file\n";
        return;
    }
    
    char c;
    char s[MAXLEN];
    char name[MAXLEN];
    int id;
    while (file >> id) {
        file >> c;
        file.getline(name, MAXLEN, ',');
        if (id == idTarget) {
            strcpy(name_out, name);
            return;
        }
        file.getline(s, MAXLEN);
    }
    strcpy(name_out, "NO ENCONTRADO");
}


void Farmacia::searchMedico(int idTarget, char *name_out) {
    int i;
    for (i = 0; this->lmedico[i].getCodigo() != -1; i++) {
        if (lmedico[i].getCodigo() == idTarget) {
            strcpy(name_out, lmedico[i].getEspecialidad());
            return;
        }
    }
    strcpy(name_out, "NO ENCONTRADO");
}

