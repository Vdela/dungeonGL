//
// Created by Vincent on 28/12/2016.
//

#define GLEW_STATIC

#ifndef IMACGL_MESHSHARED_H
#define IMACGL_MESHSHARED_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/BBox.hpp>
#include <glimac/Geometry.hpp>

#include "Object3D.h"

class MeshShared {
private:
    GLuint vao;
    GLuint ibo;
    SimpleTextureLambert shaderProgram;
    Geometry geometry;
public:
    MeshShared() {};
    MeshShared(std::string meshName, std::string meshMt, std::string textureName);
};


#endif //IMACGL_MESHSHARED_H
