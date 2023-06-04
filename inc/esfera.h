#ifndef ESCENA_H
#define ESCENA_H

#include "objeto.h"
#include "punto.h"
#include <tuple>

class Esfera : public Objeto {
	private:
		double radio;
		Punto centro;
	public:
		std::pair<bool, Punto> chequear_colision(Punto posicion_camara, Ray rayo);
};
#endif 