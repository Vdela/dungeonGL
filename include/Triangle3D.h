//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_TRIANGLE3D_H
#define IMACGL_TRIANGLE3D_H

#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>

#include "TransformMatrix.h"
#include "Object3D.h"

class Triangle3D : public Object3D {

private:
    GLuint vao;

public:
    Triangle3D();
    void draw();
};


#endif //IMACGL_TRIANGLE3D_H
