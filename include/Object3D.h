//
// Created by Vincent on 14/12/2016.
//

#ifndef IMACGL_OBJECT3D_H
#define IMACGL_OBJECT3D_H

#include <glimac/glm.hpp>
#include <glimac/common.hpp>

#include <GL/glew.h>
#include <GL/glut.h>

#include <vector>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include "ShaderProgram.h"


class Object3D {

protected:
    glm::mat4 modelMatrix;

    glm::mat4 translationMatrix;
    glm::mat4 rotationMatrix;
    glm::mat4 scaleMatrix;

    GLuint texture;

    static const glm::mat4 projMatrix;

    static std::vector<Object3D*> sceneObjects;
    static GLuint programID;
public:
    Object3D();
    virtual void draw() = 0;

    static const std::vector<Object3D*>& getSceneObjects() { return sceneObjects; }
    static void setProgramID(GLuint programID) { Object3D::programID = programID; }

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


#endif //IMACGL_OBJECT3D_H
