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

Color Objeto::getColorDifuso() {
    return this->colorDifuso;
}

Color Objeto::getColorEspecular() {
    return this->colorEspecular;
}
