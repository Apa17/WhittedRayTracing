#include "../inc/esfera.h"
#include <iostream>

Esfera::Esfera(double radio, Punto centro, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac) {
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

std::pair<bool, Punto> Esfera::chequear_colision(Ray rayo) {
    
    Punto   u = rayo.direccion;
    Punto   o = rayo.origen;
    Punto   c = this->centro;
    double  r = this->radio;
    double determinante = pow(u*(o-c),2) - ((o-c).getNorma_al_cuadrado() - r*r) * (u.getNorma_al_cuadrado());
    if(rayo.origen == Punto(0,0,-4) && this->centro == Punto(0,0,-5)){
        std::cout << "u: " << u << std::endl;
        std::cout << "o: " << o << std::endl;
        std::cout << "c: " << c << std::endl;
        std::cout << "r: " << r << std::endl;
        std::cout << "determinante: " << determinante << std::endl;
    }
    if (determinante >= 0) {
        double t1 = -(u*(o-c)) + sqrt(determinante);
        double t2 = -(u*(o-c)) - sqrt(determinante);
        if(rayo.origen == Punto(0,0,-4) && this->centro == Punto(0,0,-5)){
            std::cout << "t1: " << t1 << std::endl;
            std::cout << "t2: " << t2 << std::endl;
        }
        if (t1 > 0 && t2 > 0) {
            Punto p1 = o + u*t1;
            Punto p2 = o + u*t2;
            if (p1.getNorma_al_cuadrado() < p2.getNorma_al_cuadrado()) {
                return std::pair<bool, Punto>(true, p1);
            } else {
                return std::pair<bool, Punto>(true, p2);
            }
        } else if (t1 > 0) {
            return std::pair<bool, Punto>(true, o + u*t1);
        } else if (t2 > 0) {
            return std::pair<bool, Punto>(true, o + u*t2);
        }
    }
    return std::pair<bool, Punto>(false, Punto(0,0,0));
}

Punto Esfera::getNormal(Punto p) {
    return (p - this->centro).normalized();
}