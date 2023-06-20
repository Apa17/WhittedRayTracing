#ifndef LUZ_H
#define LUZ_H
#include "vector.h"
#include <tuple>
class Luz{
    public:
    Vector posicion;
    Color colour;
    Luz(){
        posicion = Vector(0,0,0);
        colour = Color(0,0,0);
    }
    Luz(Vector posicion, Color colour) {
        this->posicion = posicion;
        this->colour = colour;
    }
};
#endif