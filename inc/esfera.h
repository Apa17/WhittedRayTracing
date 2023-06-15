#ifndef ESFERA_H
#define ESFERA_H

#include "objeto.h"
#include "punto.h"
#include <tuple>

class Esfera : public Objeto {
	private:
		double radio;
		Punto centro;
	public:
		Esfera(double radio, Punto centro, Color colorDifuso, Color colorEspecular, double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Punto> chequear_colision(Ray rayo);
		Punto getNormal(Punto punto);
		Color getColor();
};
#endif 