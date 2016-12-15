//
// Created by Vincent on 15/12/2016.
//

#ifndef IMACGL_SHADERPROGRAM_H
#define IMACGL_SHADERPROGRAM_H

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

struct ShaderProgram {
    Program program;
};

struct SimpleTexture : ShaderProgram{

    GLint uMVPMatrixLoc;
    GLint uMVMatrixLoc;
    GLint uNormalMatrixLoc;
    GLint uTextureID;

    SimpleTexture() {
        FilePath applicationPath(".\\opengl.exe"); // TODO mettre ça ailleurs, c'est pas propre là
        program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\3D.vs.glsl",
                                      applicationPath.dirPath() + "\\..\\..\\shaders\\tex3D.fs.glsl");

        uMVPMatrixLoc = glGetUniformLocation( program.getGLId(), "uMVPMatrix");
        uMVMatrixLoc = glGetUniformLocation( program.getGLId(), "uMVMatrix");
        uNormalMatrixLoc = glGetUniformLocation( program.getGLId(), "uNormalMatrix");
        uTextureID = glGetUniformLocation( program.getGLId(), "uTexture" );
    }


};

#endif //IMACGL_SHADERPROGRAM_H
