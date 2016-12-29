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
    bool ouverture;
    Mesh3D * battant_porte;
    float posX_porte;
    float posY_porte;

public:
    Porte();
    void draw();
    float get_posX_porte();
    float get_posY_porte();
    void set_posX_porte(float _X);
    void set_posY_porte(float _Y);

};


#endif //IMACGL_CUBE3D_H
