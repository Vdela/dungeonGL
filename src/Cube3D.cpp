//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC



#include "../include/Cube3D.h"

using namespace glimac;

struct Triangle{
    glm::vec3 pos;
    glm::vec3 color;

    Triangle( glm::vec3 pos, glm::vec3 color){
        this->pos = pos;
        this->color = color;
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


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float unit = 0.5f;
    BBox3f box( glm::vec3(-unit,-unit,-unit), glm::vec3(unit,unit,unit) );

    glm::vec3 upA( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 upB( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upC( -box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upD( -box.upper.x, box.upper.y, box.upper.z );

    glm::vec3 lowA( box.upper.x, -box.upper.y, box.upper.z  );
    glm::vec3 lowB( box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowC( -box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowD( -box.upper.x, -box.upper.y, box.upper.z );

    std::vector<Triangle> vertices;
    vertices.push_back( Triangle( upA, glm::vec3(1, 0, 0) ) );
    vertices.push_back( Triangle( upB, glm::vec3(1, 1, 0) ) );
    vertices.push_back( Triangle( upC, glm::vec3(1, 1, 1) ) );
    vertices.push_back( Triangle( upD, glm::vec3(0, 1, 1) ) );
    vertices.push_back( Triangle( lowA, glm::vec3(0, 0, 1) ) );
    vertices.push_back( Triangle( lowB, glm::vec3(1, 0, 1) ) );
    vertices.push_back( Triangle( lowC, glm::vec3(1, 1, 0) ) );
    vertices.push_back( Triangle( lowD, glm::vec3(1, 0, 0) ) );


    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Triangle), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // Ajout ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    uint32_t indices[] = {
            0, 1, 2,//faceSup
            0, 2, 3,
            0, 4, 5,//
            0, 5, 1,
            0, 4, 7,//
            0, 7, 3,
            3, 7, 6,//
            3, 6, 2,
            1, 2, 6,//
            1, 6, 5,
            4, 5, 6,//
            4, 6, 7
    };
    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    glGenVertexArrays(1, &vao);

    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

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

void Cube3D::draw() {

     /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    glm::mat4 projMatrix;
    projMatrix = glm::perspective<float>(glm::radians(70.f),1.0,0.1f,100.f);
    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glUniformMatrix4fv( uModelMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix * modelMatrix) );
    // !!! 4fv !!!

    //Dessiner avec le VAO
    glBindVertexArray(vao);

    //glDrawArrays(GL_TRIANGLES, 0, 3); // avant ibo
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Cube3D::setTranslation(glm::vec3 translation) {
    this->translationMatrix = glm::translate( glm::mat4(1), translation );
}

void Cube3D::addTranslation(glm::vec3 translation) {
    this->translationMatrix *= glm::translate( glm::mat4(1), translation );
}

void Cube3D::setTranslation(float x, float y, float z) {
    this->translationMatrix = glm::translate( glm::mat4(1), glm::vec3(x,y,z) );
}

void Cube3D::addTranslation(float x, float y, float z) {
    this->translationMatrix *= glm::translate( glm::mat4(1), glm::vec3(x,y,z) );
}


void Cube3D::setRotation(glm::vec3 rotation, float speed) {
    this->rotationMatrix = glm::rotate(glm::mat4(), speed, rotation);
}

void Cube3D::addRotation(glm::vec3 rotation, float speed) {
    this->rotationMatrix *= glm::rotate(glm::mat4(), speed, rotation);
}

void Cube3D::setScale(glm::vec3 scale) {
    this->scaleMatrix = glm::scale(glm::mat4(), scale);
}

void Cube3D::setScale(float x, float y, float z) {
    this->scaleMatrix = glm::scale( glm::mat4(), glm::vec3(x, y, z) );
}

void Cube3D::addScale(glm::vec3 scale) {
    this->scaleMatrix *= glm::scale(glm::mat4(), scale);
}

void Cube3D::addScale(float x, float y, float z) {
    this->scaleMatrix *= glm::scale( glm::mat4(), glm::vec3(x, y, z) );
}
