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

Ray** Camara::getRays(int width, int height) {
    Ray** rayos = new Ray*[height];
    
    // Calcular la dirección del vector "forward"
    Punto forward = lookatVector.normalized(); // Normalizar el vector
    
    // Calcular el vector "right" perpendicular a la dirección forward y el vector upVector
    Punto right = forward.cross(upVector).normalized(); // Producto cruz y normalización
    
    // Calcular el vector "up" perpendicular a la dirección forward y right
    Punto up = right.cross(forward).normalized(); // Producto cruz y normalización
    
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
            Punto rayDirection = forward + right * x + up * y;
            
            // Crear el punto de origen del rayo (0,0,0)
            Punto rayOrigin(0, 0, 0);

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