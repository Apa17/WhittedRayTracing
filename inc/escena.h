#include <set>
#include "tinyxml2.h"
#include <string>
#include <vector>
#include "objeto.h"
#include "camara.h"
#include "luz.h"

#ifndef ESCENA_H
#define ESCENA_H

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
	Color sombra_rr(Objeto* o, Ray r, Vector interseccion, Vector normal, int depth);
	void Escena::recorrer_pixeles(int imin, int imax, h_w_color& color, h_w_color& coefs_reflexion_fondo_negro, h_w_color& coefs_refraccion_fondo_negro, Ray** rayos);
public:
	Escena(std::string);
	~Escena();
	int render();
	void debug();
};

#endif