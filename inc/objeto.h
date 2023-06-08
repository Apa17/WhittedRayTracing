#ifndef OBJETO_H
#define OBJETO_H

#include "ray.h"
#include "punto.h"
#include <tuple>
using color = std::tuple<double, double, double, double>;
class Objeto {
	public: 
		virtual std::pair<bool, Punto> chequear_colision(Ray rayo) = 0;
		virtual Punto getNormal(Punto punto) = 0;
		double getcoefReflex();
		double getcoefTransm();
		double getindRefrac();
		color getColor();
	protected:
		color Colour;
		double coefReflex;
		double coefTransm;
		double indRefrac;

};

#endif