#ifndef fecha_h
#define fecha_h
#include <iostream>
#include <string>

using namespace std;
typedef time_t tFecha;

tFecha fechaActual();
string stringFecha(tFecha fecha, bool hora);
#endif