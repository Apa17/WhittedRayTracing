#ifndef RAY_H
#define RAY_H

#include "vector.h"

struct Ray {
	Vector origen;
	Vector direccion;
	double indRefrac;
};
#endif