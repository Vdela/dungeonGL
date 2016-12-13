//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC



#include "../include/Cube3D.h"

using namespace glimac;

struct Vertex2DUV{
    glm::vec2 pos;
    glm::vec2 texture;

    Vertex2DUV( glm::vec2 pos, glm::vec2 texture){
        this->pos = pos;
        this->texture = texture;
    }

};

Cube3D::Cube3D() {

    //charge les shaders que l'on a ajouté dans le dossier shaders
    FilePath applicationPath(".\\opengl.exe");
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\color2D.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\color2D.fs.glsl");
    program.use();

    // Matrice de transformation
    this->uModelMatrixID = glGetUniformLocation( program.getGLId(), "uModelMatrix" );

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices[] = {-0.5f, -0.5f,1.f, 0.f, 0.f, //premier sommet, couleurs de 0 à 1
                          0.5f, -0.5f,  0.f, 1.f, 0.f, //deuxieme sommet
                          0.0f, 0.5f, 0.f, 0.f, 1.f //troisieme sommet
    };


    glBufferData(GL_ARRAY_BUFFER, 15*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    //Debinder glBindBufer avec second para 0
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    //création VAO : pour pouvoir interpreter les données du VBO
    //creation comme gen vbo

    glGenVertexArrays(1, &vao);

    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    //activation des attributs de vertex, prend en para l'index renseignant le type de data
    //on prefere les déclarer auparavant dans des constantes plutot que en clair
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR= 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);


    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT),0);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT),(const GLvoid*)(2*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);

}

void Cube3D::Draw() {

     /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // Transformations
    glUniformMatrix3fv( uModelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix) );

    //Dessiner avec le VAO
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Cube3D::Translate(float x, float y, float z) {
    this->modelMatrix = TransformMatrix::translate( x , y , z);
}



