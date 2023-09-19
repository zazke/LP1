#include <iostream>
#include <fstream>

#define MAXLEN 100

using namespace std;

typedef struct {int i;} custom1_t;
typedef struct {int i;} custom2_t;

/* Usando ostream (stream) (good) */
ostream& operator<<(ostream& os, custom1_t rhs) {
    return os << "stream";
}

/* Usando oftream (file) (bad) */
ofstream& operator<<(ofstream& os, custom2_t rhs) {
    //return os << "file";        /* compiler complains */
    os << "file";
    return os;
}

int main() {
    ofstream out("report.txt");
    if (!out) {
        cerr << "Error: no se pudo abrir el archivo\n";
        return 1;
    }
    custom1_t t1 = {0};       // use stream
    custom2_t t2 = {0};       // use fstream

    out << t1 << "PUCP" << '\n';
    out << "PUCP" << t1 << '\n';

    out << t2 << "PUCP" << '\n';
    // out << "PUCP" << t2 << '\n';  // breaks

    return 0;
}
