#include <string>
#include <iostream>
#include "Escena.h"
#include <tuple>
#include "Render.h"
#include "Camara.h"
#include "Punto.h"
#include "Esfera.h"
#include "Luz.h"
#include "color.h"

#define ANCHO 500;
#define ALTO 500;
double verticalSize = 1;
double horizontalSize = 1;

Camara camara(Punto(0, 0, 0), Punto(0, 1, 0), Punto(0, 0, -1), verticalSize, horizontalSize); //replace this
Esfera esfera(1, Punto(0, 0, -5), color(0.6, 0.6, 0.6, 1.0), 1.0, 0.0, 1.0); //replace this
Luz* luces;
color ia = color(0.1, 0.1, 0.1, 1.0);
double ka = 1;
double kd = 1;
int depth_max = 3;
int cantLuces;

color sombra_rr(Objeto& o, Ray r, Punto interseccion, Punto normal, int depth){
	// color = término del ambiente;
	color c = ia;
	for(int i =0; i< cantLuces; i++){ // for (cada luz) {
		//	rayo_s = rayo desde el punto a la luz;
		Ray rayo_s;
		rayo_s.origen = interseccion;
		rayo_s.direccion = (luces[i].posicion - interseccion).normalized();
		double NxL = normal * rayo_s.direccion;
		if (NxL > 0) { //if(normal * (Punto(0,0,0)-rayo_s.direccion) > 0){ if (producto punto entre normal y dirección de la luz es positivo) {
			// TODO COLISIONES CON OBJETOS ENTRE LA INTERSECCION DEL OBJETO Y LUZ
			double dl2 = distancia_entre_punto_al_cuadrado(interseccion, luces[i].posicion);
			double b = 0.01;
			double fatt = 1/(b*dl2);
			//std::cout << fatt << std::endl;
			color ip = luces[i].colour;
			// TODO LUZ ESPECULAR
			// std::cout << sqrt(dl2) << std::endl;
			c = sumar_color(c, multiplicar_color(multiplicar_color(multiplicar_color(ip,fatt),kd),NxL));
		}
	}
	
	if(depth < depth_max){
		color color_r;
		if(o.getcoefReflex() > 0){
			//r, n
			Ray rayo_r;
			rayo_r.origen = interseccion;
			double angulo_incidencia = acos(normal.normalized() * r.direccion.normalized()); 
			Punto nNormalizado = normal.normalized();
			double NxL = normal.normalized() * r.direccion.normalized();
			// rayo_r = rayo en la dirección de reflexión desde punto;
			rayo_r.direccion = (nNormalizado * 2 * NxL) - r.direccion;
			color_r = traza_rr(rayo_r, depth + 1);
			// TODO
			// escalar color_r por el coeficiente especular y añadir al color;  
		}
		color color_t;
		// if(o.getcoefTransm() > 0){
		// 	if (no ocurre la reflexión interna total) {
		// 		// rayo_t = rayo en la dirección de refracción desde punto;
		// 		Ray rayo_t;
		// 		rayo_t.origen = interseccion;
		// 		rayo_t.direccion = 
		// 		color_t = traza_RR (rayo_t, profundidad + 1);
		// 		escalar color_t por el coeficiente de transmisión y
		// 		añadir a color;
		// 	}
		// }
	}
	c = normalizar_color(c);
	c = multiplicar_color(c, o.getColor());
	return c;
}

color traza_rr(Ray ray, int depth){
	std::pair<bool, Punto> colision = esfera.chequear_colision(ray);
	if(colision.first){
		//calcular la normal en la intersección;
		Punto normal = esfera.getNormal(colision.second);
		// return sombra_RR(obj. intersecado más cercano, rayo, intersección, normal, profundidad);
		return sombra_rr(esfera, ray, colision.second, normal, depth);
		//return color(0.6, 0.6, 0.6, 1.0);
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
			color[i][j] = multiplicar_color(traza_rr(ray, 1), 255);
		}
	}
	return color;
}


int main() {
	luces = new Luz[2];
	luces[0] = Luz(Punto(0, 0, 1), color(1.0, 1.0, 1.0, 1.0));
	luces[1] = Luz(Punto(0, 0, -1), color(1.0, 1.0, 1.0, 1.0));
	cantLuces = 2;
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