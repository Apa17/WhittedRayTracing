#include <string>
#include <iostream>
#include <tuple>
#include "Escena.h"
#include "Render.h"
#include "Camara.h"
#include "Punto.h"
#include "Esfera.h"
#include "Cilindro.h"
#include "Luz.h"
#include "color.h"
#include "../inc/malla_poligonal.h"

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

bool imprimi = false;
Objeto** objetos;
double cantObjetos;
Camara camara(Punto(0, 0, 0), Punto(0, 1, 0), Punto(0, 0, -1), verticalSize, horizontalSize); //replace this
Luz* luces;
Color ia = Color(0.2, 0.2, 0.2);
int depth_max = 7;
int cantLuces;
int iglobal;
int jglobal;
int iglobal_checkear = 240;
int jglobal_checkear = 458;

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
	Color c = ia * o->getColorDifuso() * o->getcoefAmbiente();
	Color color_s = c;
	Punto nNormalizado = normal.normalized();
	for(int i =0; i< cantLuces; i++) { // for (cada luz) {
		//	rayo_s = rayo desde el punto a la luz;
		Ray rayo_s;
		rayo_s.origen = interseccion + nNormalizado * 0.0001;
		rayo_s.indRefrac = r.indRefrac;
		rayo_s.direccion = (luces[i].posicion - interseccion).normalized();
		double NxL = nNormalizado * rayo_s.direccion;
		double distancia_luz = (luces[i].posicion - rayo_s.origen).getNorma_al_cuadrado();
		if (NxL > 0) {
			Color luz_visible = Color(1, 1, 1);
			bool luz_visible_bool = true;
			for(int j = 0; j < cantObjetos; j++){
				std::pair<bool, Punto> aux = objetos[j]->chequear_colision(rayo_s);
				if(aux.first && objetos[j] != o && distancia_luz > (aux.second - rayo_s.origen).getNorma_al_cuadrado()){
					luz_visible = (luz_visible + objetos[j]->getColorDifuso() * (1 - objetos[j]->getcoefTransm())) * objetos[j]->getcoefTransm();
					luz_visible_bool = false;
					if(objetos[j]->getcoefTransm() == 0){
						break;
					}
				}
			}
			double dl2 = distancia_entre_punto_al_cuadrado(interseccion, luces[i].posicion);
			double b = 0.02;
			double fatt = 1/(b*dl2);
			Color ip = luces[i].colour;
			color_s = color_s  + (ip * fatt * o->getcoefDifuso() * NxL * o->getColorDifuso());
			Punto V = (r.direccion.normalized() * - 1);
			Punto R = (nNormalizado * 2 * NxL) - rayo_s.direccion.normalized();
			double cosalfa = R * V;
			color_s = color_s + o->getColorEspecular() * o->getcoefReflex() * fatt * ip * pow(cosalfa,40);
			color_s = color_s * luz_visible;
		}
	}
	
	Color color_r = Color(0.0, 0.0, 0.0);
	Color color_t = Color(0.0, 0.0, 0.0);
	if(depth < depth_max){
		Punto V = r.direccion.normalized() * -1;
		double NxV = normal.normalized() * V;
		double angulo_incidencia = acos(abs(normal.normalized() * V)); //theta i o theta 1 segun el libro
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
			double angulo_salida = asin(n1/n2*sin(angulo_incidencia)); //theta t o theta 2 segun el libro
			double thetac = asin(n1 / n2); // theta c o angulo critico
			rayo_t.origen = interseccion + X;
			if(n1 > n2 || angulo_incidencia < thetac ){
				//sin(angulo_salida)*Perpendiular_normal - cos(angulo_incidencia)*normal
				Punto M = (nNormalizado*cos(angulo_incidencia) - V)/sin(angulo_incidencia);
				rayo_t.direccion = M*sin(angulo_salida) - nNormalizado* cos(angulo_salida);
				rayo_t.indRefrac = n2;
			}
			else {
				rayo_t.indRefrac = r.indRefrac;
				rayo_t.direccion = (nNormalizado * 2 * NxV) - V; 
			}
			if(iglobal == iglobal_checkear && jglobal == jglobal_checkear){
				std::cout << "angulo incidencia: " << angulo_incidencia << std::endl;
				std::cout << "theta c: " << thetac << std::endl;
				std::cout << "angulo salida: " << angulo_salida << std::endl;
				std::cout << "r.direccion: " << r.direccion << std::endl;
				// std::cout << "interseccion: " << interseccion << std::endl;
				std::cout << "rayo_t.origen: " << rayo_t.origen << std::endl;
				std::cout << "rayo_t.direccion: " << rayo_t.direccion << std::endl;
				std::cout << "depth: " << depth << std::endl;
				std::cout << "n1: " << n1 << std::endl;
				std::cout << "n2: " << n2 << std::endl;
				std::cout << "n1/n2: " << n1/n2 << std::endl;
			}
			color_t = traza_rr(rayo_t, depth + 1); // escalar color_r por el coeficiente especular y añadir al color;
			color_t = color_t * o->getcoefTransm();
		}
	}
	// c = c + color_s * o->getcoefDifuso() + color_r + color_t;
	c = c + color_s + color_r + color_t;
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
	if(iglobal == iglobal_checkear && jglobal == jglobal_checkear){
		std::cout << "id: " << id << endl;
	}
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

