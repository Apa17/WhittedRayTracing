#include <string>
#include <iostream>
#include "Escena.h"
#include <tuple>
#include "Render.h"
#include "Camara.h"
#include "Punto.h"
#include "Esfera.h"
#include "Cilindro.h"
#include "Luz.h"
#include "color.h"

#define ANCHO 500; //para probar
#define ALTO 500;
double horizontalSize = 1;
double verticalSize = 1;

// #define ANCHO 1920; //full hd
// #define ALTO 1080;
// double horizontalSize = 1.920;
// double verticalSize = 1.080;

// #define ANCHO 3840; //4k
// #define ALTO 2160;
// double horizontalSize = 1.920;
// double verticalSize = 1.080;
//
bool imprimi = false;
Objeto** objetos;
double cantObjetos;
Camara camara(Punto(0, 0, 0), Punto(0, 1, 0), Punto(0, 0, -1), verticalSize, horizontalSize); //replace this
Luz* luces;
Color ia = Color(0.2, 0.2, 0.2);
double ka = 1;
double kd = 0.5;
double ks = 0.5;
double kt = 0.5;
int depth_max = 7;
int cantLuces;
int iglobal;
int jglobal;

//double get_indice_refraccion(Punto x){
//	double res = 1;
//	for(int i = 0; i < cantObjetos; i++){
//		if(objetos[i]->isInside(x)){
//			if(objetos[i]->getindRefrac() > res){
//				res = objetos[i]->getindRefrac();
//			}
//		};
//	}
//}

Color traza_rr(Ray ray, int depth);

