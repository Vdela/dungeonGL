//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_CUBE3D_H
#define IMACGL_CUBE3D_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/BBox.hpp>

#include "GameManager.h"
#include "Object3D.h"


class Cube3D : public Object3D {

private:
    GLuint vao;
    GLuint ibo;
    SimpleTexture shaderProgram;

public:
    Cube3D(std::string textureName);
    void draw();
};


#endif //IMACGL_CUBE3D_H
