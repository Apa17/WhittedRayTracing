#include "Render.h"
#include "FreeImage.h"
#include <string>
#include <direct.h>
#include <iomanip>
#include <chrono>
#include <sstream>
#include "../inc/color.h"

#pragma warning(disable : 4996)


#define BPP 24

int renderizar(int h, int w, h_w_color colors, int i, std::string nombreAGuardar) {
		h_w_color c = colors;	
		FreeImage_Initialise();
		FIBITMAP* bitmap = FreeImage_Allocate(3840, 2160, BPP);
		RGBQUAD color;
		if (!bitmap)
			return -2;
		//set pixels
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				color.rgbRed = (BYTE)(c[i][j].get_r() * 255);
				color.rgbGreen = (BYTE)(c[i][j].get_g() * 255);
				color.rgbBlue = (BYTE)(c[i][j].get_b() * 255);
				//falta calcular como afecta el a de RGBA a RGB porque RGB
				FreeImage_SetPixelColor(bitmap, j, i, &color);
			}
		}
		//create directory
		std::time_t const now_c = std::time(nullptr);
		std::stringstream auxiliar;
		auxiliar << std::put_time(std::localtime(&now_c), "%F %H-%M-%S");
		std::string timeanddate = auxiliar.str();

		//cout << _mkdir(directorio.c_str()) << endl; //imprime 0 si crea el directorio
		std::string directorio;
		if (i == 0)
			directorio = "../output/color";
		else if (i<2)
			directorio = "../output/refraccion";
		else
			directorio = "../output/reflexion";
		/*if (_mkdir(directorio.c_str()) != 0) {
			return -3;
		}*/
		//save img
		std::string fileSaveLocation = directorio + "/" + timeanddate + ".png";
		std::cout << fileSaveLocation;
		if (FreeImage_Save(FIF_PNG, bitmap, fileSaveLocation.c_str(), 0)){
			std::cout << "Imagesuccessfully saved !" << std::endl;
		}else{
			return -4;
		}
		FreeImage_DeInitialise();
	 // Cleanup !
	return 0;
}