#include "../inc/punto.h"

Punto::Punto() {
    this->x=0;
    this->y=0;
    this->z=0;
    this->norma_al_cuadrado=0;
}

Punto::~Punto() {
    // TODO
}

Punto::Punto(double x, double y, double z) {
    this->x=x;
    this->y=y;
    this->z=z;
    this->norma_al_cuadrado=x*x+y*y+z*z;
}

double Punto::getNorma_al_cuadrado() {
    return norma_al_cuadrado;
}

double Punto::getX() {
    return x;
}

double Punto::getY() {
    return y;
}

double Punto::getZ() {
    return z;
}

Punto Punto::operator-(Punto p) {
    return Punto(x-p.getX(), y-p.getY(), z-p.getZ());
}

Punto Punto::operator+(Punto p) {
    return Punto(x+p.getX(), y+p.getY(), z+p.getZ());
}

double Punto::operator*(Punto p) {
    return x*p.getX()+y*p.getY()+z*p.getZ();
}

Punto Punto::operator*(double d) {
    return Punto(x*d, y*d, z*d);
}