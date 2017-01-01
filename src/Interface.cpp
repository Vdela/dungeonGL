//
// Created by Vincent on 01/01/2017.
//

#include <cstdio>
#include "../include/Interface.h"
#include "../include/Mesh3D.h"

Interface * Interface::instance = NULL;

Interface &Interface::getInstance() {
    if ( instance == NULL ) {
        instance = new Interface();
    }
    return *Interface::instance;
}

Interface::Interface() {
    /*Mesh3D * heart = new Mesh3D( "circle.obj", "circle.mtl", "gui_heart.png" );
    heart->isGUI = true;
    heart->setRotation( glm::vec3(0,1,0), 180 );
    heart->setScale( 0.25f );
    //heart->setRotation( glm::vec3(1,0,0), 90 );
    //heart->setRotation( glm::vec3(0,0,1), 180 );
    heart->setTranslation( 0.3f, 0, 0.3f );*/
}
