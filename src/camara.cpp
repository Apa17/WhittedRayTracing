#include "../inc/camara.h"

Camara::Camara(Punto posicion, Punto upVector, Punto lookatVector) {
    this->posicion = posicion;
    this->upVector = upVector;
    this->lookatVector = lookatVector;
}

Punto Camara::getPosicion() {
    return this->posicion;
}

Punto Camara::getUpVector() {
    return this->upVector;
}

Punto Camara::getLookatVector() {
    return this->lookatVector;
}