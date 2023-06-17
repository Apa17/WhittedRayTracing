#ifndef RAY_H
#define RAY_H

#include "punto.h"

struct Ray {
	Punto origen;
	Punto direccion;
	double indRefrac;
};
#endif