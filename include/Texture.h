//
// Created by Vincent on 28/12/2016.
//

#ifndef IMACGL_TEXTURE_H
#define IMACGL_TEXTURE_H

#include <glimac/glm.hpp>
#include <glimac/common.hpp>

#include <GL/glew.h>
#include <GL/glut.h>

#include <vector>
#include <map>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include "ShaderProgram.h"


class Texture {
private:
public:
    GLuint textId;
    std::string textureName;
    static std::map<std::string,Texture*> textures;
    std::unique_ptr<Image> textureImg;
    Texture(std::string textureName);

};


#endif //IMACGL_TEXTURE_H
