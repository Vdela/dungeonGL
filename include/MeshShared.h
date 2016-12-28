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
#include <map>

#include "Object3D.h"

class Texture;

class MeshShared {
private:
public:
    GLuint vao;
    GLuint ibo;
    SimpleTextureLambert shaderProgram;
    Geometry geometry;
    MeshShared() {};
    MeshShared(std::string meshName, std::string meshMt, Texture * texture);
    static std::map<std::string,MeshShared*> meshesMap;
};


#endif //IMACGL_MESHSHARED_H
