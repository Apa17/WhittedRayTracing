#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include "color.h"

//pre condicion los double dentro del tuple tienen que valer entre 0.0 y 255.0
int renderizar(int h, int v, h_w_color * c, std::string nombreAGuardar = "whittedRayTracing");

#endif

