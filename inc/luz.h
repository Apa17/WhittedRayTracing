#ifndef LUZ_H
#define LUZ_H
#include "punto.h"
#include <tuple>
using color = std::tuple<double, double, double, double>;
struct Luz{
    Punto posicion;
    color colour;
    Luz(){}
    Luz(Punto posicion, color colour){
        this->posicion = posicion;
        this->colour = colour;
    }
};
#endif