#include "Render.h"
#include "FreeImage.h"
#include <string>
#include <direct.h>
#include <iomanip>
#include <chrono>
#include <sstream>

using namespace std;
#pragma warning(disable : 4996)


#define BPP 24

int renderizar(int h, int w, std::vector<std::vector<std::tuple<double, double, double, double>>> c, string nombreAGuardar) {
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(w, h, BPP);
	RGBQUAD color;
	if (!bitmap)
		return -2;
	//set pixels
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			color.rgbRed = (BYTE)std::get<0>(c[i][j]);
			color.rgbGreen = (BYTE)std::get<1>(c[i][j]);
			color.rgbBlue = (BYTE)std::get<2>(c[i][j]);
			//falta calcular como afecta el a de RGBA a RGB porque RGB
			FreeImage_SetPixelColor(bitmap, j, i, &color);
		}
	}
	//create directory
	std::time_t const now_c = std::time(nullptr);
	stringstream auxiliar;
	auxiliar << std::put_time(std::localtime(&now_c), "%F %H-%M-%S");
	string timeanddate = auxiliar.str();

	//cout << _mkdir(directorio.c_str()) << endl; //imprime 0 si crea el directorio
	string directorio = "../output/";
	/*if (_mkdir(directorio.c_str()) != 0) {
		return -3;
	}*/
	//save img
	string fileSaveLocation = directorio + "/" + timeanddate + ".png";
	cout << fileSaveLocation;
	if (FreeImage_Save(FIF_PNG, bitmap, fileSaveLocation.c_str(), 0)){
		std::cout << "Imagesuccessfully saved !" << std::endl;
	}else{
		return -4;
	}
	FreeImage_DeInitialise(); // Cleanup !
	return 0;
}