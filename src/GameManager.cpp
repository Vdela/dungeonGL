//
// Created by Vincent on 15/12/2016.
//

#include "../include/GameManager.h"
#include "../include/Demon3D.h"
#include "../include/Player.h"
#include "../include/Dungeon.h"
#include "../include/Porte.h"

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

    //Init niveau
    Dungeon donjon;
    donjon.chargementDonjon((char*) "test1.txt");
    Niveau* pNiveau = donjon.getNiveau();
    pNiveau->createMap();
    pNiveau->createTresors();
    pNiveau->createMonstres();

    std::cout << "gameManager" << std::endl;

    // Init Player
    Player& player = Player::getInstance();
    glm::vec2 startPos = pNiveau->getStartPos();
    player.setPositionOnMap((int)startPos.x, (int)startPos.y, true); //cran vers le bas ; cran vers la droite
    Mesh3D * blade = new Mesh3D( "blade.obj", "blade.mtl", "iron.png" );
    blade->setTranslation( (int)startPos.x, 0, (int)startPos.y );
    player.setWeapon( blade );

    int index;

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

                switch(e.key.keysym.sym) {

                    case SDLK_a: // q en azerty
                        player.rotateLeft();
                    break ;

                    case SDLK_d:
                        player.rotateRight();
                        break ;

                    case SDLK_w: // z en azerty
                        if ( !(pNiveau->faceCoffre(player.getPositionOnMap() + player.getLookDirection(), &index)) && Cell::walkableCell( pNiveau->getCell( player.getPositionOnMap() + player.getLookDirection() ) ) ) {
                            player.stepForward();
                        }
                    break ;

                    case SDLK_s:
                        if ( !(pNiveau->faceCoffre(player.getPositionOnMap() - player.getLookDirection(), &index)) && Cell::walkableCell( pNiveau->getCell( player.getPositionOnMap() - player.getLookDirection() ) ) ) {
                            player.stepBack();
                        }
                        break ;

                    case SDLK_q: // a en azerty
                        if ( !(pNiveau->faceCoffre(player.getPositionOnMap() + player.getLookDirection(), &index)) && Cell::walkableCell( pNiveau->getCell( player.getPositionOnMap() + player.getLeftDirection() ) ) ) {
                            player.stepLeft();
                        }
                        break ;

                    case SDLK_e:
                        if ( !(pNiveau->faceCoffre(player.getPositionOnMap() - player.getLookDirection(), &index)) && Cell::walkableCell( pNiveau->getCell( player.getPositionOnMap() - player.getLeftDirection() ) ) ) {
                            player.stepRight();
                        }
                        break ;

                    case SDLK_SPACE: {
                        player.hit();
                        pNiveau->frappeCoffre(player.getPositionOnMap() + player.getLookDirection());
                        pNiveau->frappeMonstre(player.getPositionOnMap() + player.getLookDirection());
                        break;
                    }

                    default:
                        break ;




                }


        }

        // Jeu

        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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