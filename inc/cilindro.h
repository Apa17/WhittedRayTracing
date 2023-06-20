#ifndef CILINDRO_H
#define CILINDRO_H

#include "objeto.h"
#include "vector.h"
#include "color.h"
#include <tuple>

class Cilindro : public Objeto {
	private:
		double radio;
        double altura;
		Vector centro;
        Vector direccion_eje;
        Vector centro_tapa1;
        Vector centro_tapa2;
	public:
		Cilindro(double radio, double altura, Vector centro, Vector direccion_eje, Color colorDifuso, Color colorEspecular, double ka, double kd,double coefReflex, double coefTransm, double indRefrac);
		std::pair<bool, Vector> chequear_colision(Ray rayo);
		std::pair<bool, Vector> chequear_colision_tapas (Ray rayo);
		std::pair<bool, Vector> chequear_colision_tronco (Ray rayo);
		Vector getNormal(Vector vector);
		void Print();
};
#endif 
