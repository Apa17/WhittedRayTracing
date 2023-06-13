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
		color getColorDifuso();
		color getColorEspecular();
	protected:
		color colorDifuso;
		color colorEspecular;
		double coefReflex; // coeficiente de reflexión
		double coefTransm; // coeficiente de transmisión
		double indRefrac; // índice de refracción
};

#endif