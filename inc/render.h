#ifndef RENDER_H
#define RENDER_H

#include <vector>
#include <tuple>
#include <iostream>
#include <string>

//pre condicion los double dentro del tuple tienen que valer entre 0.0 y 255.0
int renderizar(int h, int v, std::vector<std::vector<std::tuple<double, double, double, double>>> c, std::string nombreAGuardar = "whittedRayTracing");

#endif