Color traza_rr_2(Ray ray, bool refraccion, Color fondo){
	int id = -1;
	std::pair<bool, Punto> colision_id = std::make_pair(false, Punto(0, 0, 0)); 
	for(int i = 0; i < cantObjetos; i++){
		std::pair<bool, Punto> colision = objetos[i]->chequear_colision(ray);
		if(colision.first && (id == -1 || distancia_entre_punto_al_cuadrado(ray.origen, colision.second) < distancia_entre_punto_al_cuadrado(ray.origen, colision_id.second))){
			id = i;
			colision_id = colision;
		}
	}

	if(colision_id.first){
		if(refraccion)
			return Color(1.0, 1.0, 1.0) * objetos[id]->getcoefTransm();
		return Color(1.0, 1.0, 1.0) * objetos[id]->getcoefReflex();
	} else {
		return fondo;
	}
}

h_w_color * render() {
	int altura = ALTO; //i
	int ancho = ANCHO; //j
	h_w_color color(
		altura,
		w_color(ancho, Color()));
	h_w_color coefs_refraccion_fondo_negro(
		altura,
		w_color(ancho, Color()));
	h_w_color coefs_reflexion_fondo_negro(
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
			coefs_reflexion_fondo_negro[i][j] = traza_rr_2(ray, false, Color(0,0,0));
			coefs_refraccion_fondo_negro[i][j] = traza_rr_2(ray, true, Color(0,0,0));
		}
	}
	h_w_color * res = new h_w_color[3];
	res[0] = color;
	res[1] = coefs_refraccion_fondo_negro;
	res[2] = coefs_reflexion_fondo_negro;
	return res;
}

