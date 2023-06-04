#include <set>
#include "tinyxml2.h"
#include <string>
#include <vector>

#ifndef ESCENA_H
#define ESCENA_H

using namespace std;

class Escena {
private:
	//vector<Objeto3d*> objetos;
	//Camara * camara;
	//vector<Light*> luces;
public:
	Escena(string);
	//Punto* getCentroDeProyeccion();
	//Punto* getcentroVentanaPV();
	//Ray* getrayo(double, double); //generateray 
	~Escena();
};

#endif