//
// Created by Vincent on 26/12/2016.
//

#define GLEW_STATIC

#ifndef IMACGL_MESH3D_H
#define IMACGL_MESH3D_H

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/BBox.hpp>
#include <glimac/Geometry.hpp>

#include "Object3D.h"
#include "MeshShared.h"


class Mesh3D : public Object3D {

private:
    SimpleTextureLambert shaderProgram;
    MeshShared * meshShared;
    Texture * texture;
public:
    //Mesh3D() {};
    Mesh3D(std::string meshName, std::string meshMt, std::string textureName);
    void draw();
};



#endif //IMACGL_MESH3D_H
