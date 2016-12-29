//
// Created by Vincent on 28/12/2016.
//

#include "../include/Texture.h"

std::map<std::string,Texture*> Texture::textures = std::map<std::string,Texture*>();

Texture::Texture(std::string textureName) {
    this->textureName = textureName;
    textures[ textureName ] = this;

    FilePath path(".\\opengl.exe");
    textureImg = loadImage( path.dirPath() + "\\..\\..\\assets\\textures\\" + textureName);
}
