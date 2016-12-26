//
// Created by Vincent on 15/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_GAMEMANAGER_H
#define IMACGL_GAMEMANAGER_H

#include <stddef.h>
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
#include <glimac/FreeflyCamera.hpp>

#include "Triangle3D.h"
#include "Cube3D.h"
#include "Niveau.h"


using namespace glimac;

class GameManager {

public:
    static GameManager& getInstance();
    void initGame(uint32_t width, uint32_t height, char* gameName);
    FreeflyCamera camera1;
    FilePath getAppPath();
private:
    GameManager();
    static GameManager instance;
    void initGlew();

    FilePath applicationPath;




};


#endif //IMACGL_GAMEMANAGER_H
