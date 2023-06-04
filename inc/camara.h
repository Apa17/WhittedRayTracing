#ifndef CAMARA_H
#define CAMARA_H
#include "punto.h"

class Camara {
    private:
        Punto posicion;
        Punto upVector;
        Punto lookatVector;
        double verticalSize;
        double horizontalSize;
    public:
        Camara(Punto posicion, Punto upVector, Punto lookatVector, double verticalSize, double horizontalSize);
        Punto getPosicion();
        Punto getUpVector();
        Punto getLookatVector();
        double getVerticalSize();
        double getHorizontalSize();
        double getDistanceToViewPlane();
        Punto** getRays(int width, int height);
};

#endif