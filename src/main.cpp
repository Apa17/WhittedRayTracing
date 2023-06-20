
#include "../inc/escena.h"
#include <iostream>
#include <tuple>
#include <string>

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
#define BPP 24
#include "../inc/FreeImage.h"

int main() {
	//objetos[0] = &cilindro;
	/*cout << "Ingresar nombre del archivo" << endl;
	cin >> s;
	if (s == "0") {
		s = "default";
	}
	*/
	FIBITMAP* bitmap = FreeImage_Allocate(3840, 2160, BPP);
		RGBQUAD color;
		if (!bitmap)
			return -2;

	//leer nombre del archivo xml
	std::string s = "default";
	s = "../xml/" + s + ".xml";
	////crear la escena
	try
	{
		std::cout << s << '\n';
		Escena e = Escena(s);
		//renderizar y guardar en png
		// e.debug();

		return e.render();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return -1;
	}
	return 0;
}