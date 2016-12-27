//
// Created by Vincent on 26/12/2016.
//

#include "../include/Mesh3D.h"
#include "../include/Demon3D.h"


Demon3D::Demon3D() : bodyOscillation( -0.05f, 0.8f, 2.25f ) {

    skull = new Mesh3D( "demonSkull.obj", "", "bone02.png" );
    chest = new Mesh3D( "demonChest.obj", "", "bone02.png" );
    shoulders = new Mesh3D( "demonShoulders.obj", "", "bone01.png" );
    leftHand = new Mesh3D( "demonHand.obj", "", "bone02.png" );
    rightHand = new Mesh3D( "demonHand.obj", "", "bone02.png" );

    skull->setParentMatrix( &modelMatrix );
    chest->setParentMatrix( &modelMatrix );
    shoulders->setParentMatrix( &modelMatrix );
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

    skull->setTranslation( 0, bodyOscillation.getValue() * 1.25f , 0 );

    bodyOscillation.nextValueSmooth();
    shoulders->setTranslation( 0, bodyOscillation.getValue() * 1.0f , 0 );
    chest->setTranslation( 0, bodyOscillation.getValue() * 0.65f , 0 );

    leftHand->setTranslation( 0, bodyOscillation.getValue() * -1.0f , 0 );
    rightHand->setTranslation( 0, bodyOscillation.getValue() * -1.0f , 0 );

    //leftHand->addRotation( glm::vec3(0,1,0), 90 );

}
