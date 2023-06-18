#ifndef CILINDRO_H
#define CILINDRO_H

#include "objeto.h"
#include "punto.h"
#include "color.h"
#include <tuple>

class Cilindro : public Objeto {
	private:
		double radio;
        double altura;
		Punto centro;
        Punto direccion_eje;
        Punto centro_tapa1;
        Punto centro_tapa2;
	public:
		Cilindro(double radio, double altura, Punto centro, Punto direccion_eje, Color colorDifuso, Color colorEspecular, double ka, double kd,double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Punto> chequear_colision(Ray rayo);
		Punto getNormal(Punto punto);
};
#endif 
