#include "../inc/color.h"

std::ostream& operator<<(std::ostream& os, Color c) {
    os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;
}