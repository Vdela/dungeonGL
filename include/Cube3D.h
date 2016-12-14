//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_CUBE3D_H
#define IMACGL_CUBE3D_H

#include <iostream>
#include <vector>
#include <math.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/BBox.hpp>

#include "Object3D.h"
#include "TransformMatrix.h"

class Cube3D : public Object3D {

private:
    GLuint vao;
    GLuint ibo;


public:
    Cube3D();
    void draw();
};


#endif //IMACGL_CUBE3D_H
