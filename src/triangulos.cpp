#include "../inc/triangulos.h"
#include <iostream>

Triangulo::Triangulo(Vector a, Vector b, Vector c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->normal = (b-a).cross(c-a).normalized();
}

Vector Triangulo::getNormal(Vector vector) {
    return this->normal;
}

std::pair<bool, Vector> Triangulo::chequear_colision(Ray rayo){
    double u= this->normal * rayo.direccion;
    Vector actreves = this->normal.cross(this->a - this->c);
    actreves = actreves / ((this->b-this->a)*actreves);
    Vector abtreves = this->normal.cross(this->b - this->a);
    abtreves = abtreves / ((this->c-this->a)*abtreves);
    if (u == 0) {
        return std::make_pair(false, Vector(0,0,0));
    }
    double t = ((this->a - rayo.origen) * this->normal) / u;
    if (t < 0) {
        return std::make_pair(false, Vector(0,0,0));
    }

    Vector Q = rayo.origen + rayo.direccion * t;
    double gamma = (Q - this->c) * actreves;
    double beta = (Q - this->b) * abtreves;
    double alfa = 1 - gamma - beta;
    if (gamma < -1e-4 || gamma > 1 + 1e-4 || beta < -1e-4 || beta > 1 + 1e-4 || alfa < -1e-4 || alfa > 1 + 1e-4) {
        return std::make_pair(false, Vector(0,0,0));
    } else {
        return std::make_pair(true, Q);
    }
}

std::ostream& operator<<(std::ostream& os, const Triangulo& obj) {
    os << " Triangulo: \n";
    os << " A: " << obj.a << "\n";
    os << " B: " << obj.b << "\n";
    os << " C: " << obj.c << "\n";
    os << " Normal: " << obj.normal << "\n";
    return os;
}