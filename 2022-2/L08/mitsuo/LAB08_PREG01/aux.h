/* 
 * File:   aux.h
 * Author: mitsuo
 *
 * Created on 27 November 2022, 11:48
 */

#ifndef AUX_H
#define AUX_H

// The parenthesis in C/C++ macros are best practice
// https://stackoverflow.com/q/7186504/7498073

// Width-Left (use with strings)
#define WL(w)           " " << setw((w) - 1) << left << setprecision(2) << fixed

// Width-Right (use with numbers)
#define WR(w)           setw(w) << right << setprecision(2) << fixed

// Width-Right-0-padding
#define WR0(w, w0, x)   setw((w) - (w0)) << "" \
                        << setw(w0) << right << setfill('0') \
                        << setprecision(2) << fixed << (x) \
                        << setfill(' ')

// Width-Left-Date (dd/mm/yyyy format)
#define WLD(w, x)       setw((w) - 10) << "" << WR0(2, 2, (x) % 100) \
                        << '/' << WR0(2, 2, (x) / 100 % 100) \
                        << '/' << WR0(4, 4, (x) / 10000)

#define MAXLEN          100

#endif /* AUX_H */

