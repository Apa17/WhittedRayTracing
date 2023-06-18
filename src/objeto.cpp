#include "../inc/objeto.h"

double Objeto::getcoefAmbiente() {
    return this->ka;
}

double Objeto::getcoefDifuso() {
    return this->kd;
}

double Objeto::getcoefReflex() {
    return this->ks;
}

double Objeto::getcoefTransm() {
    return this->kt;
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