Color sombra_rr(int id, Ray r, Punto interseccion, Punto normal, int depth){
	// Rayo vista = r.origen
	// Ri = vector reflejado
	// Os lambda el color del objeto (color especular)
	// Od lambda el color del objeto (color difuso)
	// Ip color de la fuente de luz??? // TODO Preguntar profe por las dudas
	// color = término del ambiente;
	Objeto * o = objetos[id];
	Color c = ia * o->getColorDifuso();
	Color color_s = c;
	Punto nNormalizado = normal.normalized();
	for(int i =0; i< cantLuces; i++) { // for (cada luz) {
		//	rayo_s = rayo desde el punto a la luz;
		Ray rayo_s;
		rayo_s.origen = interseccion + nNormalizado * 0.0001;
		rayo_s.indRefrac = r.indRefrac;
		rayo_s.direccion = (luces[i].posicion - interseccion).normalized();
		double NxL = nNormalizado * rayo_s.direccion;
		if (NxL > 0) {
			Color luz_visible = Color(1, 1, 1);
			bool luz_visible_bool = true;
			for(int j = 0; j < cantObjetos; j++){
				if(objetos[j]->chequear_colision(rayo_s).first && objetos[j] != o){
					luz_visible = luz_visible * objetos[j]->getcoefTransm() + objetos[j]->getColorDifuso() * (1 - objetos[j]->getcoefTransm());
					luz_visible_bool = false;
					if(objetos[j]->getcoefTransm() == 0){
						break;
					}
				}
			}
			double dl2 = distancia_entre_punto_al_cuadrado(interseccion, luces[i].posicion);
			double b = 0.04;
			double fatt = 1/(b*dl2);
			Color ip = luces[i].colour;
			color_s = color_s  + (ip * fatt * kd * NxL * o->getColorDifuso());
			Punto V = (r.direccion.normalized() * - 1);
			Punto R = (nNormalizado * 2 * NxL) - rayo_s.direccion.normalized();
			double cosalfa = R * V;
			color_s = color_s + o->getColorEspecular() * ks * fatt * ip * pow(cosalfa,40);
			color_s = color_s * luz_visible;
		}
	}
	
	Color color_r = Color(0.0, 0.0, 0.0);
	Color color_t = Color(0.0, 0.0, 0.0);
	if(depth < depth_max){
		Punto V = r.direccion.normalized() * -1;
		double NxV = normal.normalized() * V;
		double angulo_incidencia = acos(abs(normal.normalized() * V));
		if(o->getcoefReflex() > 0){
			Ray rayo_r;	
			rayo_r.origen = interseccion + normal.normalized() * 0.0001;
			rayo_r.indRefrac = r.indRefrac;
			rayo_r.direccion = (nNormalizado * 2 * NxV) - V;
			color_r = traza_rr(rayo_r, depth + 1);
			color_r = color_r * o->getcoefReflex(); // escalar color_r por el coeficiente especular y añadir al color;
		}
		if(o->getcoefTransm() > 0){
			Punto X;
			double n2;
			Ray rayo_t;
			if (nNormalizado * V > 0){
				X = nNormalizado * -0.001;
				n2 = o->getindRefrac();
			}
			else {
				X = nNormalizado * 0.001;
				n2 = 1;
			}
			double n1 = r.indRefrac;
			double angulo_salida = asin(n1/n2*sin(angulo_incidencia));
			double thetac = asin(n1 / n2);
			if(angulo_incidencia < thetac){
				//sin(angulo_salida)*Perpendiular_normal - cos(angulo_incidencia)*normal
				Punto M = nNormalizado*cos(angulo_incidencia) - V;
				rayo_t.direccion = M - nNormalizado* cos(angulo_incidencia);
				rayo_t.origen = interseccion + X;
				rayo_t.indRefrac = 1;
				// double thetat = asin(sin(angulo_incidencia)*n1/n2); //0
				// Punto proLn;
				// if(normal.normalized() == V)
				// 	proLn = normal.normalized();
				// else
				// 	proLn = V - (normal.normalized() * (normal.normalized() * V));
				// Punto G = proLn/sin(angulo_incidencia);
				// Ray rayo_t;
				// rayo_t.origen = interseccion - normal.normalized() * 0.0001;
				// Punto lado_izq_ecua = normal * -1 * cos(thetat);
				// Punto lado_der_ecua = G * sin(thetat);
				// rayo_t.direccion = lado_izq_ecua - lado_der_ecua;
				//if (depth == 2) {
				// 	std::cout << "	interseccion: " << interseccion << std::endl;
				// 	std::cout << "	r.direccion.normalized(): " << r.direccion.normalized() << std::endl;
				// 	std::cout << "	normal.normalized()" << normal.normalized() << std::endl;
				// 	std::cout << "	normal: " << normal << std::endl;
				// 	std::cout << "	rayo_t.direccion: " << rayo_t.direccion << std::endl;
				// 	std::cout << "	sin(angulo_incidencia): " << sin(angulo_incidencia) << std::endl;
				//}
				// rayo_t.indRefrac = n2;		
			}
			else {
				rayo_t.origen = interseccion - X;
				rayo_t.indRefrac = r.indRefrac;
				rayo_t.direccion = (nNormalizado * 2 * NxV) - V; 
			}
			color_t = traza_rr(rayo_t, depth + 1); // escalar color_r por el coeficiente especular y añadir al color;
			color_t = color_t * o->getcoefTransm();
		}
	}
	// TODO PREGUNTAR PROFE
	// c = sumar_color(c, color_r);
	c = color_s * (1 - o->getcoefTransm() - o->getcoefReflex()) + color_r + color_t;
	return c.normalizar_color();
}

