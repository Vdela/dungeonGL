//
// Created by Vincent on 26/12/2016.
//

#include "../include/Mesh3D.h"
#include "../include/Demon3D.h"


Demon3D::Demon3D() : bodyOscillation( -0.05f, 0.8f, 2.25f ), bodyOscillation2( -0.25f, 0.25f, 1.5f ) {

    skull = new Mesh3D( "demonSkull.obj", "", "bone01.png" );
    shoulders = new Mesh3D( "demonShoulders.obj", "", "bone02.png" );
    chest = new Mesh3D( "demonChest.obj", "", "bone01.png" );
    leftHand = new Mesh3D( "demonHand.obj", "", "bone01.png" );
    rightHand = new Mesh3D( "demonHand.obj", "", "bone01.png" );

    skull->setParentMatrix( &modelMatrix );
    shoulders->setParentMatrix( &modelMatrix );
    chest->setParentMatrix( &modelMatrix );
    leftHand->setParentMatrix( &modelMatrix );
    rightHand->setParentMatrix( &modelMatrix );

    leftHand->addRotation( glm::vec3(0,1,0), 55 );
    rightHand->addRotation( glm::vec3(0,1,0), 135 );

}

void Demon3D::draw() {
    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    bodyOscillation.nextValueSmooth();
    bodyOscillation2.nextValueSmooth();

    skull->setTranslation( -bodyOscillation2.getValue() * 0.4f, 0.25f + bodyOscillation.getValue() * 1.25f ,  -bodyOscillation2.getValue() * 0.4f );

    shoulders->setTranslation( bodyOscillation2.getValue(), bodyOscillation.getValue() * 1.0f ,  bodyOscillation2.getValue() );
    chest->setTranslation( bodyOscillation2.getValue() * 0.8f, bodyOscillation.getValue() * 0.65f , bodyOscillation2.getValue() * 0.8f );

    leftHand->setTranslation( bodyOscillation2.getValue(), bodyOscillation.getValue() * -1.0f , bodyOscillation2.getValue() );
    rightHand->setTranslation( bodyOscillation2.getValue(), bodyOscillation.getValue() * -1.0f , bodyOscillation2.getValue() );



}
