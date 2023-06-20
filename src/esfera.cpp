#include "../inc/esfera.h"
#include <iostream>

Esfera::Esfera(double radio, Vector centro, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac) {
    this->radio = radio;
    this->centro = centro;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->ka = ka;
    this->kd = kd;
    this->ks = coefReflex;
    this->kt = coefTransm;
    this->indRefrac = indRefrac;
}

std::pair<bool, Vector> Esfera::chequear_colision(Ray rayo) {
    
    Vector   u = rayo.direccion;
    Vector   o = rayo.origen;
    Vector   c = this->centro;
    double  r = this->radio;
    double determinante = pow(u*(o-c),2) - ((o-c).getNorma_al_cuadrado() - r*r) * (u.getNorma_al_cuadrado());
    if (determinante >= 0) {
        double t1 = -(u*(o-c)) + sqrt(determinante);
        double t2 = -(u*(o-c)) - sqrt(determinante);
        if (t1 > 0 && t2 > 0) {
            Vector p1 = o + u*t1;
            Vector p2 = o + u*t2;
            if (p1.getNorma_al_cuadrado() < p2.getNorma_al_cuadrado()) {
                return std::pair<bool, Vector>(true, p1);
            } else {
                return std::pair<bool, Vector>(true, p2);
            }
        } else if (t1 > 0) {
            return std::pair<bool, Vector>(true, o + u*t1);
        } else if (t2 > 0) {
            return std::pair<bool, Vector>(true, o + u*t2);
        }
    }
    return std::pair<bool, Vector>(false, Vector(0,0,0));
}

Vector Esfera::getNormal(Vector p) {
    return (p - this->centro).normalized();
}

void Esfera::Print() {
    std::cout << "Esfera: \n";
    std::cout << "Radio: " << this->radio << "\n";
    std::cout << "Centro: " << this->centro << "\n";
}