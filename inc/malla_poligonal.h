#ifndef MALLA_H
#define MALLA_H

#include "objeto.h"
#include "vector.h"
#include "triangulos.h"

class Malla_Poligonal : public Objeto {
	private:
		std::vector<Triangulo> poligonos;
	public:
		Malla_Poligonal(std::vector<Triangulo> poligonos, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Vector> chequear_colision(Ray rayo);
		Vector getNormal(Vector vector);
		Color getColor();
		void Print();
};
#endif 