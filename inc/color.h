#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <tuple>
#include <iostream>
class Color {
    public:
        double r;
        double g;
        double b;
    Color() {
        r = 0;
        g = 0;
        b = 0;
    }
    Color(double r, double g, double b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    double get_r() {
        return r;
    }

    double get_g() {
        return g;
    }

    double get_b() {
        return b;
    }
    Color operator*(double x) {
        return Color(r*x, g*x, b*x);
    }

    Color operator*(Color c) {
        return Color(r*c.get_r(), g*c.get_g(), b*c.get_b());
    }

    Color operator+(Color c) {
        return Color(r+c.get_r(), g+c.get_g(), b+c.get_b());
    }

    Color normalizar_color() {
        return Color(std::min(r,1.0), std::min(g,1.0), std::min(b,1.0));
    }

    friend std::ostream& operator<<(std::ostream& os, Color c);
};

using w_color = std::vector<Color>;
using h_w_color = std::vector<w_color>;

#endif