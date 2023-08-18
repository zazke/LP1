#include <iostream>
#include <fstream>
#include <typeinfo>

#define MAXLEN 100

using namespace std;

/* Usando ostream (stream) */
typedef struct {
    int id;
    const char name[MAXLEN];
} student1_t;

ostream& operator<<(ostream& os, student1_t rhs) {
    os << "Student name: " << rhs.name;
    return os;
}

/* Usando oftream (file) */
typedef struct {
    int id;
    const char name[MAXLEN];
} student2_t;

ofstream& operator<<(ofstream& os, student2_t rhs) {
    os << "Student name: " << rhs.name;
    return os;
}

int main() {
    ofstream out("report.txt");
    if (!out) {
        cerr << "Error: no se pudo abrir el archivo\n";
        return 1;
    }
    student1_t student1 = {1, "Ana Ambooken"};
    student2_t student2 = {2, "Bob Banana"};

    out << student1 << "PUCP" << '\n';  // works
    out << "PUCP" << student1 << '\n';  // works

    out << student2 << "PUCP" << '\n';  // works
    /* out << "PUCP" << student2 << '\n';  // breaks */

    return 0;
}
