//
// Created by Valentin on 27/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_CUBE3D_H
#define IMACGL_CUBE3D_H

#include <GL/glew.h>
#include <GL/glut.h>

#include <string>
#include <glm/vec3.hpp>
#include "Object3D.h"

#include "Mesh3D.h"

class Porte : public Object3D {

private:
    bool isOpen;
    Mesh3D * battant_porte;
    glm::vec2 pos;

public:
    Porte();
    void draw();
    glm::vec2 getPos();
    bool getIsOpen() { return isOpen; }
    bool setIsOpen( bool state ) { isOpen = state; }

};


#endif //IMACGL_CUBE3D_H
