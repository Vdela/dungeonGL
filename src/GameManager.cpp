//
// Created by Vincent on 15/12/2016.
//

#include "../include/GameManager.h"


GameManager GameManager::instance = GameManager();

GameManager::GameManager() {

}

GameManager& GameManager::getInstance() {
    return GameManager::instance;
}

void GameManager::initGame(uint32_t width, uint32_t height, char* gameName) {

    //=================================//
    //===== Init de l'application =====//
    //=================================//
    SDLWindowManager windowManager(width, height, gameName);
    initGlew();
    glEnable(GL_DEPTH_TEST);


    //=================================//
    //===== Construction du monde =====//
    //=================================//
    Cube3D c1( "wood.jpg" );
    //Sphere3D sphere(windowManager);
    c1.setTranslation( 0, 0, -5 );

    Cube3D c2("cubeDebugUV.png" );
    c2.setTranslation( 0, -2, -5 );

    Cube3D cTop("cubeDebugUV.png" );
    cTop.setTranslation( -1, 2, -5 );

    Triangle3D t("EarthMap.jpg");
    t.setTranslation( 1,1.35,-3 );


    //=================================//
    //========== Loop du jeu ==========//
    //=================================//

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        // Jeu
        c1.addRotation( glm::vec3(0, 1, 0), 0.015f );
        c2.addRotation( glm::vec3(1, 0, 0), 0.015f );
        cTop.addRotation( glm::vec3(1, 1, 1), 0.015f );
        t.addRotation( glm::vec3(0, 1, 0), 0.005f );

        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendu des objets de la scene
        for ( std::vector<Object3D*>::const_iterator it = Object3D::getSceneObjects().begin() ;  it != Object3D::getSceneObjects().end() ; it++ ) {
            (*it)->draw();
        }

        // Update the display
        windowManager.swapBuffers();
    }

    //=================================//
    //=== Liberation des ressources ===//
    //=================================//
    // TODO
    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);
}


void GameManager::initGlew() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(1);
    }
}
