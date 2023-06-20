#ifndef CAMARA_H
#define CAMARA_H
#include "vector.h"
#include "../inc/ray.h"

class Camara {
    private:
        Vector posicion;
        Vector upVector;
        Vector lookatVector;
        double verticalSize;
        double horizontalSize;
    public:
        Camara(Vector posicion, Vector upVector, Vector lookatVector, double verticalSize, double horizontalSize);
        Camara();
        Vector getPosicion();
        Vector getUpVector();
        Vector getLookatVector();
        double getVerticalSize();
        double getHorizontalSize();
        double getDistanceToViewPlane();
        Ray** getRays(int width, int height);
};

#endif