Color traza_rr(Ray ray, int depth){
	if(depth > depth_max){
		return Color(0.1, 0.1, 0.1);
	}

	int id = -1;
	std::pair<bool, Punto> colision_id = std::make_pair(false, Punto(0, 0, 0)); 
	for(int i = 0; i < cantObjetos; i++){
		std::pair<bool, Punto> colision = objetos[i]->chequear_colision(ray);
		if(colision.first && (id == -1 || distancia_entre_punto_al_cuadrado(ray.origen, colision.second) < distancia_entre_punto_al_cuadrado(ray.origen, colision_id.second))){
			id = i;
			colision_id = colision;
		}
	}
	// if(iglobal == 251 && jglobal == 251){
	// 	std::cout << "id: " << id << endl;
	// 	std::cout << "colision_id.first: " << colision_id.first << endl;
	// 	std::cout << "colision_id.second: " << colision_id.second << endl;
	// 	std::cout << "ray.origen: " << ray.origen << endl;
	// 	std::cout << "ray.direccion: " << ray.direccion << endl;
	// 	std::cout << "ray.indRefrac: " << ray.indRefrac << endl;
	// 	std::cout << "depth: " << depth << endl;
	// 	if(colision_id.first){
	// 		Punto normal = objetos[id]->getNormal(colision_id.second);
	// 		std::cout << "normal: " << normal << endl;
	// 	}
	// }
	if(colision_id.first){
		//calcular la normal en la intersección;
		Punto normal = objetos[id]->getNormal(colision_id.second);
		// return sombra_RR(obj. intersecado más cercano, rayo, intersección, normal, profundidad);
		return sombra_rr(id, ray, colision_id.second, normal, depth);
		//return color(0.6, 0.6, 0.6, 1.0);
	} else {
		return Color(0.0, 0.0, 0.0);
	}
}

h_w_color render() {
	int altura = ALTO; //i
	int ancho = ANCHO; //j
	h_w_color color(
		altura,
		w_color(ancho, Color()));
	Ray** rayos = camara.getRays(ancho, altura);
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < ancho; j++) {
			iglobal = i;
			jglobal = j;
			double incrementoI = (-i - 1) * (verticalSize / altura);
			double incrementoJ = (j + 1) * (horizontalSize / ancho);
			Ray ray = rayos[i][j];
			color[i][j] = traza_rr(ray, 1);
		}
	}
	return color;
}


int main() {
	luces = new Luz[1];
	luces[0] = Luz(Punto(-1, 1, 0), Color(1.0, 1.0, 1.0));
	luces[1] = Luz(Punto(-1, 1, 0), Color(1.0, 1.0, 1.0));
	cantLuces = 2;
	// Esfera esfera = Esfera(0.5, Punto(-1, 0, -3), Color(0.0, 1.0, 0.0), Color(0.0, 1.0, 0.0), 1.0, 0.0, 1.5); //verde refractiva 100%
	// Esfera esfera2 = Esfera(0.5, Punto(0, 1, -3), Color(1.0, 0.0, 0.0), Color(1.0, 0.0, 0.0), 0.5, 0.5, 1.5); //roja mitad refractiva mitad transmitiva
	Esfera esfera3 = Esfera(2, Punto(2, 1, 0), Color(1, 1, 1), Color(1, 1, 1), 0.0, 0.0, 1); //azul transmitiva 100%
	Esfera esfera = Esfera(0.5, Punto(0, 0, -2), Color(0.0, 0.5, 0.0), Color(0.0, 0.5, 0.0), 0.0, 0.9, 1.5); //verde refractiva 100%
	Esfera esfera2 = Esfera(2, Punto(0, 0, -5), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.0, 0.0, 1); //roja mitad refractiva mitad transmitiva
	//Cilindro cilindro = Cilindro(1, 2, Punto(0, 0, -5), Punto(0,1,0), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.0, 0.0, 1.5); //roja mitad refractiva mitad transmitiva
	// Ray j;
	// j.indRefrac = esfera2.getindRefrac();
	// j.direccion = Punto(0, 0, -1);
	// j.origen = Punto(0, 0, -3);
	// std::cout << esfera2.chequear_colision(j).first << esfera2.chequear_colision(j).second << endl;
	// Esfera esfera3 = Esfera(0.5, Punto(1, 0, -3), Color(0.0, 0.0, 1.0), Color(0.0, 0.0, 1.0), 0.0, 0.0, 1.5); //azul transmitiva 100%
	cantObjetos = 3;
	objetos = new Objeto*[cantObjetos];
	objetos[0] = &esfera;
	//objetos[0] = &cilindro;
	objetos[1] = &esfera2;
	objetos[2] = &esfera3;
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
	// return 0;
}