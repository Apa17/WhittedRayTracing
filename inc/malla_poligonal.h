#ifndef MALLA_H
#define MALLA_H

#include "objeto.h"
#include "punto.h"
#include "triangulos.h"

class Malla_Poligonal : public Objeto {
	private:
		std::vector<Triangulo> poligonos;
	public:
		Malla_Poligonal(std::vector<Triangulo> poligonos, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Punto> chequear_colision(Ray rayo);
		Punto getNormal(Punto punto);
		Color getColor();
		void Print();
};
#endif 