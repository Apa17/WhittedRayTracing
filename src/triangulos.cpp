#include "../inc/triangulos.h"
#include <iostream>

Triangulo::Triangulo(Punto a, Punto b, Punto c, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->normal = (b-a).cross(c-a).normalized();
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->ks = coefReflex;
    this->kt = coefTransm;
    this->indRefrac = indRefrac;
}

Punto Triangulo::getNormal(Punto punto) {
    return this->normal;
}

std::pair<bool, Punto> Triangulo::chequear_colision(Ray rayo){
    double u= this->normal * rayo.direccion;
    Punto actreves = this->normal.cross(this->a - this->c);
    actreves = actreves / ((this->b-this->a)*actreves);
    Punto abtreves = this->normal.cross(this->b - this->a);
    abtreves = abtreves / ((this->c-this->a)*abtreves);
    if (u == 0) {
        return std::make_pair(false, Punto(0,0,0));
    }
    double t = ((this->a - rayo.origen) * this->normal) / u;
    if (t < 0) {
        return std::make_pair(false, Punto(0,0,0));
    }

    Punto Q = rayo.origen + rayo.direccion * t;
    double gamma = (Q - this->c) * actreves;
    double beta = (Q - this->b) * abtreves;
    double alfa = 1 - gamma - beta;
    if (gamma < 0 || gamma > 1 || beta < 0 || beta > 1 || alfa < 0 || alfa > 1) {
        return std::make_pair(false, Punto(0,0,0));
    } else {
        return std::make_pair(true, Q);
    }
}