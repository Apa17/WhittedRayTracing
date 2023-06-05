#include "../inc/esfera.h"
#include <iostream>

Esfera::Esfera(double radio, Punto centro, color colour) {
    this->radio = radio;
    this->centro = centro;
    this->colour = colour;
}

std::pair<bool, Punto> Esfera::chequear_colision(Ray rayo) { //rayo = ([0,0,0], 0,0,-1)
    Punto   u = rayo.direccion; //0,0,-1
    Punto   o = rayo.origen;  // 0,0,0
    Punto   c = this->centro; //0,0,-10
    double  r = this->radio; // 100
    // o-c = 0,0,10
    // u * 0,0,10 = -10
    //pow(u*(o-c),2) = 100
    // (o-c).getNorma_al_cuadrado() = 100
    // (o-c).getNorma_al_cuadrado() + r*r = 10000
    // 100 - (100 +10000) * 1    
    double determinante = pow(u*(o-c),2) - ((o-c).getNorma_al_cuadrado() - r*r) * (u.getNorma_al_cuadrado());
    // if(u == Punto(0,0,-1))
        // std::cout << determinante << std::endl;
    if (determinante >= 0) {
        double t1 = -(u*(o-c)) + sqrt(determinante);
        double t2 = -(u*(o-c)) - sqrt(determinante);
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
    } else {
        return std::pair<bool, Punto>(false, Punto(0,0,0));
    }
}

color Esfera::getColor() {
    return this->colour;
}