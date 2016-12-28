//
// Created by valentin on 27/12/2016.
//

#include "../include/Porte.h"

#define GLEW_STATIC

Porte::Porte() {
    battant_porte= new Mesh3D( "porte.obj", "", "texture_porte.jpg" );

    battant_porte->setParentMatrix( &modelMatrix );
}
void Porte::draw() {

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    if(ouverture==true){
        battant_porte->setTranslation(0.0f,-1.0f,0.0f);
    }



}