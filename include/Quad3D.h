//
// Created by Vincent on 27/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_QUAD3D_H
#define IMACGL_QUAD3D_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/BBox.hpp>

#include "Object3D.h"
#include "GameManager.h"

class Quad3D : public Object3D {

private:
    GLuint vao;
    GLuint ibo;
    SimpleTexture shaderProgram;

public:
    Quad3D(std::string textureName);
    void draw();
};

#endif //IMACGL_QUAD3D_H
