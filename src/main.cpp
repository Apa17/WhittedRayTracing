#include <string>
#include <iostream>
#include "Escena.h"
#include <tuple>
#include "Render.h"

using namespace std;
using h_w_color = std::vector<std::vector<std::tuple<double, double, double, double>>>;
using w_color = std::vector<std::tuple<double, double, double, double>>;

double verticalSize = 5;
double horizontalSize = 5;

/*tuple<double, double, double, double> escalarColor(tuple<double, double, double, double> color, tuple<double, double, double, double> alpha) {
	return tuple<double, double, double, double>(std::get<0>(color) * (std::get<0>(alpha) / 255.0),
		std::get<1>(color) * (std::get<1>(alpha) / 255.0), std::get<2>(color) * (std::get<2>(alpha) / 255.0),
		std::get<3>(color));
}*/

h_w_color render() {
	int altura = 500; //i
	int ancho = 500; //j
	h_w_color color(
		500,
		w_color(500, tuple<double, double, double, double>(0.0, 0.0, 0.0, 1.0)));
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < ancho; j++) {
			double incrementoI = (-i - 1) * (verticalSize / altura);
			double incrementoJ = (j + 1) * (horizontalSize / ancho);
			//Punto* dirRayo = (new Punto(cam->getcenterOfViewPlane()->getX(), (cam->getverticalSize() / 2) + incrementoI - (cam->getverticalSize() / (altura * 2)), (-cam->gethorizontalSize() / 2) + incrementoJ - (cam->gethorizontalSize() / (ancho * 2))))->sub(cam->getposCamara()); //el 6 corresponde a la distancia en x de posCamara y planoVista. Restar posCamara.
			//Ray* rayo = new Ray(cam->getposCamara(), dirRayo);
			////std::cout << rayo->getdirection()->getX() << endl;
			//color[i][j] = traza_rr(rayo, 1);
		}
	}
	return color;
}


int main() {
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
	h_w_color testPixels = render();
	return renderizar(500, 500, testPixels);
}