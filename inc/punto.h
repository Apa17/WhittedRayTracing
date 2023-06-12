#ifndef PUNTO_H
#define PUNTO_H
#include <iostream>

class Punto {
	private:
		double x;
		double y;
		double z;
		double norma_al_cuadrado;
	public:
		Punto();
		Punto(double x, double y, double z);
		~Punto();
		Punto operator-(Punto p);
		Punto operator+(Punto p);
		double operator*(Punto d);
		Punto operator*(double d);
		bool operator==(Punto p);
		Punto operator/(double d);
		Punto cross(Punto p);
		Punto normalized();
		double getNorma_al_cuadrado();
		double getX();
		double getY();
		double getZ();
		friend std::ostream& operator<<(std::ostream& os, Punto p);
};

double distancia_entre_punto_al_cuadrado(Punto p1, Punto p2);
#endif