#include <string>
#include <iostream>
#include "Escena.h"
#include <tuple>
#include "Render.h"
#include "Camara.h"
#include "Punto.h"
#include "Esfera.h"

#define ANCHO 1920;
#define ALTO 1080;

using namespace std;

using h_w_color = std::vector<std::vector<std::tuple<double, double, double, double>>>;
using w_color = std::vector<std::tuple<double, double, double, double>>;
using color = std::tuple<double, double, double, double>;

double verticalSize = 1.080;
double horizontalSize = 1.920;

Camara camara(Punto(0, 0, 0), Punto(0, 1, 0), Punto(0, 0, -1), verticalSize, horizontalSize); //replace this
Esfera esfera(2, Punto(0, 0, -10), color(163.0, 163.0, 163.0, 1.0), 1.0, 0.0, 1.0); //replace this
Punto* luces;
int cantLuces;

/*tuple<double, double, double, double> escalarColor(tuple<double, double, double, double> color, tuple<double, double, double, double> alpha) {
	return tuple<double, double, double, double>(std::get<0>(color) * (std::get<0>(alpha) / 255.0),
		std::get<1>(color) * (std::get<1>(alpha) / 255.0), std::get<2>(color) * (std::get<2>(alpha) / 255.0),
		std::get<3>(color));
}*/

color sombra_rr(Objeto& o, Ray r, Punto interseccion, Punto normal, int depth){
	// color = término del ambiente;
	color c = color(0.1, 0.1, 0.1, 1.0);
	for(int i =0; i< cantLuces; i++){ // for (cada luz) {
		//	rayo_s = rayo desde el punto a la luz;
		Ray rayo_s;
		rayo_s.origen = interseccion;
		rayo_s.direccion = (luces[i] - interseccion).normalized();
		if (normal * rayo_s.direccion > 0) { //if(normal * (Punto(0,0,0)-rayo_s.direccion) > 0){ if (producto punto entre normal y dirección de la luz es positivo) {
			//calcular cuánta luz es bloqueada por sup. opacas y transp., y
			//usarlo para escalar los términos difusos y especulares antes de
			//añadirlos a color;
			//TODO
		}
	}
	return color(0.0, 0.0, 0.0, 1.0);
}

color traza_rr(Ray ray, int depth){
	std::pair<bool, Punto> colision = esfera.chequear_colision(ray);
	if(colision.first){
		//calcular la normal en la intersección;
		Punto normal = esfera.getNormal(colision.second);
		// return sombra_RR(obj. intersecado más cercano, rayo, intersección, normal, profundidad);
		return sombra_rr(esfera, ray, colision.second, normal, depth);
	} else {
		return color(0.0, 0.0, 0.0, 1.0);
	}
}

h_w_color render() {
	int altura = ALTO; //i
	int ancho = ANCHO; //j
	h_w_color color(
		altura,
		w_color(ancho, tuple<double, double, double, double>(0.0, 0.0, 0.0, 1.0)));
	Ray** rayos = camara.getRays(ancho, altura);
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < ancho; j++) {
			double incrementoI = (-i - 1) * (verticalSize / altura);
			double incrementoJ = (j + 1) * (horizontalSize / ancho);
			Ray ray = rayos[i][j];
			color[i][j] = traza_rr(ray, 1);
		}
	}
	return color;
}


int main() {
	luces = new Punto[2];
	luces[0] = Punto(1, 0, 1);
	luces[1] = Punto(-1, 0, -1);
	/*cout << "Ingresar nombre del archivo" << endl;
	cin >> s;
	if (s == "0") {
		s = "default";
	}
	*/

	//leer nombre del archivo xml
	string s = "default";
	s = "../xml/escenas/" + s + ".xml";
	////crear la escena
	//Escena e(s);

	//aplicar algoritmo
	//e.render();

	//renderizar y guardar en png
	int ancho = ANCHO;
	int alto = ALTO;
	h_w_color pixels = render();
	return renderizar(alto, ancho, pixels);
}