//
// Created by Vincent on 26/12/2016.
//

#include "../include/Mesh3D.h"
#include "../include/Demon3D.h"


Demon3D::Demon3D() : oscillation(-0.5f, 0.5f, 1.0f) {

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

    leftHand->addRotation( glm::vec3(0,1,0), 90 );
    rightHand->addRotation( glm::vec3(0,1,0), 20 );

}

void Demon3D::draw() {
    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

    oscillation.nextValueSmooth();
    skull->setTranslation( 0, oscillation.getValue() , 0 );

}
