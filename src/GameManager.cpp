//
// Created by Vincent on 15/12/2016.
//

#include "../include/GameManager.h"
#include "../include/Demon3D.h"
#include "../include/Player.h"

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

    // Init Player
    Player& player = Player::getInstance();
    player.setPositionOnMap(1, 1); //cran vers le bas ; cran vers la droite
    //player.setPositionOnMap(2, 25); //x, y // POUR MAP 1


    Niveau niveau1;
    niveau1.lectureMap((char*)"map3.ppm");
    niveau1.createMap();


    Demon3D demon;
    demon.setScale( 0.05f );
    demon.setTranslation( 1, -0.5f, 2 );
    demon.setRotation( glm::vec3(0, 1, 0), 270 );

    Mesh3D heart( "heart.obj", "heart.mtl", "wood.jpg" );
    heart.setScale( 1.0f );
    heart.setTranslation( 1, 0, 5 );

    //=================================//
    //========== Loop du jeu ==========//
    //=================================//
    // Application loop:
    bool done = false;

    while(!done) {
        Time::updateDeltaTime();

        player.camera.getViewMatrix();
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

                float moveSpeed = 6.0f;
                float rotSpeed = 120.0f;

                switch(e.key.keysym.sym) {

                    case SDLK_a: // q en azerty
                        player.rotateLeft();
                    break ;

                    case SDLK_d:
                        player.rotateRight();
                        break ;

                    case SDLK_w: // z en azerty
                        if ( Cell::walkableCell( niveau1.getCell( player.getPositionOnMap() + player.getLookDirection() ) ) ) {
                            player.stepForward();
                        }
                    break ;

                    case SDLK_s:
                        if ( Cell::walkableCell( niveau1.getCell( player.getPositionOnMap() - player.getLookDirection() ) ) ) {
                            player.stepBack();
                        }
                        break ;

                    case SDLK_q: // a en azerty
                        if ( Cell::walkableCell( niveau1.getCell( player.getPositionOnMap() + player.getLeftDirection() ) ) ) {
                            player.stepLeft();
                        }
                        break ;

                    case SDLK_e:
                        if ( Cell::walkableCell( niveau1.getCell( player.getPositionOnMap() - player.getLeftDirection() ) ) ) {
                            player.stepRight();
                        }
                        break ;

                    default:
                        break ;


                }


        }

        // Jeu
        heart.addRotation( glm::vec3(0, 1, 0), (float)Time::deltaTime * 10.0f );


        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendu des objets de la scene
        for ( std::vector<Object3D*>::const_iterator it = Object3D::getSceneObjects().begin() ;  it != Object3D::getSceneObjects().end() ; it++ ) {
            (*it)->draw();
        }
        player.draw();

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
