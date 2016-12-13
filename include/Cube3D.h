//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_CUBE3D_H
#define IMACGL_CUBE3D_H

#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>

#include "TransformMatrix.h"

class Cube3D {

private:
    GLuint vao;
    glm::mat3 modelMatrix;
    GLint uModelMatrixID;
public:
    Cube3D();
    void Draw();
    void Translate(float x, float y, float z);
};


#endif //IMACGL_CUBE3D_H
