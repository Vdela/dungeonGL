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
        FilePath applicationPath(".\\opengl.exe");
        program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\3D.vs.glsl",
                                      applicationPath.dirPath() + "\\..\\..\\shaders\\tex3D.fs.glsl");

        uMVPMatrixLoc = glGetUniformLocation( program.getGLId(), "uMVPMatrix");
        uMVMatrixLoc = glGetUniformLocation( program.getGLId(), "uMVMatrix");
        uNormalMatrixLoc = glGetUniformLocation( program.getGLId(), "uNormalMatrix");
        uTextureID = glGetUniformLocation( program.getGLId(), "uTexture" );
    }


};

struct SimpleTextureLambert : ShaderProgram{

    GLint uMVPMatrixLoc;
    GLint uMVMatrixLoc;
    GLint uNormalMatrixLoc;
    GLint uTextureID;
    GLint uLightPosLoc;
    GLint uLightIntensityLoc;

    SimpleTextureLambert() {
            FilePath applicationPath(".\\opengl.exe");
            program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\3D.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\tex3DLambert.fs.glsl");

            uMVPMatrixLoc = glGetUniformLocation( program.getGLId(), "uMVPMatrix");
            uMVMatrixLoc = glGetUniformLocation( program.getGLId(), "uMVMatrix");
            uNormalMatrixLoc = glGetUniformLocation( program.getGLId(), "uNormalMatrix");
            uTextureID = glGetUniformLocation( program.getGLId(), "uTexture" );
            uLightPosLoc = glGetUniformLocation( program.getGLId(), "uLightPos" );
            uLightIntensityLoc = glGetUniformLocation( program.getGLId(), "uLightIntensity" );
    }


};

#endif //IMACGL_SHADERPROGRAM_H
