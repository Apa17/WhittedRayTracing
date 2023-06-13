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

Objeto** objetos;
double cantObjetos;
Camara camara(Punto(0, 0, 0), Punto(0, 1, 0), Punto(0, 0, -1), verticalSize, horizontalSize); //replace this
Luz* luces;
color ia = color(0.1, 0.1, 0.1, 1.0);
double ka = 1;
double kd = 1;
int depth_max = 7;
int cantLuces;
int iglobal;
int jglobal;

color traza_rr(Ray ray, int depth);

color sombra_rr(Objeto* o, Ray r, Punto interseccion, Punto normal, int depth){
	// Rayo vista = r.origen
	// Ri = vector reflejado
	// Os lambda el color del objeto (color especular)
	// Od lambda el color del objeto (color difuso)
	// color = término del ambiente;
	color c = ia;
	Punto L = r.direccion.normalized() * -1;
	Ray rayo_r;
	rayo_r.origen = interseccion + normal.normalized() * 0.0001;
	rayo_r.indRefrac = r.indRefrac;
	Punto nNormalizado = normal.normalized();
	double NxL = normal.normalized() * L;
	rayo_r.direccion = (nNormalizado * 2 * NxL) - L;
	for(int i =0; i< cantLuces; i++){ // for (cada luz) {
		//	rayo_s = rayo desde el punto a la luz;
		Ray rayo_s;
		rayo_s.origen = interseccion;
		rayo_s.direccion = (luces[i].posicion - interseccion).normalized();
		rayo_s.indRefrac = r.indRefrac;
		double NxL = normal * rayo_s.direccion;
		if (NxL > 0) { //if(normal * (Punto(0,0,0)-rayo_s.direccion) > 0){ if (producto punto entre normal y dirección de la luz es positivo) {
			// TODO cambiar esto
			bool luz_visible = true; 
			for(int j = 0; j < cantObjetos; j++){
				if(objetos[j]->chequear_colision(rayo_s).first && objetos[j] != o){
					luz_visible = false;
					break;
				}
			}
			if(luz_visible){
				double dl2 = distancia_entre_punto_al_cuadrado(interseccion, luces[i].posicion);
				double b = 0.04;
				double fatt = 1/(b*dl2);
				color ip = luces[i].colour;
				// TODO LUZ ESPECULAR
				c = multiplicar_color(sumar_color(c, multiplicar_color(multiplicar_color(multiplicar_color(ip,fatt),kd),NxL)), o->getColorDifuso());
				double x = rayo_r.direccion * r.direccion;
				c = sumar_color(c, multiplicar_color(o->getColorEspecular(), pow(x,40)));
			}
		}
	}
	
	color color_r = color(0.0, 0.0, 0.0, 1.0);
	color color_t = color(0.0, 0.0, 0.0, 1.0);
	if(depth < depth_max){
		double angulo_incidencia = acos(normal.normalized() * L);
		if(o->getcoefReflex() > 0){
			
			color_r = traza_rr(rayo_r, depth + 1);
			color_r = multiplicar_color(color_r, o->getcoefReflex()); // escalar color_r por el coeficiente especular y añadir al color;  			
		}
		if(o->getcoefTransm() > 0){
			double n1 = r.indRefrac;
			double n2 = o->getindRefrac();
			double thetac = asin(n1/n2);
			// if (iglobal == 251 && jglobal == 251) {
			// 	std::cout << "	angulo incidencia: " << angulo_incidencia << std::endl;
			// 	std::cout << "	thetac: " << thetac << std::endl;
			// 	bool condicion = angulo_incidencia < thetac;
			// 	std::cout << "	condicion: " << condicion << std::endl;
			// }
			if(angulo_incidencia < thetac){
				double thetat = asin(sin(angulo_incidencia)*n1/n2); //0
				Punto proLn;
				if(normal.normalized() == L)
					proLn = normal;
				else
					proLn = L - (normal.normalized() * (normal.normalized() * L));
				Punto G = proLn/sin(angulo_incidencia);
				Ray rayo_t;
				rayo_t.origen = interseccion - normal.normalized() * 0.0001;
				Punto lado_izq_ecua = normal * -1 * cos(thetat);
				Punto lado_der_ecua = G * sin(thetat);
				rayo_t.direccion = lado_izq_ecua - lado_der_ecua;
				// if (iglobal == 251 && jglobal == 251) {
				// 	std::cout << "	interseccion: " << interseccion << std::endl;
				// 	std::cout << "	r.direccion.normalized(): " << r.direccion.normalized() << std::endl;
				// 	std::cout << "	normal.normalized()" << normal.normalized() << std::endl;
				// 	std::cout << "	proLn: " << proLn << std::endl;
				// 	std::cout << "	normal: " << normal << std::endl;
				// 	std::cout << "	thetat: " << thetat << std::endl;
				// 	std::cout << "	cos(thetat): " << cos(thetat) << std::endl;
				// 	std::cout << "	sin(thetat): " << sin(thetat) << std::endl;
				// 	std::cout << "	rayo_t.direccion: " << rayo_t.direccion << std::endl;
				// 	std::cout << "	lado_izq_ecua: " << lado_izq_ecua << std::endl;
				// 	std::cout << "	lado_der_ecua: " << lado_der_ecua << std::endl;
				// 	std::cout << "	sin(angulo_incidencia): " << sin(angulo_incidencia) << std::endl;
				// 	std::cout << "	G: " << G << std::endl;
				// }
				rayo_t.indRefrac = n2;
				color_t = traza_rr (rayo_t, depth + 1);
				color_t = multiplicar_color(color_t, o->getcoefTransm()); // escalar color_t por el coeficiente de transmisión y añadir a color;				
			}
		}
	}
	// TODO PREGUNTAR PROFE
	c = sumar_color(c, color_r);
	c = sumar_color(c, color_t);
	c = normalizar_color(c);
	return c;
}

