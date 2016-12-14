//
// Created by Vincent on 13/12/2016.
//

#include "../include/TransformMatrix.h"
/*
glm::mat3 TransformMatrix::translate(float x, float y, float z) {
    glm::mat3 res = glm::mat3( glm::vec3(1,0,0), glm::vec3(0,1,0), glm::vec3(x,y,z) );
    return res;
}

glm::mat3 TransformMatrix::scale(float x, float y, float z) {
    glm::mat3 res = glm::mat3( glm::vec3(x,0,0), glm::vec3(0,y,0), glm::vec3(0,0,z) );
    return res;
}

glm::mat3 TransformMatrix::rotate(float a) {
    glm::mat3 res = glm::mat3( glm::vec3(cos(glm::radians(a)),sin(glm::radians(a)),0), glm::vec3(-sin(glm::radians(a)),cos(glm::radians(a)),0), glm::vec3(0,0,1) );
    return res;
}
*/
glm::mat4 TransformMatrix::translate(float x, float y, float z) {
    glm::mat4 res = glm::mat4( glm::vec4(1,0,0,0), glm::vec4(0,1,0,0), glm::vec4(0,0,1,0), glm::vec4(x,y,z,1) );
    return res;
}