#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <tuple>

using h_w_color = std::vector<std::vector<std::tuple<double, double, double, double>>>;
using w_color = std::vector<std::tuple<double, double, double, double>>;
using color = std::tuple<double, double, double, double>;
color multiplicar_color(color c1, double x){
	return color(std::get<0>(c1)*x, std::get<1>(c1)*x, std::get<2>(c1)*x, std::get<3>(c1)*x);
}

color multiplicar_color(color c1, color c2){
	return color(std::get<0>(c1)*std::get<0>(c2), std::get<1>(c1)*std::get<1>(c2), std::get<2>(c1)*std::get<2>(c2), std::get<3>(c1)*std::get<3>(c2));
}

color sumar_color(color c1, color c2){
    return color(std::get<0>(c1)+std::get<0>(c2), std::get<1>(c1)+std::get<1>(c2), std::get<2>(c1)+std::get<2>(c2), std::get<3>(c1)+std::get<3>(c2));
}

color normalizar_color(color c1){
    return color(std::min(std::get<0>(c1),1.0), std::min(std::get<1>(c1),1.0), std::min(std::get<2>(c1),1.0), std::min(std::get<3>(c1),1.0));
}

#endif