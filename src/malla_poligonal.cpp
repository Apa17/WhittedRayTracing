#include "../inc/malla_poligonal.h"

Malla_Poligonal::Malla_Poligonal(Triangulo** poligonos, int cantidad_triangulos, Color colorDifuso, Color colorEspecular, double ka, double kd, double coefReflex, double coefTransm, double indRefrac) {
    this->poligonos = poligonos;
    this->cantidad_triangulos = cantidad_triangulos;
    this->colorDifuso = colorDifuso;
    this->colorEspecular = colorEspecular;
    this->ka = ka;
    this->kd = kd;
    this->ks = coefReflex;
    this->kt = coefTransm;
    this->indRefrac = indRefrac;
}

Punto Malla_Poligonal::getNormal(Punto punto) {
    Ray rayo;
    rayo.origen = Punto(0,0,0);
    rayo.direccion = punto;
    std::pair<bool, Punto> colision = std::make_pair(false, Punto(0,0,0));
    Triangulo * triangulo = NULL;
    for (int i = 0; i < this->cantidad_triangulos; i++) {
        std::pair<bool, Punto> colisionActual = this->poligonos[i]->chequear_colision(rayo);
        if (colisionActual.first) {
            if (colision.first) {
                if ((colisionActual.second - rayo.origen).normalized() < (colision.second - rayo.origen).normalized()) {
                    colision = colisionActual;
                    triangulo = this->poligonos[i];
                }
            } else {
                colision = colisionActual;
                triangulo = this->poligonos[i];
            }
        }
    }
    return triangulo->getNormal(punto);
}

std::pair<bool, Punto> Malla_Poligonal::chequear_colision(Ray rayo){
    std::pair<bool, Punto> colision = std::make_pair(false, Punto(0,0,0));
    for (int i = 0; i < this->cantidad_triangulos; i++) {
        std::pair<bool, Punto> colisionActual = this->poligonos[i]->chequear_colision(rayo);
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