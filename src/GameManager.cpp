//
// Created by Vincent on 15/12/2016.
//

#include "../include/GameManager.h"
#include "../lib/glimac/include/glimac/FreeflyCamera.hpp"
#include "../include/Triangle3D.h"
#include "../include/Cube3D.h"
#include "../include/Mesh3D.h"
#include "../include/Demon3D.h"

GameManager GameManager::instance = GameManager();

GameManager::GameManager() {
    applicationPath = FilePath(".\\opengl.exe");
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



    Niveau niveau1;
    niveau1.lectureMap((char*)"map3.ppm");


    Demon3D demon;
    float scale = 0.25;
    demon.setScale( scale, scale, scale );
    demon.setTranslation( 0, -2, -5 );


    //=================================//
    //========== Loop du jeu ==========//
    //=================================//
    // Application loop:
    bool done = false;

    while(!done) {
        Time::updateDeltaTime();

        GameManager::getInstance().camera1.getViewMatrix();
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        SDL_PollEvent(&e);

        switch(e.type) {

            case SDL_KEYDOWN :

                switch(e.key.keysym.sym) {

                    case SDLK_a:
                        //c1.addRotation( glm::vec3(0, 1, 0), 90.0f );
                   GameManager::getInstance().camera1.rotateLeft(0.05f);
                    break ;

                    case SDLK_d:
                        //c1.addRotation( glm::vec3(0, 1, 0), 90.0f );
                        GameManager::getInstance().camera1.rotateLeft(-0.05f);
                        break ;


                    case SDLK_w:
                       // c1.addRotation( glm::vec3(0, 1, 0), 90.0f );
                    GameManager::getInstance().camera1.moveFront(0.005f);
                    break ;

                    case SDLK_s:
                        // c1.addRotation( glm::vec3(0, 1, 0), 90.0f );
                        GameManager::getInstance().camera1.moveFront(-0.005f);
                        break ;


                }


        }

        // Jeu

        //demon.addRotation( glm::vec3(0, 1, 0), Time::deltaTime * 0.5d );

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

FilePath GameManager::getAppPath() {
    return applicationPath.dirPath();
}
