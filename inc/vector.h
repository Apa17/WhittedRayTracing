#ifndef PUNTO_H
#define PUNTO_H
#include <iostream>

class Vector {
	private:
		double x;
		double y;
		double z;
		double norma_al_cuadrado;
	public:
		Vector();
		Vector(double x, double y, double z);
		~Vector();
		Vector operator-(Vector p);
		Vector operator+(Vector p);
		double operator*(Vector d);
		Vector operator*(double d);
		bool operator==(Vector p);
		Vector operator/(double d);
		bool operator<(Vector p);
		Vector cross(Vector p);
		Vector normalized();
		double getNorma_al_cuadrado();
		double getX();
		double getY();
		double getZ();
		friend std::ostream& operator<<(std::ostream& os, Vector p);
};

double distancia_entre_punto_al_cuadrado(Vector p1, Vector p2);
#endif