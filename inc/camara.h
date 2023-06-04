#ifndef CAMARA_H
#define CAMARA_H
#include "punto.h"

class Camara {
    private:
        Punto posicion;
        Punto upVector;
        Punto lookatVector;
    public:
        Camara(Punto posicion, Punto upVector, Punto lookatVector);
        Punto getPosicion();
        Punto getUpVector();
        Punto getLookatVector();
};

#endif