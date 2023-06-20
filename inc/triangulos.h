#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "objeto.h"
#include "punto.h"

class Triangulo {
	private:
        Punto a;
        Punto b;
        Punto c;
        Punto normal;
	public:
		Triangulo(Punto a, Punto b, Punto c);
		std::pair<bool, Punto> chequear_colision(Ray rayo);
		Punto getNormal(Punto punto);
		friend std::ostream& operator<<(std::ostream& os, const Triangulo& obj);
};
#endif 