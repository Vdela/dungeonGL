//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC

#ifndef IMACGL_TRANSFORMMATRIX_H
#define IMACGL_TRANSFORMMATRIX_H

#include <glimac/glm.hpp>
#include <math.h>

class TransformMatrix {

public:
    /*
    static glm::mat3 translate(float x, float y, float z);
    static glm::mat3 scale(float x, float y, float z);
    static glm::mat3 rotate(float x, float y, float z);
     */
    static glm::mat4 translate(float x, float y, float z);

};


#endif //IMACGL_TRANSFORMMATRIX_H