void objetos_para_probar(){
	cantLuces = 2;
	luces = new Luz[cantLuces];
	luces[0] = Luz(Punto(0, -4, -2), Color(1.0, 1.0, 1.0));
	luces[1] = Luz(Punto(0, -4, -2), Color(1.0, 1.0, 1.0));
	Cilindro* cilindro = new Cilindro(1, 1, Punto(0, 0, -5), Punto(0,1,0), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.2, 0.8 ,0.0, 0.0, 1.5); //roja mitad refractiva mitad transmitiva
	
	Objeto * esfera = new Esfera(0.5, Punto(1.1, 0, -3), Color(0.0, 0.5, 0.0), Color(0.0, 0.5, 0.0), 0.01, 0.01, 0.0, 0.98, 1.5); // verde no fuerte
	Objeto * esfera2 = new Esfera(2, Punto(0, 0, -4), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.1, 0.9, 0.0, 0.0, 1.1); // gris
	Objeto * esfera3 = new Esfera(0.5, Punto(0, 0, 6), Color(1, 1, 1), Color(1, 1, 1), 0.1, 0.9, 0.0, 0.0, 1); // blanca
	//pared fondo
	Triangulo* triangulof = new Triangulo(Punto(-5, -5, -12), Punto(5, -5, -12), Punto(5, 5, -12), Color(0.0, 0.0, 0.5), Color(0.0, 0.0, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo* triangulo1f = new Triangulo(Punto(5, 5, -12), Punto(-5, 5, -12), Punto(-5, -5, -12), Color(0.0, 0.0, 0.5), Color(0.0, 0.0, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5); 
	Triangulo ** arrTriangulosf = new Triangulo*[2];
	arrTriangulosf[0] = triangulof;
	arrTriangulosf[1] = triangulo1f;
	Malla_Poligonal * mpfondo =  new Malla_Poligonal(arrTriangulosf, 2, Color(0.0, 0.0, 0.5), Color(0.0, 0.0, 0.5), 0.1, 0.9, 0.0, 0.0, 1.5);
	//pared frente (atras de la camara)
	Triangulo* triangulof2 = new Triangulo(Punto(5, 5, 2), Punto(5, -5, 2), Punto(-5, -5, 2), Color(0.0, 0.0, 0.5), Color(0.0, 0.0, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo* triangulo1f2 = new Triangulo(Punto(-5, -5, 2), Punto(-5, 5, 2), Punto(5, 5, 2),  Color(0.0, 0.0, 0.5), Color(0.0, 0.0, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5); 
	Triangulo ** arrTriangulosf2 = new Triangulo*[2];
	arrTriangulosf2[0] = triangulof2;
	arrTriangulosf2[1] = triangulo1f2;
	Malla_Poligonal * mpfrente =  new Malla_Poligonal(arrTriangulosf2, 2, Color(0.5, 0.0, 0.5), Color(0.5, 0.0, 0.5), 0.1, 0.9, 0.0, 0.0, 1.5);
	//pared izq
	Triangulo* trianguloi = new Triangulo(Punto(-5, -5, -12), Punto(-5, 5, 2), Punto(-5, -5, 2), Color(0.5, 0.0, 0), Color(0.5, 0.0, 0), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo* triangulo1i = new Triangulo(Punto(-5, -5, -12), Punto(-5, 5, -12), Punto(-5, 5, 2), Color(0.5, 0.0, 0), Color(0.5, 0.0, 0), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo** arrTriangulosi = new Triangulo * [2];
	arrTriangulosi[0] = trianguloi;
	arrTriangulosi[1] = triangulo1i;
	Malla_Poligonal* mpizq = new Malla_Poligonal(arrTriangulosi, 2, Color(0.0, 0.5, 0), Color(0.0, 0.5, 0), 0.1, 0.9, 0.0, 0.0, 1.5);
	//pared derecha
	Triangulo* triangulod = new Triangulo(Punto(5, -5, 2), Punto(5, 5, 2), Punto(5, -5, -12), Color(0.0, 0.5, 0), Color(0.0, 0.5, 0), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo* triangulo1d = new Triangulo(Punto(5, 5, 2), Punto(5, 5, -12), Punto(5, -5, -12), Color(0.0, 0.5, 0), Color(0.0, 0.5, 0.0), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo** arrTriangulosd = new Triangulo * [2];
	arrTriangulosd[0] = triangulod;
	arrTriangulosd[1] = triangulo1d;
	Malla_Poligonal* mpder = new Malla_Poligonal(arrTriangulosd, 2, Color(0.5, 0, 0), Color(0.5, 0, 0), 0.1, 0.9, 0.0, 0.0, 1.5);
	//pared arriba
	Triangulo* trianguloup = new Triangulo(Punto(-5, 5, -12), Punto(5, 5, -12), Punto(5, 5, 2), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo* triangulo1up = new Triangulo(Punto(5, 5, 2), Punto(-5, 5, 2), Punto(-5, 5, -12), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo** arrTriangulosup = new Triangulo * [2];
	arrTriangulosup[0] = trianguloup;
	arrTriangulosup[1] = triangulo1up;
	Malla_Poligonal* mpup = new Malla_Poligonal(arrTriangulosup, 2, Color(0.5, 0.5, 0), Color(0.5, 0.5, 0), 0.1, 0.9, 0.0, 0.0, 1.5);
	//pared abajo
	Triangulo* triangulodw = new Triangulo(Punto(5, -5, 2), Punto(5, -5, -12), Punto(-5, -5, -12), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo* triangulo1dw = new Triangulo(Punto(-5, -5, -12), Punto(-5, -5, 2), Punto(5, -5, 2), Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.0, 0.0, 0.0, 2.0, 1.5);
	Triangulo** arrTriangulosdw = new Triangulo * [2];
	arrTriangulosdw[0] = triangulodw;
	arrTriangulosdw[1] = triangulo1dw;
	Malla_Poligonal* mpdown = new Malla_Poligonal(arrTriangulosdw, 2, Color(0.5, 0.5, 0.5), Color(0.5, 0.5, 0.5), 0.1, 0.9, 0.0, 0.0, 1.5);
	cantObjetos = 8;
	objetos = new Objeto*[cantObjetos];
	objetos[0] = esfera;
	objetos[1] = mpfrente;
	objetos[2] = mpfondo;
	objetos[3] = mpizq;
	objetos[4] = mpder;
	objetos[5] = mpup;
	objetos[6] = mpdown;
	objetos[7] = cilindro;
	//objetos[7] = esfera2;
	//objetos[8] = esfera3;
}

int main() {
	objetos_para_probar();
	//objetos[0] = &cilindro;
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
	h_w_color * pixels = render();
	return renderizar(alto, ancho, pixels);
	// return 0;
}