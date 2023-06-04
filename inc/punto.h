#ifndef PUNTO_H
#define PUNTO_H

class Punto {
	private:
		double x;
		double y;
		double z;
		double norma_al_cuadrado;
	public:
		Punto(double x, double y, double z);
		Punto operator-(Punto p);
		Punto operator+(Punto p);
		Punto operator*(Punto d);
		Punto operator*(double d);
		double getNorma_al_cuadrado();
		double getX();
		double getY();
		double getZ();
};
#endif