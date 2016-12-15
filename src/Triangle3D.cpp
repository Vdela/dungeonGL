//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC



#include "../include/Triangle3D.h"

using namespace glimac;

Triangle3D::Triangle3D() {

    uMVPMatrixLoc = glGetUniformLocation(Object3D::programID, "uMVPMatrix");
    uMVMatrixLoc = glGetUniformLocation(Object3D::programID, "uMVMatrix");
    uNormalMatrixLoc = glGetUniformLocation(Object3D::programID, "uNormalMatrix");

    //*********************************
    // HERE SHOULD COME THE INITIALIZATION CODE
    //*********************************

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<ShapeVertex> vertices;
    float unit = 0.5f;
    vertices.push_back( ShapeVertex( glm::vec3(-unit,-unit,0), glm::vec3(1, 0, 0), glm::vec2(0,0) ) );
    vertices.push_back( ShapeVertex( glm::vec3(unit,-unit,0), glm::vec3(1, 1, 0), glm::vec2(0,0) ) );
    vertices.push_back( ShapeVertex( glm::vec3(0,unit,0), glm::vec3(1, 1, 1), glm::vec2(0,0) ) );


    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    //création VAO : pour pouvoir interpreter les données du VBO
    //creation comme gen vbo

    glGenVertexArrays(1, &vao);

    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);


    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXCORD = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXCORD);


    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)( offsetof(ShapeVertex, position) ) );
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)( offsetof(ShapeVertex, normal) ) );
    glVertexAttribPointer(VERTEX_ATTR_TEXCORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*)( offsetof(ShapeVertex, texCoords) ) );
    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);

}

void Triangle3D::draw() {

     /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

    glUniformMatrix4fv(uMVPMatrixLoc,1,GL_FALSE,glm::value_ptr(projMatrix * modelMatrix));
    glUniformMatrix4fv(uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(normalMatrix));

    //Dessiner avec le VAO
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
