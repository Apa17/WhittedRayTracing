#ifndef OBJETO_H
#define OBJETO_H

#include "ray.h"
#include "vector.h"
#include "color.h"
#include <tuple>
#include <iostream>

class Objeto {
	public: 
		virtual std::pair<bool, Vector> chequear_colision(Ray rayo) = 0;
		virtual Vector getNormal(Vector vector) = 0;
		double getcoefAmbiente();
		double getcoefDifuso();
		double getcoefReflex();
		double getcoefTransm();
		double getindRefrac();
		Color getColorDifuso();
		Color getColorEspecular();
		virtual void Print() = 0;
		//double isInside(Vector vector);
	protected:
		Color colorDifuso;
		Color colorEspecular;
		double ka; // coeficiente de ambiente
		double kd; // coeficiente de difusión
		double ks; // coeficiente de reflexión
		double kt; // coeficiente de transmisión
		double indRefrac; // índice de refracción
};

#endif