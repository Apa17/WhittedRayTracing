#include "../inc/cilindro.h"
#include <iostream>

Cilindro::Cilindro(double radio, double altura, Vector centro, Vector direccion_eje, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac){
    this->radio = radio;
    this->altura = altura;
    this->centro = centro;
    this->direccion_eje = direccion_eje.normalized();
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->ka = ka;
    this->kd = kd;
    this->ks = coefReflex;
    this->kt = coefTransm;
    this->indRefrac = indRefrac;
    this->centro_tapa1 = centro + (direccion_eje.normalized() * (altura/2));
    this->centro_tapa2 = centro + (direccion_eje.normalized() * (-altura/2));
}

std::pair<bool, Vector> Cilindro::chequear_colision_tapas(Ray rayo) {
    Vector centro_tapa1 = this->centro_tapa1;
    Vector centro_tapa2 = this->centro_tapa2;
    Vector normal1 = this->direccion_eje;
    Vector normal2 = this->direccion_eje *-1;

    double u1 = normal1 * rayo.direccion.normalized();
    double u2 = normal2 * rayo.direccion.normalized();
    if (u1 == 0) {
        return std::make_pair(false, Vector(0,0,0));
    }
    double t1 = ((this->centro_tapa1 - rayo.origen) * normal1) / u1;
    double t2 = ((this->centro_tapa2 - rayo.origen) * normal2) / u2;
    Vector Q1 = rayo.origen + rayo.direccion * t1;
    Vector Q2 = rayo.origen + rayo.direccion * t2;
    bool x1 = (Q1 - centro_tapa1).getNorma_al_cuadrado() <= (this->radio * this->radio) + 1e-4;
    bool x2 = (Q2 - centro_tapa2).getNorma_al_cuadrado() <= (this->radio * this->radio) + 1e-4;
    if (t1 > 0 && t2 > 0 && x1 && x2){
        if ((Q1 - rayo.origen).getNorma_al_cuadrado() < (Q2 - rayo.origen).getNorma_al_cuadrado()) {
            return std::make_pair(true, Q1);
        } else {
            return std::make_pair(true, Q2);
        }
    } else if (t1 > 0 && x1){
        return std::make_pair(true, Q1);
    }
    if(t2 > 0 && x2){
        return std::make_pair(true, Q2);
    }
    return std::make_pair(false, Vector());
}

std::pair<bool, Vector> Cilindro::chequear_colision_tronco(Ray rayo) {
    Vector   u = rayo.direccion;
    Vector   v = this->direccion_eje;
    Vector   o = rayo.origen;
    Vector   c = this->centro;
    double  r = this->radio;
    double  h = this->altura;
    double a = u * u - (u * v) * (u * v); // a = u^2 - (u.v)^2
    double b = 2 * (u * (o - c) - (u * v) * (v * (o - c))); // b = 2(u.(o-c) - (u.v)(v.(o-c)))
    double c1 = (o - c) * (o - c) - (v * (o - c)) * (v * (o - c)) - r * r;
    double discriminante = b * b - 4 * a * c1;
    if (discriminante < 0) {
        return std::make_pair(false, Vector());
    }
    double t1 = (-b + sqrt(discriminante)) / (2 * a);
    double t2 = (-b - sqrt(discriminante)) / (2 * a);
    Vector Q1 = o + u * t1;
    Vector Q2 = o + u * t2;
    double x1 = (Q1 - c) * v;
    double x2 = (Q2 - c) * v;
    if (t1 > 0 && t2 > 0 && x1 > -h/2 + 1e-4 && x1 < h/2 + 1e-4 && x2 > -h/2 + 1e-4 && x2 < h/2 + 1e-4){
        if (t1 < t2) {
            return std::make_pair(true, Q1);
        } else {
            return std::make_pair(true, Q2);
        }
    } else if (t1 > 0 && x1 > -h/2 + 1e-4 && x1 < h/2 + 1e-4){
        return std::make_pair(true, Q1);
    }
    if(t2 > 0 && x2 > -h/2 + 1e-4 && x2 < h/2 + 1e-4){
        return std::make_pair(true, Q2);
    }
    return std::make_pair(false, Vector());
}

std::pair<bool, Vector> Cilindro::chequear_colision(Ray rayo) {
    std::pair<bool, Vector> colision_tapas = chequear_colision_tapas(rayo);
    std::pair<bool, Vector> colision_tronco = chequear_colision_tronco(rayo);

    if (colision_tapas.first) {
        if (colision_tronco.first) {
            if ((colision_tapas.second - rayo.origen).getNorma_al_cuadrado() < (colision_tronco.second - rayo.origen).getNorma_al_cuadrado())
                return colision_tapas;
            else
                return colision_tronco;
        }
        else
            return colision_tapas;
    }
    if (colision_tronco.first)
        return colision_tronco;
    else
        return std::pair<bool, Vector>(false, Vector());
}

Vector Cilindro::getNormal(Vector p) {
    double a = this->direccion_eje.cross(p - this->centro).getNorma_al_cuadrado();
    bool j = (p - this->centro_tapa1).getNorma_al_cuadrado() < (p - this->centro_tapa2).getNorma_al_cuadrado();
    if(abs(a - this->radio * this->radio) < 1e-4){ //x > y
        return (p - this->centro).normalized();
    } else if (j){
        return this->direccion_eje;
    } else {
        return this->direccion_eje * -1;
    }
}

void Cilindro::Print(){
    std::cout << "Cilindro: Centro: " << this->centro << " Radio: " << this->radio << " Altura: " << this->altura << " Direccion_Eje: " << this->direccion_eje << "\n";
}