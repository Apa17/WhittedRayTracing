#include "Escena.h"
#include "tinyxml2.h"
#include <string>
#include <tuple>
//#include "Poligono.h"
//#include "Arista.h"
//#include "Malla_poligonal.h"
//#include "Cilindro.h"

using namespace std;
using namespace tinyxml2;

Escena::Escena(string s) {}
//	//some code
//	/*vector<Objeto3d*> newobjetos;
//	vector<Light*> newoluces;
//	Camara* cam = nullptr;*/
//
//	XMLDocument doc;
//	doc.LoadFile(s.c_str());
//	
//	XMLElement * xmlEscena = doc.RootElement();
//	if (xmlEscena != NULL) {
//		XMLElement* xmlCamara = xmlEscena->FirstChildElement("camara");
//		if(xmlCamara != NULL){
//			//cargar camara
//			double xAux, yAux, zAux;
//			const char* xAuxchar; 
//			const char* yAuxchar;
//			const char* zAuxchar;
//			XMLElement* aux;
//
//			aux = xmlCamara->FirstChildElement("posCamara");
//			xAuxchar = aux->FirstChildElement("x")->GetText();
//			xAux = stod(xAuxchar);
//			yAuxchar = aux->FirstChildElement("y")->GetText();
//			yAux = stod(yAuxchar);
//			zAuxchar = aux->FirstChildElement("z")->GetText();
//			zAux = stod(zAuxchar);
//			Punto* posCamara = new Punto(xAux, yAux, zAux);
//
//
//			aux = xmlCamara->FirstChildElement("lookAtCamara");
//			xAuxchar = aux->FirstChildElement("x")->GetText();
//			xAux = stod(xAuxchar);
//			yAuxchar = aux->FirstChildElement("y")->GetText();
//			yAux = stod(yAuxchar);
//			zAuxchar = aux->FirstChildElement("z")->GetText();
//			zAux = stod(zAuxchar);
//			Punto* lookAtCamara = new Punto(xAux, yAux, zAux);
//
//			aux = xmlCamara->FirstChildElement("upVector");
//			xAuxchar = aux->FirstChildElement("x")->GetText();
//			xAux = stod(xAuxchar);
//			yAuxchar = aux->FirstChildElement("y")->GetText();
//			yAux = stod(yAuxchar);
//			zAuxchar = aux->FirstChildElement("z")->GetText();
//			zAux = stod(zAuxchar);
//			Punto* upVector = new Punto(xAux, yAux, zAux);
//
//			const char* auxChar;
//
//			auxChar = xmlCamara->FirstChildElement("distancia")->GetText();
//			double distancia = stod(auxChar);
//			auxChar = xmlCamara->FirstChildElement("horizontalSize")->GetText();
//			double horizontalSize = stod(auxChar);
//			auxChar = xmlCamara->FirstChildElement("verticalSize")->GetText();
//			double verticalSize = stod(auxChar);
//			/*cam = new Camara(posCamara,
//				lookAtCamara,
//				upVector,
//				distancia,
//				horizontalSize,
//				verticalSize);*/
//		}
//
//		XMLElement* xmlLuces= xmlEscena->FirstChildElement("luces");
//		if (xmlLuces != NULL) {
//			//cargar luces
//			XMLElement* xmlLuz = xmlLuces->FirstChildElement("luz");
//			while (xmlLuz) {
//				//cargar luz
//				double x, y, z, r, g, b, a;
//				const char* xChar;
//				const char* yChar;
//				const char* zChar;
//				const char* rChar;
//				const char* gChar;
//				const char* bChar;
//				const char* aChar;
//
//				XMLElement* xmlPosicion = xmlLuz->FirstChildElement("posicion");
//				xChar = xmlPosicion->FirstChildElement("x")->GetText();
//				yChar = xmlPosicion->FirstChildElement("y")->GetText();
//				zChar = xmlPosicion->FirstChildElement("z")->GetText();
//				x = stod(xChar);
//				y = stod(yChar);
//				z = stod(zChar);
//				Punto* p = new Punto(x, y, z);
//
//				XMLElement* xmlColor = xmlLuz->FirstChildElement("color");
//				rChar = xmlColor->FirstChildElement("r")->GetText();
//				gChar = xmlColor->FirstChildElement("g")->GetText();
//				bChar = xmlColor->FirstChildElement("b")->GetText();
//				aChar = xmlColor->FirstChildElement("a")->GetText();
//				r = stod(rChar);
//				g = stod(gChar);
//				b = stod(bChar);
//				a = stod(aChar);
//
//				tuple<double, double, double, double> rgba = tuple<double, double, double, double>(r,g,b,a);
//
//				Light* luz = new Light(p, rgba);
//				newoluces.push_back(luz);
//
//				//siguiente
//				xmlLuz = xmlLuz->NextSiblingElement("luz");
//			}
//		}
//
//		XMLElement* xmlObjects = xmlEscena->FirstChildElement("objetos");
//		if (xmlObjects != NULL) {
//			XMLElement* aux;
//			//esferas
//			aux = xmlObjects->FirstChildElement("esfera");
//			while (aux) {
//				//cargar esfera
//				double radio, xcentro, ycentro, zcentro, r, g, b, a, coefReflex, CoefRefrac;
//				const char* qAuxChar; 
//
//				qAuxChar = aux->FirstChildElement("radio")->GetText();
//				radio = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("centro")->FirstChildElement("x")->GetText();
//				xcentro = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("centro")->FirstChildElement("y")->GetText();
//				ycentro = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("centro")->FirstChildElement("z")->GetText();
//				zcentro = stod(qAuxChar);
//				Punto* centro = new Punto(xcentro, ycentro, zcentro);
//
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("r")->GetText();
//				r = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("g")->GetText();
//				g = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("b")->GetText();
//				b = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("a")->GetText();
//				a = stod(qAuxChar);
//				tuple<double, double, double, double> rgba = tuple<double, double, double, double>(r, g, b, a);
//
//
//				qAuxChar = aux->FirstChildElement("coefReflex")->GetText();
//				coefReflex = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("coefRefrac")->GetText();
//				CoefRefrac = stod(qAuxChar);
//
//				Objeto3d* esfera = new Esfera(radio, centro, rgba, coefReflex, CoefRefrac);
//				newobjetos.push_back(esfera);
//
//				aux = aux->NextSiblingElement("esfera");
//			}
//
//			//cilindros
//			aux = xmlObjects->FirstChildElement("cilindro");
//			while (aux) {
//				//cargar cilindro
//				double x,y,z, altura, radio, r, g, b, a, coefReflex, coefRefrac;
//				const char* qAuxChar;
//
//				//rgba
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("r")->GetText();
//				r = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("g")->GetText();
//				g = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("b")->GetText();
//				b = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("a")->GetText();
//				a = stod(qAuxChar);
//				tuple<double, double, double, double> rgba = tuple<double, double, double, double>(r, g, b, a);
//
//				qAuxChar = aux->FirstChildElement("coefReflex")->GetText();
//				coefReflex = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("coefRefrac")->GetText();
//				coefRefrac = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("radio")->GetText();
//				radio = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("radio")->GetText();
//				altura = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("centro")->FirstChildElement("x")->GetText();
//				x = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("centro")->FirstChildElement("y")->GetText();
//				y = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("centro")->FirstChildElement("z")->GetText();
//				z = stod(qAuxChar);
//				Punto* p = new Punto(x, y, z);
//
//				Objeto3d* cilindro = new Cilindro(altura, radio, p, rgba, coefReflex, coefRefrac);;
//				newobjetos.push_back(cilindro);
//				aux = aux->NextSiblingElement("cilindro");
//			}
//
//			//mallapoligonal
//			aux = xmlObjects->FirstChildElement("mallapoligonal");
//			while (aux) {
//				vector<Poligono*> vp;
//				double r, g, b, a, coefReflex, coefRefrac;
//				const char* qAuxChar;
//
//				//rgba
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("r")->GetText();
//				r = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("g")->GetText();
//				g = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("b")->GetText();
//				b = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("a")->GetText();
//				a = stod(qAuxChar);
//				tuple<double, double, double, double> rgba = tuple<double, double, double, double>(r, g, b, a);
//
//
//				//coeficientes
//				qAuxChar = aux->FirstChildElement("coefReflex")->GetText();
//				coefReflex = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("coefRefrac")->GetText();
//				coefRefrac = stod(qAuxChar);
//
//
//				//cargar poligono
//				XMLElement* xmlpoligono = aux->FirstChildElement("poligono");
//				while (xmlpoligono) {
//					double x, y, z;
//					
//
//					XMLElement* aux2 = xmlpoligono->FirstChildElement("punto");
//
//					qAuxChar = aux2->FirstChildElement("x")->GetText();
//					x = stod(qAuxChar);
//					qAuxChar = aux2->FirstChildElement("y")->GetText();
//					y = stod(qAuxChar);
//					qAuxChar = aux2->FirstChildElement("z")->GetText();
//					z = stod(qAuxChar);
//					Punto* vertice1 = new Punto(x, y, z);
//
//					aux2 = aux2->NextSiblingElement("punto");
//					qAuxChar = aux2->FirstChildElement("x")->GetText();
//					x = stod(qAuxChar);
//					qAuxChar = aux2->FirstChildElement("y")->GetText();
//					y = stod(qAuxChar);
//					qAuxChar = aux2->FirstChildElement("z")->GetText();
//					z = stod(qAuxChar);
//					Punto* vertice2 = new Punto(x, y, z);
//
//					aux2 = aux2->NextSiblingElement("punto");
//					qAuxChar = aux2->FirstChildElement("x")->GetText();
//					x = stod(qAuxChar);
//					qAuxChar = aux2->FirstChildElement("y")->GetText();
//					y = stod(qAuxChar);
//					qAuxChar = aux2->FirstChildElement("z")->GetText();
//					z = stod(qAuxChar);
//					Punto* vertice3 = new Punto(x, y, z);
//
//
//					vector<Punto*> vertices;
//					vertices.push_back(vertice1);
//					vertices.push_back(vertice2);
//					vertices.push_back(vertice3);
//
//					vector<Arista*> aristas;
//					aristas.push_back(new Arista(vertice1, vertice2));
//					aristas.push_back(new Arista(vertice2, vertice3));
//					aristas.push_back(new Arista(vertice3, vertice1));
//
//					Poligono* poligono = new Poligono(vertice1, vertice2, vertice3, aristas, rgba, coefReflex, coefRefrac);
//					vp.push_back(poligono);
//
//					xmlpoligono = xmlpoligono->NextSiblingElement("poligono");
//				}
//				Objeto3d* malla_poligonal = new Malla_Poligonal(vp, rgba, coefReflex, coefRefrac);
//				newobjetos.push_back(malla_poligonal);
//				aux = aux->NextSiblingElement("malla_poligonal");
//			}
//
//			//paredes
//			aux = xmlObjects->FirstChildElement("pared");
//			while (aux) {
//				//cargar pared
//				double x, y, z, r, g, b, a, coefReflex, coefRefrac;
//				const char* qAuxChar;
//
//				XMLElement* aux2 = aux->FirstChildElement("punto");
//
//				qAuxChar = aux2->FirstChildElement("x")->GetText();
//				x = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("y")->GetText();
//				y = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("z")->GetText();
//				z = stod(qAuxChar);
//				Punto* vertice1 = new Punto(x, y, z);
//
//				aux2 = aux2->NextSiblingElement("punto");
//				qAuxChar = aux2->FirstChildElement("x")->GetText();
//				x = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("y")->GetText();
//				y = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("z")->GetText();
//				z = stod(qAuxChar);
//				Punto* vertice2 = new Punto(x, y, z);
//
//				aux2 = aux2->NextSiblingElement("punto");
//				qAuxChar = aux2->FirstChildElement("x")->GetText();
//				x = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("y")->GetText();
//				y = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("z")->GetText();
//				z = stod(qAuxChar);
//				Punto* vertice3 = new Punto(x, y, z);
//
//				aux2 = aux2->NextSiblingElement("punto");
//				qAuxChar = aux2->FirstChildElement("x")->GetText();
//				x = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("y")->GetText();
//				y = stod(qAuxChar);
//				qAuxChar = aux2->FirstChildElement("z")->GetText();
//				z = stod(qAuxChar);
//				Punto* vertice4 = new Punto(x, y, z);
//
//
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("r")->GetText();
//				r = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("g")->GetText();
//				g = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("b")->GetText();
//				b = stod(qAuxChar);
//				qAuxChar = aux->FirstChildElement("color")->FirstChildElement("a")->GetText();
//				a = stod(qAuxChar);
//				tuple<double, double, double, double> rgba = tuple<double, double, double, double>(r, g, b, a);
//				
//				qAuxChar = aux->FirstChildElement("coefReflex")->GetText();
//				coefReflex = stod(qAuxChar);
//
//				qAuxChar = aux->FirstChildElement("coefRefrac")->GetText();
//				coefRefrac = stod(qAuxChar);
//
//				vector<Punto*> vertices;
//				vertices.push_back(vertice1);
//				vertices.push_back(vertice2);
//				vertices.push_back(vertice3);
//				vertices.push_back(vertice4);
//
//				vector<Arista*> aristas;
//				aristas.push_back(new Arista(vertice1,vertice2));
//				aristas.push_back(new Arista(vertice2, vertice3));
//				aristas.push_back(new Arista(vertice3, vertice4));
//				aristas.push_back(new Arista(vertice4, vertice1));
//
//				Objeto3d* poligono = new Poligono(vertice1, vertice2, vertice3, aristas, rgba, coefReflex, coefRefrac);
//				newobjetos.push_back(poligono);
//
//				aux = aux->NextSiblingElement("prisma");
//			}
//		}
//
//	}
//	
//	this->camara = cam;
//	this->objetos = newobjetos;
//	this->luces = newoluces;
//	cout << "finished loading scene" << endl;
//}
//
//Punto* Escena::getCentroDeProyeccion() {
//	return nullptr;
//}
//Punto* Escena::getcentroVentanaPV() {
//	return nullptr;
//}
//Ray* Escena::getrayo(double, double) {
//	return nullptr;
//}
//
//Escena::~Escena() {
//	delete this->camara;
//}