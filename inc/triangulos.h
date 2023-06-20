#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "objeto.h"
#include "vector.h"

class Triangulo {
	private:
        Vector a;
        Vector b;
        Vector c;
        Vector normal;
	public:
		Triangulo(Vector a, Vector b, Vector c);
		std::pair<bool, Vector> chequear_colision(Ray rayo);
		Vector getNormal(Vector vector);
		friend std::ostream& operator<<(std::ostream& os, const Triangulo& obj);
};
#endif 