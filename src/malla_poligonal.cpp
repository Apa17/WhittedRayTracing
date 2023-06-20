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

Punto Malla_Poligonal::getNormal(Punto punto) {
    Ray rayo;
    rayo.origen = Punto(0,0,0);
    rayo.direccion = punto;
    std::pair<bool, Punto> colision = std::make_pair(false, Punto(0,0,0));
    Punto res = Punto();
    for (Triangulo poligono: this->poligonos) {
        std::pair<bool, Punto> colisionActual = poligono.chequear_colision(rayo);
        if (colisionActual.first) {
            if (colision.first) {
                if ((colisionActual.second - rayo.origen).normalized() < (colision.second - rayo.origen).normalized()) {
                    colision = colisionActual;
                    res = poligono.getNormal(punto);
                }
            } else {
                colision = colisionActual;
                res = poligono.getNormal(punto);
            }
        }
    }
    return res;
}

std::pair<bool, Punto> Malla_Poligonal::chequear_colision(Ray rayo){
    std::pair<bool, Punto> colision = std::make_pair(false, Punto(0,0,0));
    for (Triangulo triangulo: this->poligonos) {
        std::pair<bool, Punto> colisionActual = triangulo.chequear_colision(rayo);
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