color traza_rr(Ray ray, int depth){
	int id = -1;
	std::pair<bool, Punto> colision_id = std::make_pair(false, Punto(0, 0, 0)); 
	for(int i = 0; i < cantObjetos; i++){
		std::pair<bool, Punto> colision = objetos[i]->chequear_colision(ray);
		if(colision.first && (id == -1 || distancia_entre_punto_al_cuadrado(ray.origen, colision.second) < distancia_entre_punto_al_cuadrado(ray.origen, colision_id.second))){
			id = i;
			colision_id = colision;
		}
	}
	if(iglobal == 251 && jglobal == 251){
		std::cout << "id: " << id << endl;
		std::cout << "colision_id.first: " << colision_id.first << endl;
		std::cout << "colision_id.second: " << colision_id.second << endl;
		std::cout << "ray.origen: " << ray.origen << endl;
		std::cout << "ray.direccion: " << ray.direccion << endl;
		std::cout << "ray.indRefrac: " << ray.indRefrac << endl;
		std::cout << "depth: " << depth << endl;
		if(colision_id.first){
			Punto normal = objetos[id]->getNormal(colision_id.second);
			std::cout << "normal: " << normal << endl;
		}
	}
	if(colision_id.first){
		//calcular la normal en la intersección;
		Punto normal = objetos[id]->getNormal(colision_id.second);
		// return sombra_RR(obj. intersecado más cercano, rayo, intersección, normal, profundidad);
		return sombra_rr(objetos[id], ray, colision_id.second, normal, depth);
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
			iglobal = i;
			jglobal = j;
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
	luces[0] = Luz(Punto(0, 0, 3), color(1.0, 1.0, 1.0, 1.0));
	luces[1] = Luz(Punto(0, 0, 3), color(1.0, 1.0, 1.0, 1.0));
	cantLuces = 2;
	Esfera esfera = Esfera(1, Punto(0, 1, -3), color(0.6, 0.6, 0.6, 1.0), color(0.6, 0.6, 0.6, 1.0), 1.0, 0.0, 1.5); //replace this
	Esfera esfera2 = Esfera(1, Punto(0, -1, -3), color(1.0, 0.0, 0.0, 1.0), color(0.6, 0.6, 0.6, 1.0), 1.0, 0.0, 1.5); //replace this
	cantObjetos = 2;
	objetos = new Objeto*[cantObjetos];
	objetos[0] = &esfera;
	objetos[1] = &esfera2;
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