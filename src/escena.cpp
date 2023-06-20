#include "Escena.h"
#include "tinyxml2.h"
#include <tuple>
#include "Camara.h"
#include "Punto.h"
#include "Esfera.h"
#include "Cilindro.h"
#include "Luz.h"
#include "color.h"
#include "../inc/malla_poligonal.h"
#include "Render.h"

using namespace std;
using namespace tinyxml2;

// #define ANCHO 500; //para probar
// #define ALTO 500;
// double horizontalSize = 1;
// double verticalSize = 1;

// #define ANCHO 1920; //full hd
// #define ALTO 1080;
// double horizontalSize = 1.920;
// double verticalSize = 1.080;

// #define ANCHO 3840; //4k
// #define ALTO 2160;
// double horizontalSize = 1.920;
// double verticalSize = 1.080;

Color ia = Color(0.2, 0.2, 0.2);
int iglobal;
int jglobal;
int iglobal_checkear = 240;
int jglobal_checkear = 458;

Color Escena::sombra_rr(Objeto* o, Ray r, Punto interseccion, Punto normal, int depth){
	// Rayo vista = r.origen
	// Ri = vector reflejado
	// Os lambda el color del objeto (color especular)
	// Od lambda el color del objeto (color difuso)
	// Ip color de la fuente de luz??? // TODO Preguntar profe por las dudas
	// color = término del ambiente;
	Color c = ia * o->getColorDifuso() * o->getcoefAmbiente();
	Color color_s = c;
	Punto nNormalizado = normal.normalized();
	for(Luz l: luces) { // for (cada luz) {
		//	rayo_s = rayo desde el punto a la luz;
		Ray rayo_s;
		rayo_s.origen = interseccion + nNormalizado * 0.0001;
		rayo_s.indRefrac = r.indRefrac;
		rayo_s.direccion = (l.posicion - interseccion).normalized();
		double NxL = nNormalizado * rayo_s.direccion;
		double distancia_luz = (l.posicion - rayo_s.origen).getNorma_al_cuadrado();
		if (NxL > 0) {
			Color luz_visible = Color(1, 1, 1);
			bool luz_visible_bool = true;
			for(Objeto* obj: objetos){
				std::pair<bool, Punto> aux = obj->chequear_colision(rayo_s);
				if(aux.first && obj != o && distancia_luz > (aux.second - rayo_s.origen).getNorma_al_cuadrado()){
					luz_visible = (luz_visible + obj->getColorDifuso() * (1 - obj->getcoefTransm())) * obj->getcoefTransm();
					luz_visible_bool = false;
					if(obj->getcoefTransm() == 0){
						break;
					}
				}
			}
			double dl2 = distancia_entre_punto_al_cuadrado(interseccion, l.posicion);
			double b = 0.0000002;
			double fatt = 1;
			Color ip = l.colour;
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
	c = c + color_s + color_r + color_t;
	return c.normalizar_color();
}

Color Escena::traza_rr(Ray ray, int depth){
	if(depth > depth_max){
		return Color(0.1, 0.1, 0.1);
	}

	std::pair<bool, Punto> colision_id = std::make_pair(false, Punto(0, 0, 0)); 
	Objeto* oid = nullptr;
	for(Objeto* o : objetos){
		std::pair<bool, Punto> colision = o->chequear_colision(ray);
		if(colision.first && (oid == nullptr || distancia_entre_punto_al_cuadrado(ray.origen, colision.second) < distancia_entre_punto_al_cuadrado(ray.origen, colision_id.second))){
			oid = o;
			colision_id = colision;
		}
	}
	if(colision_id.first){
		//calcular la normal en la intersección;
		Punto normal = oid->getNormal(colision_id.second);
		// return sombra_RR(obj. intersecado más cercano, rayo, intersección, normal, profundidad);
		return sombra_rr(oid, ray, colision_id.second, normal, depth);
		//return color(0.6, 0.6, 0.6, 1.0);
	} else {
		return Color(0.0, 0.0, 0.0);
	}
}

Color Escena::traza_rr_2(Ray ray, bool refraccion, Color fondo){
	Objeto* oid = nullptr;
	std::pair<bool, Punto> colision_id = std::make_pair(false, Punto(0, 0, 0)); 
	for(Objeto* o : objetos){
		std::pair<bool, Punto> colision = o->chequear_colision(ray);
		if(colision.first && (oid == nullptr || distancia_entre_punto_al_cuadrado(ray.origen, colision.second) < distancia_entre_punto_al_cuadrado(ray.origen, colision_id.second))){
			oid = o;
			colision_id = colision;
		}
	}

	if(colision_id.first){
		if(refraccion)
			return Color(1.0, 1.0, 1.0) * oid->getcoefTransm();
		return Color(1.0, 1.0, 1.0) * oid->getcoefReflex();
	} else {
		return fondo;
	}
}

int Escena::render() {
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
    return renderizar(altura, ancho, res);
}

Escena::Escena(string s) {	
    XMLDocument doc;
	doc.LoadFile(s.c_str());
	vector<Objeto*> newobjetos;
	vector<Luz> newluces;
	this->depth_max = 7;
	XMLElement * xmlEscena = doc.RootElement();
	if (!xmlEscena) {
		throw std::runtime_error("No se encontro la escena");
	}
	this->ancho = stoi(xmlEscena->FirstChildElement("AnchoImagen")->GetText());
	this->altura = stoi(xmlEscena->FirstChildElement("AlturaImagen")->GetText());
	XMLElement* xmlCamara = xmlEscena->FirstChildElement("camara");
	if(xmlCamara != NULL){
		//cargar camara
		double xAux, yAux, zAux;
		const char* xAuxchar; 
		const char* yAuxchar;
		const char* zAuxchar;
		XMLElement * aux;
		aux = xmlCamara->FirstChildElement("posicion");
		xAuxchar = aux->FirstChildElement("x")->GetText();
		xAux = stod(xAuxchar);
		yAuxchar = aux->FirstChildElement("y")->GetText();
		yAux = stod(yAuxchar);
		zAuxchar = aux->FirstChildElement("z")->GetText();
		zAux = stod(zAuxchar);
		Punto posCamara = Punto(xAux, yAux, zAux);


		aux = xmlCamara->FirstChildElement("lookAtVector");
		xAuxchar = aux->FirstChildElement("x")->GetText();
		xAux = stod(xAuxchar);
		yAuxchar = aux->FirstChildElement("y")->GetText();
		yAux = stod(yAuxchar);
		zAuxchar = aux->FirstChildElement("z")->GetText();
		zAux = stod(zAuxchar);
		Punto lookAtCamara = Punto(xAux, yAux, zAux);

		aux = xmlCamara->FirstChildElement("upVector");
		xAuxchar = aux->FirstChildElement("x")->GetText();
		xAux = stod(xAuxchar);
		yAuxchar = aux->FirstChildElement("y")->GetText();
		yAux = stod(yAuxchar);
		zAuxchar = aux->FirstChildElement("z")->GetText();
		zAux = stod(zAuxchar);
		Punto upVector = Punto(xAux, yAux, zAux);

		const char* auxChar;
		auxChar = xmlCamara->FirstChildElement("horizontalSize")->GetText();
		this->horizontalSize = stod(auxChar);
		auxChar = xmlCamara->FirstChildElement("verticalSize")->GetText();
		this->verticalSize = stod(auxChar);
		this->camara = Camara(posCamara, upVector, lookAtCamara, verticalSize, horizontalSize);
	}else{
		throw std::runtime_error("No se encontro la camara");
	}
	XMLElement* xmlLuces = xmlEscena->FirstChildElement("luces");
	if(xmlLuces != NULL) {
		//cargar luces
		XMLElement* xmlLuz = xmlLuces->FirstChildElement("luz");
		if(!xmlLuz){
			throw std::runtime_error("No se encontro la luz");
		}
		while (xmlLuz) {
			//cargar luz
			double x, y, z, r, g, b, a;
			const char* xChar;
			const char* yChar;
			const char* zChar;
			const char* rChar;
			const char* gChar;
			const char* bChar;

			XMLElement* xmlPosicion = xmlLuz->FirstChildElement("posicion");
			xChar = xmlPosicion->FirstChildElement("x")->GetText();
			yChar = xmlPosicion->FirstChildElement("y")->GetText();
			zChar = xmlPosicion->FirstChildElement("z")->GetText();
			x = stod(xChar);
			y = stod(yChar);
			z = stod(zChar);
			Punto p = Punto(x, y, z);

			XMLElement* xmlColor = xmlLuz->FirstChildElement("color");
			rChar = xmlColor->FirstChildElement("r")->GetText();
			gChar = xmlColor->FirstChildElement("g")->GetText();
			bChar = xmlColor->FirstChildElement("b")->GetText();
			r = stod(rChar);
			g = stod(gChar);
			b = stod(bChar);

			Color rgb = Color(r/255,g/255,b/255);

			Luz luz = Luz(p, rgb);
			newluces.push_back(luz);

			//siguiente
			xmlLuz = xmlLuz->NextSiblingElement("luz");
		}
	}
	XMLElement* xmlObjetos = xmlEscena->FirstChildElement("objetos");
	if(xmlObjetos != NULL) {
		XMLElement* xmlEsfera = xmlObjetos->FirstChildElement("esfera");
		while (xmlEsfera)
		{
			//cargar esfera
			double radio, xcentro, ycentro, zcentro, r, g, b, a, ka, kd, ks, kt;
			const char* qAuxChar; 

			qAuxChar = xmlEsfera->FirstChildElement("radio")->GetText();
			radio = stod(qAuxChar);

			qAuxChar = xmlEsfera->FirstChildElement("centro")->FirstChildElement("x")->GetText();
			xcentro = stod(qAuxChar);
			qAuxChar = xmlEsfera->FirstChildElement("centro")->FirstChildElement("y")->GetText();
			ycentro = stod(qAuxChar);
			qAuxChar = xmlEsfera->FirstChildElement("centro")->FirstChildElement("z")->GetText();
			zcentro = stod(qAuxChar);
			Punto centro = Punto(xcentro, ycentro, zcentro);

			qAuxChar = xmlEsfera->FirstChildElement("colorDifuso")->FirstChildElement("r")->GetText();
			r = stod(qAuxChar);
			qAuxChar = xmlEsfera->FirstChildElement("colorDifuso")->FirstChildElement("g")->GetText();
			g = stod(qAuxChar);
			qAuxChar = xmlEsfera->FirstChildElement("colorDifuso")->FirstChildElement("b")->GetText();
			b = stod(qAuxChar);
			Color colorDifuso = Color(r/255, g/255, b/255);

			qAuxChar = xmlEsfera->FirstChildElement("colorEspecular")->FirstChildElement("r")->GetText();
			r = stod(qAuxChar);
			qAuxChar = xmlEsfera->FirstChildElement("colorEspecular")->FirstChildElement("g")->GetText();
			g = stod(qAuxChar);
			qAuxChar = xmlEsfera->FirstChildElement("colorEspecular")->FirstChildElement("b")->GetText();
			b = stod(qAuxChar);
			Color colorEspecular = Color(r/255, g/255, b/255);


			qAuxChar = xmlEsfera->FirstChildElement("ka")->GetText();
			ka = stod(qAuxChar);

			qAuxChar = xmlEsfera->FirstChildElement("kd")->GetText();
			kd = stod(qAuxChar);

			qAuxChar = xmlEsfera->FirstChildElement("ks")->GetText();
			ks = stod(qAuxChar);

			qAuxChar = xmlEsfera->FirstChildElement("kt")->GetText();
			kt = stod(qAuxChar);

			qAuxChar = xmlEsfera->FirstChildElement("indRefrac")->GetText();
			double indRefrac = stod(qAuxChar);

			Objeto* esfera = new Esfera(radio, centro, colorDifuso, colorEspecular, ka, kd, ks, kt, indRefrac);
			newobjetos.push_back(esfera);

			xmlEsfera = xmlEsfera->NextSiblingElement("esfera");
		}

		XMLElement* xmlCilindro = xmlObjetos->FirstChildElement("cilindro");
		while (xmlCilindro)
		{
			//cargar cilindro
			double radio, altura, xaux, yaux, zaux, r, g, b, ka, kd, ks, kt, indRefrac;
			const char* qAuxChar; 

			qAuxChar = xmlCilindro->FirstChildElement("radio")->GetText();
			radio = stod(qAuxChar);

			qAuxChar = xmlCilindro->FirstChildElement("altura")->GetText();
			altura = stod(qAuxChar);

			qAuxChar = xmlCilindro->FirstChildElement("centro")->FirstChildElement("x")->GetText();
			xaux = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("centro")->FirstChildElement("y")->GetText();
			yaux = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("centro")->FirstChildElement("z")->GetText();
			zaux = stod(qAuxChar);
			Punto centro = Punto(xaux, yaux, zaux);

			qAuxChar = xmlCilindro->FirstChildElement("direccion_eje")->FirstChildElement("x")->GetText();
			xaux = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("direccion_eje")->FirstChildElement("y")->GetText();
			yaux = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("direccion_eje")->FirstChildElement("z")->GetText();
			zaux = stod(qAuxChar);
			Punto direccion_eje = Punto(xaux, yaux, zaux);

			qAuxChar = xmlCilindro->FirstChildElement("colorDifuso")->FirstChildElement("r")->GetText();
			r = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("colorDifuso")->FirstChildElement("g")->GetText();
			g = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("colorDifuso")->FirstChildElement("b")->GetText();
			b = stod(qAuxChar);
			Color colorDifuso = Color(r/255, g/255, b/255);

			qAuxChar = xmlCilindro->FirstChildElement("colorEspecular")->FirstChildElement("r")->GetText();
			r = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("colorEspecular")->FirstChildElement("g")->GetText();
			g = stod(qAuxChar);
			qAuxChar = xmlCilindro->FirstChildElement("colorEspecular")->FirstChildElement("b")->GetText();
			b = stod(qAuxChar);
			Color colorEspecular = Color(r/255, g/255, b/255);


			qAuxChar = xmlCilindro->FirstChildElement("ka")->GetText();
			ka = stod(qAuxChar);

			qAuxChar = xmlCilindro->FirstChildElement("kd")->GetText();
			kd = stod(qAuxChar);

			qAuxChar = xmlCilindro->FirstChildElement("ks")->GetText();
			ks = stod(qAuxChar);

			qAuxChar = xmlCilindro->FirstChildElement("kt")->GetText();
			kt = stod(qAuxChar);

			qAuxChar = xmlCilindro->FirstChildElement("indRefrac")->GetText();
			indRefrac = stod(qAuxChar);

			Objeto* cilindro = new Cilindro(radio, altura, centro, direccion_eje, colorDifuso, colorEspecular, ka, kd, ks, kt, indRefrac);
			newobjetos.push_back(cilindro);

			xmlCilindro = xmlCilindro->NextSiblingElement("cilindro");
		}

		XMLElement* xmlMalla_Poligonal = xmlObjetos->FirstChildElement("malla_poligonal");
		while (xmlMalla_Poligonal)
		{
			//cargar malla_poligonal
			double r, g, b, ka, kd, ks, kt, indRefrac;
			const char* qAuxChar; 
			std::vector<Triangulo> triangulos;

			XMLElement* xmlTriangulos = xmlMalla_Poligonal->FirstChildElement("triangulos");
			if(!xmlTriangulos){
				throw std::runtime_error("No hay triangulos");
			}
			XMLElement* xmlTriangulo = xmlTriangulos->FirstChildElement("triangulo");
			if(!xmlTriangulo){
				throw std::runtime_error("No hay triangulos");
			}
			while(xmlTriangulo){
				Punto vertices[3];
				XMLElement* xmlVertice = xmlTriangulo->FirstChildElement("vertice");
				for(int i=0; i<3; i++){
					double xaux, yaux, zaux;
					if(!xmlVertice){
						throw std::runtime_error("No hay suficientes vertices");
					}
					qAuxChar = xmlVertice->FirstChildElement("x")->GetText();
					xaux = stod(qAuxChar);
					qAuxChar = xmlVertice->FirstChildElement("y")->GetText();
					yaux = stod(qAuxChar);
					qAuxChar = xmlVertice->FirstChildElement("z")->GetText();
					zaux = stod(qAuxChar);
					vertices[i] = Punto(xaux, yaux, zaux);
					xmlVertice = xmlVertice->NextSiblingElement("vertice");
				}
				triangulos.push_back(Triangulo(vertices[0], vertices[1], vertices[2]));
				xmlTriangulo = xmlTriangulo->NextSiblingElement("triangulo");
			}

			qAuxChar = xmlMalla_Poligonal->FirstChildElement("colorDifuso")->FirstChildElement("r")->GetText();
			r = stod(qAuxChar);
			qAuxChar = xmlMalla_Poligonal->FirstChildElement("colorDifuso")->FirstChildElement("g")->GetText();
			g = stod(qAuxChar);
			qAuxChar = xmlMalla_Poligonal->FirstChildElement("colorDifuso")->FirstChildElement("b")->GetText();
			b = stod(qAuxChar);
			Color colorDifuso = Color(r/255, g/255, b/255);

			qAuxChar = xmlMalla_Poligonal->FirstChildElement("colorEspecular")->FirstChildElement("r")->GetText();
			r = stod(qAuxChar);
			qAuxChar = xmlMalla_Poligonal->FirstChildElement("colorEspecular")->FirstChildElement("g")->GetText();
			g = stod(qAuxChar);
			qAuxChar = xmlMalla_Poligonal->FirstChildElement("colorEspecular")->FirstChildElement("b")->GetText();
			b = stod(qAuxChar);
			Color colorEspecular = Color(r/255, g/255, b/255);


			qAuxChar = xmlMalla_Poligonal->FirstChildElement("ka")->GetText();
			ka = stod(qAuxChar);

			qAuxChar = xmlMalla_Poligonal->FirstChildElement("kd")->GetText();
			kd = stod(qAuxChar);

			qAuxChar = xmlMalla_Poligonal->FirstChildElement("ks")->GetText();
			ks = stod(qAuxChar);

			qAuxChar = xmlMalla_Poligonal->FirstChildElement("kt")->GetText();
			kt = stod(qAuxChar);

			qAuxChar = xmlMalla_Poligonal->FirstChildElement("indRefrac")->GetText();
			indRefrac = stod(qAuxChar);

			Objeto* malla_poligonal = new Malla_Poligonal(triangulos, colorDifuso, colorEspecular, ka, kd, ks, kt, indRefrac);
			newobjetos.push_back(malla_poligonal);

			xmlMalla_Poligonal = xmlMalla_Poligonal->NextSiblingElement("malla_poligonal");
		}
		
	}
	this->objetos = newobjetos;
	for(Objeto* obj : objetos){
		 obj->Print();
	}
	this->luces = newluces;

	std::cout << "Escena cargada" << std::endl;
}

void Escena::debug(){
	 std::cout << "ancho " << ancho << std::endl;
	 std::cout << "altura " << altura << std::endl;
	 std::cout << "Camara posicion: " << camara.getPosicion() << std::endl;
	 std::cout << "Camara mirando a: " << camara.getLookatVector() << std::endl;
	 std::cout << "Camara arriba: " << camara.getUpVector() << std::endl;
	 std::cout << "Camara horizontal: " << camara.getHorizontalSize() << std::endl;
	 std::cout << "Camara vertical: " << camara.getVerticalSize() << std::endl;
	 std::cout << "Luces size: " << luces.size() << std::endl;
	 std::cout << "Objetos size: " << objetos.size() << std::endl;
	std::cout<< "=========================================" << std::endl;
	std::cout<< "=========================================" << std::endl;
	std::cout<< "=========================================" << std::endl;
	for(Objeto* obj : objetos){
		 obj->Print();
	}

	/*for(Luz luz : luces){
		std::cout << "Luz posicion: " << luz.posicion << std::endl;
		std::cout << "Luz color: " << luz.colour << std::endl;
	}*/
}