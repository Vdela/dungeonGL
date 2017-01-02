//
// Created by valentin on 27/12/2016.
//

#include "../include/Porte.h"
#include "../include/Player.h"
#define GLEW_STATIC

Porte::Porte() {
    battant_porte = new Mesh3D( "porte.obj", "porte.mtl", "bone02.png" );
    battant_porte->setParentMatrix( &modelMatrix );
    isOpen = false;
}
void Porte::draw() {

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;


}

glm::vec2 Porte::getPos() {
    return pos;
}

