#include "../inc/vector.h"
#include <math.h>

Vector::Vector() {
    this->x=0;
    this->y=0;
    this->z=0;
    this->norma_al_cuadrado=0;
}

Vector::~Vector() {
    // TODO
}

Vector::Vector(double x, double y, double z) {
    this->x=x;
    this->y=y;
    this->z=z;
    this->norma_al_cuadrado=x*x+y*y+z*z;
}

double Vector::getNorma_al_cuadrado() {
    return norma_al_cuadrado;
}

double Vector::getX() {
    return x;
}

double Vector::getY() {
    return y;
}

double Vector::getZ() {
    return z;
}

Vector Vector::operator-(Vector p) {
    return Vector(x-p.getX(), y-p.getY(), z-p.getZ());
}

Vector Vector::operator+(Vector p) {
    return Vector(x+p.getX(), y+p.getY(), z+p.getZ());
}

double Vector::operator*(Vector p) {
    return x*p.getX()+y*p.getY()+z*p.getZ();
}

Vector Vector::operator*(double d) {
    return Vector(x*d, y*d, z*d);
}

bool Vector::operator==(Vector p) {
    return x==p.getX() && y==p.getY() && z==p.getZ();
}

Vector Vector::cross(Vector p) {
    return Vector(y *p.getZ() - z*p.getY(), z*p.getX()-x*p.getZ(), x*p.getY()-y*p.getX());
}

Vector Vector::normalized() {
    return Vector(x/sqrt(norma_al_cuadrado), y/sqrt(norma_al_cuadrado), z/sqrt(norma_al_cuadrado));
}

double distancia_entre_punto_al_cuadrado(Vector p1, Vector p2){
    return (p1 - p2).getNorma_al_cuadrado();
}

Vector Vector::operator/(double d) {
    return Vector(x/d, y/d, z/d);
}

bool Vector::operator<(Vector p) {
    return x<p.getX() && y<p.getY() && z<p.getZ();
}

std::ostream& operator<<(std::ostream& os, Vector p) {
    os << "(" << p.getX() << ", " << p.getY() << ", " << p.getZ() << ")";
    return os;
}