#ifndef LUZ_H
#define LUZ_H
#include "punto.h"
#include <tuple>
class Luz{
    public:
    Punto posicion;
    Color colour;
    Luz(){
        posicion = Punto(0,0,0);
        colour = Color(0,0,0);
    }
    Luz(Punto posicion, Color colour) {
        this->posicion = posicion;
        this->colour = colour;
    }
};
#endif