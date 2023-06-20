#include "../inc/camara.h"


Camara::Camara(Vector posicion, Vector upVector, Vector lookatVector, double verticalSize, double horizontalSize) {
    this->posicion = Vector(0,0,0);
    this->upVector = upVector.normalized();
    this->lookatVector = (lookatVector).normalized();
    this->verticalSize = verticalSize;
    this->horizontalSize = horizontalSize;
}

Camara::Camara() {
    this->posicion = Vector(0,0,0);
    this->upVector = Vector(0,1,0);
    this->lookatVector = Vector(0,0,1);
    this->verticalSize = 1;
    this->horizontalSize = 1;
}

Vector Camara::getPosicion() {
    return this->posicion;
}

Vector Camara::getUpVector() {
    return this->upVector;
}

Vector Camara::getLookatVector() {
    return this->lookatVector;
}

Ray** Camara::getRays(int width, int height) {
    Ray** rayos = new Ray*[height];
    
    // Calcular la dirección del vector "forward"
    Vector forward = lookatVector.normalized(); // Normalizar el vector
    
    // Calcular el vector "right" perpendicular a la dirección forward y el vector upVector
    Vector right = upVector.cross(forward).normalized(); // Producto cruz y normalización


    Vector up = upVector.normalized();
    
    // Calcular el vector "up" perpendicular a la dirección forward y right
    
    // Calcular el tamaño de los píxeles en el plano del viewport
    double pixelWidth = horizontalSize / width;
    double pixelHeight = verticalSize / height;
    
    // Calcular los rayos para cada píxel del viewport
    for (int i = 0; i < height; i++) {
        rayos[i] = new Ray[width];
        for (int j = 0; j < width; j++) {
            // Calcular la posición del píxel en el plano del viewport
            double x = (j - width / 2) * pixelWidth;
            double y = (i - height / 2) * pixelHeight;
            
            // Calcular la dirección del rayo que pasa por el píxel
            Vector rayDirection = forward + right * x + up * y;
            
            // Crear el vector de origen del rayo (0,0,0)
            Vector rayOrigin(0, 0, 0);

            Ray r;
            r.origen = rayOrigin;
            r.direccion = rayDirection.normalized();
            r.indRefrac = 1.0;
            
            // Asignar el rayo al arreglo de rayos
            rayos[i][j] = r; // Normalizar el vector
        }
    }
    
   return rayos;
}

double Camara::getVerticalSize() {
    return this->verticalSize;
}

double Camara::getHorizontalSize() {
    return this->horizontalSize;
}