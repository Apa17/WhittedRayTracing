#ifndef OBJETO_H
#define OBJETO_H

#include "ray.h"
#include "punto.h"
#include <tuple>

class Objeto {
	public: 
		virtual std::pair<bool, Punto> chequear_colision(Ray rayo) = 0;
	private: 
};

#endif