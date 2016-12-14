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

class Triangle3D {

private:
    GLuint vao;
    glm::mat4 modelMatrix;
    GLint uModelMatrixID;

    glm::mat4 translationMatrix;
    glm::mat4 rotationMatrix;
    glm::mat4 scaleMatrix;

public:
    Triangle3D();
    void draw();
    /*
    void setTransform(glm::mat4 transformMatrix);
    void addTransform(glm::mat4 transformMatrix);
    void addTransformLocal(glm::mat4 transformMatrix);
    */

    void setTranslation(glm::vec3 translation);
    void addTranslation(glm::vec3 translation);
    void setTranslation(float x, float y, float z);
    void addTranslation(float x, float y, float z);

    void setRotation(glm::vec3 rotation, float speed);
    void addRotation(glm::vec3 rotation, float speed);

    void setScale(glm::vec3 scale);
    void setScale(float x, float y, float z);
    void addScale(glm::vec3 scale);
    void addScale(float x, float y, float z);
};


#endif //IMACGL_CUBE3D_H
