#pragma once

#include <GL/glew.h>
#include "glm.hpp"

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    ShapeVertex() {}

    ShapeVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords) {
        this->position = position;
        this->normal = normal;
        this->texCoords = texCoords;
    }

};

}
