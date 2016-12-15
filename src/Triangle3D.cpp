//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC



#include "../include/Triangle3D.h"

using namespace glimac;

Triangle3D::Triangle3D() {
    //charge les shaders que l'on a ajouté dans le dossier shaders
    FilePath applicationPath(".\\opengl.exe");
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\color2D.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\color2D.fs.glsl");
    program.use();

    // Matrice de transformation
    this->uModelMatrixID = glGetUniformLocation( program.getGLId(), "uModelMatrix" );


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    std::vector<Triangle> vertices;
    float unit = 0.5f;
    vertices.push_back( Triangle( glm::vec3(-unit,-unit,0), glm::vec3(1, 0, 0) ) );
    vertices.push_back( Triangle( glm::vec3(unit,-unit,0), glm::vec3(1, 1, 0) ) );
    vertices.push_back( Triangle( glm::vec3(0,unit,0), glm::vec3(1, 1, 1) ) );


    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Triangle), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
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
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle), (const GLvoid*)( offsetof(Triangle, pos) ) );
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle), (const GLvoid*)( offsetof(Triangle, color) ) );
    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);

}

void Triangle3D::draw() {

     /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glUniformMatrix4fv( uModelMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix * modelMatrix) );
    // !!! 4fv !!!

    //Dessiner avec le VAO
    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
