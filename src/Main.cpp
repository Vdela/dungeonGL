#define GLEW_STATIC

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include <SDL/SDL.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>

#include "../include/Triangle3D.h"
#include "../include/Cube3D.h"
#include "../include/Sphere3D.h"

using namespace glimac;

void initGlew() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv) {

    std::cout << "test log console" << std::endl;

    // Init de l'application
    SDLWindowManager windowManager(800, 800, "DungeonGL");
    initGlew();
    glEnable(GL_DEPTH_TEST);


    //===== Construction du monde =====//
    Cube3D cube;
    //Sphere3D sphere(windowManager);
    cube.setTranslation( 0, 0, -5 );

    Cube3D c1,c2,c3;
    c1.setTranslation( -1, -2, -5 );
    c2.setTranslation( 0, -2, -5 );
    c3.setTranslation( 1, -2, -5 );

    Triangle3D t;
    t.setTranslation( 0,1.35,-3 );



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
        cube.addRotation( glm::vec3(0, 1, 0), 0.025f );
        cube.addRotation( glm::vec3(1, 0, 0), 0.01f );
        cube.addRotation( glm::vec3(0, 0, 1), 0.015f );
        c1.addRotation( glm::vec3(1, 0, 0), 0.005f );
        c2.addRotation( glm::vec3(1, 0, 0), 0.005f );
        c3.addRotation( glm::vec3(1, 0, 0), 0.005f );
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

    //liberation des ressources
    // TODO
    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);

    return 0;
}
