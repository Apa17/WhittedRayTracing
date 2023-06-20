#ifndef ESFERA_H
#define ESFERA_H

#include "objeto.h"
#include "vector.h"
#include <tuple>

class Esfera : public Objeto {
	private:
		double radio;
		Vector centro;
	public:
		Esfera(double radio, Vector centro, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Vector> chequear_colision(Ray rayo);
		Vector getNormal(Vector vector);
		void Print();
};
#endif 