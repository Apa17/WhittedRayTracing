#include "../inc/objeto.h"

double Objeto::getcoefReflex() {
    return this->coefReflex;
}

double Objeto::getcoefTransm() {
    return this->coefTransm;
}

double Objeto::getindRefrac() {
    return this->indRefrac;
}

color Objeto::getColorDifuso() {
    return this->colorDifuso;
}

color Objeto::getColorEspecular() {
    return this->colorEspecular;
}
