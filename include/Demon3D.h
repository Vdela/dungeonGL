//
// Created by Vincent on 26/12/2016.
//

#define GLEW_STATIC


#ifndef IMACGL_DEMON3D_H
#define IMACGL_DEMON3D_H

#include "Time.h"
#include "Oscillation.h"

class Object3D;
class Mesh3D;

class Demon3D : public Object3D {


private:
    Mesh3D * skull;
    Mesh3D * chest;
    Mesh3D * shoulders;
    Mesh3D * leftHand;
    Mesh3D * rightHand;

    Oscillation bodyOscillation;

public:
    Demon3D();
    void draw();

};


#endif //IMACGL_DEMON3D_H
