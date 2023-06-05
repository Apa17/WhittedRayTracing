#ifndef CAMARA_H
#define CAMARA_H
#include "punto.h"
#include "../inc/ray.h"

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
        Ray** getRays(int width, int height);
};

#endif