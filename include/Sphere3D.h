//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_SPHERE3D_H
#define IMACGL_SPHERE3D_H


#include <iostream>
#include <vector>
#include <math.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

class Sphere3D {
private:
    GLuint vao;
    glm::mat4 modelMatrix;
    GLint uModelMatrixID;

    GLint uMVPMatrixLoc;
    GLint uMVMatrixLoc;
    GLint uNormalMatrixLoc;
    Sphere sphere;

    glm::mat4 projMatrix;
    glm::mat4 mvMatrix;
    glm::mat4 normalMatrix;

public:
    Sphere3D(SDLWindowManager windowManager);
    void draw();
    void setTransform(glm::mat4);
    void addTransform(glm::mat4);
};


#endif //IMACGL_SPHERE3D_H
