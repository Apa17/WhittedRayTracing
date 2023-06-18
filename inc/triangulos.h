#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "objeto.h"
#include "punto.h"

class Triangulo : public Objeto {
	private:
        Punto a;
        Punto b;
        Punto c;
        Punto normal;
	public:
		Triangulo(Punto a, Punto b, Punto c, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Punto> chequear_colision(Ray rayo);
		Punto getNormal(Punto punto);
};
#endif 