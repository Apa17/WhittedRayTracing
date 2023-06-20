#include "../inc/malla_poligonal.h"

Malla_Poligonal::Malla_Poligonal(std::vector<Triangulo> poligonos, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac) {
    this->poligonos = poligonos;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->ka = ka;
    this->kd = kd;
    this->ks = coefReflex;
    this->kt = coefTransm;
    this->indRefrac = indRefrac;
}

Vector Malla_Poligonal::getNormal(Vector vector) {
    Ray rayo;
    rayo.origen = Vector(0,0,0);
    rayo.direccion = vector;
    std::pair<bool, Vector> colision = std::make_pair(false, Vector(0,0,0));
    Vector res = Vector();
    for (Triangulo poligono: this->poligonos) {
        std::pair<bool, Vector> colisionActual = poligono.chequear_colision(rayo);
        if (colisionActual.first) {
            if (colision.first) {
                if ((colisionActual.second - rayo.origen).normalized() < (colision.second - rayo.origen).normalized()) {
                    colision = colisionActual;
                    res = poligono.getNormal(vector);
                }
            } else {
                colision = colisionActual;
                res = poligono.getNormal(vector);
            }
        }
    }
    return res;
}

std::pair<bool, Vector> Malla_Poligonal::chequear_colision(Ray rayo){
    std::pair<bool, Vector> colision = std::make_pair(false, Vector(0,0,0));
    for (Triangulo triangulo: this->poligonos) {
        std::pair<bool, Vector> colisionActual = triangulo.chequear_colision(rayo);
        if (colisionActual.first) {
            if (colision.first) {
                if ((colisionActual.second - rayo.origen).normalized() < (colision.second - rayo.origen).normalized()) {
                    colision = colisionActual;
                }
            } else {
                colision = colisionActual;
            }
        }
    }
    return colision;
}

void Malla_Poligonal::Print(){
    std::cout << "Triangulos: \n";
    for (Triangulo poligono: this->poligonos) {
        std::cout << poligono << "\n";
    }
}