/* Stream manipulator macros
 * ========================= */

// The parenthesis in C/C++ macros are best practice
// https://stackoverflow.com/q/7186504/7498073

// string 
// (add space in front to separate adjacent right-aligned and left-aligned
// fields)
#define WL(w)           " " << setw((w)-1) << left << setprecision(2) << fixed

// number
#define WR(w)           setw(w) << right << setprecision(2) << fixed

// number with some 0-padding part (e.g., a code)
#define WR0(w, w0, x)   setw((w) - (w0)) << "" \
                        << setw(w0) << right << setfill('0') \
                        << setprecision(2) << fixed << (x) \
                        << setfill(' ')


/* Project definitions */

#define MAXLEN 100      // fixed length strings


/* Function declarations */

int readdate(std::istream &is);
void writedate(std::ostream &os, int intdate);
