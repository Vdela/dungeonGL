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

#include "Object3D.h"
#include "GameManager.h"

class Triangle3D : public Object3D {

private:
    GLuint vao;
    SimpleTexture shaderProgram;

public:
    Triangle3D(std::string textureName);
    void draw();

};


#endif //IMACGL_TRIANGLE3D_H
