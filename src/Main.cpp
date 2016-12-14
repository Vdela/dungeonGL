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

    // Init de l'application
    SDLWindowManager windowManager(800, 800, "DungeonGL");
    initGlew();
    glEnable(GL_DEPTH_TEST);


    //===== Construction du monde =====//
    Triangle3D triangle;
    //Sphere3D sphere(windowManager);
    triangle.setTranslation( 0, 0, -5 );



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
        triangle.addRotation( glm::vec3(0, 0, 1), 0.025f );
        triangle.setScale( 2, 1.00f, 1.00f );
        //cube.addTranslation( 0, 0, -0.025f );

        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendu des objets
        triangle.draw();


        // Update the display
        windowManager.swapBuffers();
    }

    //liberation des ressources
    // TODO
    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);

    return 0;
}
