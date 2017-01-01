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
/*
    int hpMax = 6;
    for (int i=0 ; i<hpMax ; i++) {
        Mesh3D * heart = new Mesh3D( "circle.obj", "circle.mtl", "gui_heart.png" );
        heart->isGUI = true;
        heart->setScale( 0.05f );
        heart->setTranslation( Interface::gameWidth, 0, -0.2f );
    }
    */
}
