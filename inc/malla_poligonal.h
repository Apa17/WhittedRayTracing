#ifndef MALLA_H
#define MALLA_H

#include "objeto.h"
#include "punto.h"
#include "triangulos.h"

class Malla_Poligonal : public Objeto {
	private:
		Triangulo** poligonos;
        int cantidad_triangulos;
	public:
		Malla_Poligonal(Triangulo** poligonos, int cantidad_triangulos,Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Punto> chequear_colision(Ray rayo);
		Punto getNormal(Punto punto);
		Color getColor();
};
#endif 