#include "../inc/esfera.h"

std::pair<bool, Punto> Esfera::chequear_colision(Punto posicion_camara, Ray rayo) {
    Punto   u = rayo.direccion;
    Punto   o = posicion_camara;
    Punto   c = this->centro;
    double  r = this->radio;
    double determinante = pow(u*(o-c),2) - ((o-c).getNorma_al_cuadrado() + r*r) * (u.getNorma_al_cuadrado());
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
