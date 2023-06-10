#include "../inc/punto.h"
#include <math.h>

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

bool Punto::operator==(Punto p) {
    return x==p.getX() && y==p.getY() && z==p.getZ();
}

Punto Punto::cross(Punto p) {
    return Punto(y*p.getZ()-z*p.getY(), z*p.getX()-x*p.getZ(), x*p.getY()-y*p.getX());
}

Punto Punto::normalized() {
    return Punto(x/sqrt(norma_al_cuadrado), y/sqrt(norma_al_cuadrado), z/sqrt(norma_al_cuadrado));
}
#include <iostream>
double distancia_entre_punto_al_cuadrado(Punto p1, Punto p2){
    return (p1 - p2).getNorma_al_cuadrado();
}