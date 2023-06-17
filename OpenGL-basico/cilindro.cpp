#include "../inc/cilindro.h"
#include <iostream>

Cilindro::Cilindro(double radio, double altura, Punto centro, Punto direccion_eje, Color colorDifuso, Color colorEspecular, double coefReflex, double coefTransm, double indRefrac) {
    this->radio = radio;
    this->altura = altura;
    this->centro = centro;
    this->direccion_eje = direccion_eje.normalized();
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->coefReflex = coefReflex;
    this->coefTransm = coefTransm;
    this->indRefrac = indRefrac;
    this->centro_tapa1 = centro + (direccion_eje * (altura / 2));
    this->centro_tapa2 = centro + (direccion_eje * (-altura / 2));
}

std::pair<bool, Punto> Cilindro::chequear_colision(Ray rayo) {

    Punto   u = rayo.direccion;
    Punto   o = rayo.origen;
    Punto   c = this->centro;
    Punto   eje = this->direccion_eje;
    double  r = this->radio;
    double  h = this->altura;

    Punto centro_tapa1 = this->centro_tapa1;
    Punto centro_tapa2 = this->centro_tapa2;

    // Encuentro planos donde estan las tapas
    double xp = eje.getX();
    double yp = eje.getY();
    double zp = eje.getZ();
    double d1 = -xp * centro_tapa1.getX() - yp * centro_tapa1.getY() - zp * centro_tapa1.getZ();
    double d2 = -xp * centro_tapa2.getX() - yp * centro_tapa2.getY() - zp * centro_tapa2.getZ();

    // t es el coeficiente con el que o + u*t pertenece al plano
    double t1 = (xp * (centro_tapa1.getX() - o.getX()) + yp * (centro_tapa1.getY() - o.getY()) + zp * (centro_tapa1.getZ() - o.getZ())) / (xp * u.getX() + yp * u.getY() + zp * u.getZ());
    double t2 = (xp * (centro_tapa2.getX() - o.getX()) + yp * (centro_tapa2.getY() - o.getY()) + zp * (centro_tapa2.getZ() - o.getZ())) / (xp * u.getX() + yp * u.getY() + zp * u.getZ());

    // puntos a retornar
    Punto p1;
    Punto p2;
    bool b1 = false;
    bool b2 = false;

    if (t1 > 0) {
        Punto p1 = o + u * t1;
        if ((p1 - centro_tapa1).getNorma_al_cuadrado() <= r * r) {
            b1 = true;
        }
    }

    if (t2 > 0) {
        Punto p2 = o + u * t2;
        if ((p2 - centro_tapa2).getNorma_al_cuadrado() <= r * r)
            b2 = true;
    }

    if (b1) {
        if (b2) {
            if (p1.getNorma_al_cuadrado() < p2.getNorma_al_cuadrado())
                return std::pair<bool, Punto>(true, p1);
            else
                return std::pair<bool, Punto>(true, p2);
        }
        else
            return std::pair<bool, Punto>(true, p1);
    }
    if (b2)
        return std::pair<bool, Punto>(true, p2);

}

Punto Cilindro::getNormal(Punto p) {
    return this->direccion_eje;
}