#include "../inc/esfera.h"

std::pair<bool, Punto> Esfera::chequear_colision(Punto posicion_camara, Ray rayo) {
    Punto   u = rayo.direccion;
    Punto   o = posicion_camara;
    Punto   c = this->centro;
    double  r = this->radio;
    return std::pair<bool, Punto>(false, Punto(0,0,0));
}
