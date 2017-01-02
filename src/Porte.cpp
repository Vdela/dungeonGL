//
// Created by valentin on 27/12/2016.
//

#include "../include/Porte.h"
#include "../include/Player.h"
#define GLEW_STATIC

Porte::Porte() {
    battant_porte = new Mesh3D( "porte.obj", "porte.mtl", "bone02.png" );

    battant_porte->setParentMatrix( &modelMatrix );
}
void Porte::draw() {

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    if(ouverture){
        battant_porte->setTranslation(0.0f,-1.0f,0.0f);
    }

}

float Porte::get_posX_porte() {
    return posX_porte;
}

float Porte::get_posY_porte() {
    return posY_porte;
}

void Porte::set_posX_porte(float _X) {
    posX_porte = _X;
}

void Porte::set_posY_porte(float _Y) {
    posY_porte = _Y;
}