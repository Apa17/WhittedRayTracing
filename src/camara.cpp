#include "../inc/camara.h"

Camara::Camara(Punto posicion, Punto upVector, Punto lookatVector, double verticalSize, double horizontalSize) {
    this->posicion = Punto(0,0,0);
    this->upVector = upVector;
    this->lookatVector = lookatVector - posicion;
    this->verticalSize = verticalSize;
    this->horizontalSize = horizontalSize;
}

Punto Camara::getPosicion() {
    return this->posicion;
}

Punto Camara::getUpVector() {
    return this->upVector;
}

Punto Camara::getLookatVector() {
    return this->lookatVector;
}

Punto** Camara::getRays(int width, int height) {
    // calculamos el plano
    double xp = this->lookatVector.getX();
    double yp = this->lookatVector.getY();
    double zp = this->lookatVector.getZ();
    double coef = -xp*xp - yp*yp - zp*zp;
    // origen = lookat
    Punto direccion = Punto(this->upVector.getX(), this->upVector.getY(), (-xp*this->upVector.getX() - yp*this->upVector.getY() - coef)/zp);
    //normalizo direccion
    // plano = xpX + ypY + zpZ + coef = 0
    Punto** rayos = new Punto*[width];
    for (int i = 0; i < width; i++) {
        rayos[i] = new Punto[height];
        for (int j = 0; j < height ; j++) { // 0, 1, 0
            //estoy en lookat me muevo hacia arriba por el up vector verticalSize/2
        }
    }
    return rayos;
}