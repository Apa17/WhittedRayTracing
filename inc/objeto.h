#ifndef OBJETO_H
#define OBJETO_H

#include "ray.h"
#include "punto.h"
#include "color.h"
#include <tuple>
class Objeto {
	public: 
		virtual std::pair<bool, Punto> chequear_colision(Ray rayo) = 0;
		virtual Punto getNormal(Punto punto) = 0;
		double getcoefReflex();
		double getcoefTransm();
		double getindRefrac();
		Color getColorDifuso();
		Color getColorEspecular();
		//double isInside(Punto punto);
	protected:
		Color colorDifuso;
		Color colorEspecular;
		double coefReflex; // coeficiente de reflexión
		double coefTransm; // coeficiente de transmisión
		double indRefrac; // índice de refracción
};

#endif