#include <set>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include "objeto.h"
#include "camara.h"
#include "luz.h"

#ifndef ESCENA_H
#define ESCENA_H

using namespace std;

class Escena {
private:
	int ancho;
	int altura;
	double verticalSize;
	double horizontalSize;
	double depth_max;
	std::vector<Objeto *> objetos;
	std::vector<Luz> luces;
	Camara camara;
	Color traza_rr(Ray ray, int depth);
	Color traza_rr_2(Ray ray, bool refraccion, Color fondo);
	Color sombra_rr(Objeto* o, Ray r, Punto interseccion, Punto normal, int depth);
public:
	Escena(string);
	int render();
	void debug();
};

#endif