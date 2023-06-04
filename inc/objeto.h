#ifndef OBJETO_H
#define OBJETO_H

#include "ray.h"
#include "punto.h"

class Objeto {
	public: 
		virtual std::pair<bool, Punto> chequear_colision(Punto posicion_camara, Ray rayo);
	private: 
};

#endif OBJETO_H