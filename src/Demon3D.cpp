//
// Created by Vincent on 26/12/2016.
//

#include "../include/Mesh3D.h"
#include "../include/Demon3D.h"

Demon3D::Demon3D() {

    skull = new Mesh3D( "demonSkull.obj", "", "bone01.png" );
    chest = new Mesh3D( "demonChest.obj", "", "bone01.png" );
    skull->setParentMatrix( &modelMatrix );
    chest->setParentMatrix( &modelMatrix );

}

void Demon3D::draw() {
    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

}
