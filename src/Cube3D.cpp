//
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC



#include "../include/Cube3D.h"

using namespace glimac;


Cube3D::Cube3D(std::string textureName) {
/*
    uMVPMatrixLoc = glGetUniformLocation(Object3D::programID, "uMVPMatrix");
    uMVMatrixLoc = glGetUniformLocation(Object3D::programID, "uMVMatrix");
    uNormalMatrixLoc = glGetUniformLocation(Object3D::programID, "uNormalMatrix");
    uTextureID = glGetUniformLocation( Object3D::programID, "uTexture" );
*/

    shaderProgram = SimpleTexture();

    //********************************
    //HERE SHOULD COME THE INITIALIZATION CODE
    //*********************************

    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float unit = 0.5f;
    BBox3f box( glm::vec3(-unit,-unit,-unit), glm::vec3(unit,unit,unit) );

    /* Avant cube rework. 8 points partagés
    glm::vec3 upA( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 upB( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upC( -box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upD( -box.upper.x, box.upper.y, box.upper.z );

    glm::vec3 lowA( box.upper.x, -box.upper.y, box.upper.z  );
    glm::vec3 lowB( box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowC( -box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowD( -box.upper.x, -box.upper.y, box.upper.z );

    std::vector<ShapeVertex> vertices;
    //************************* vec3 position , vec3 normale, vec2 textCoord
     */
    /*
    vertices.push_back( ShapeVertex( upA, glm::vec3(1, 0, 0), glm::vec2(1,0) ) );
    vertices.push_back( ShapeVertex( upB, glm::vec3(1, 1, 0), glm::vec2(1,1) ) );
    vertices.push_back( ShapeVertex( upC, glm::vec3(1, 1, 1), glm::vec2(0,1) ) );
    vertices.push_back( ShapeVertex( upD, glm::vec3(0, 1, 1), glm::vec2(0,0) ) );
    vertices.push_back( ShapeVertex( lowA, glm::vec3(0, 0, 1), glm::vec2(0,1) ) );
    vertices.push_back( ShapeVertex( lowB, glm::vec3(1, 0, 1), glm::vec2(0,0) ) );
    vertices.push_back( ShapeVertex( lowC, glm::vec3(1, 1, 0), glm::vec2(1,0) ) );
    vertices.push_back( ShapeVertex( lowD, glm::vec3(1, 0, 0), glm::vec2(1,1) ) );
     */

    // cube rework : 24 points partagés.
    glm::vec3 frontA( -box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 frontB( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 frontC( box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 frontD( -box.upper.x, -box.upper.y, -box.upper.z );

    glm::vec3 rightA( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 rightB( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 rightC( box.upper.x, -box.upper.y, box.upper.z  );
    glm::vec3 rightD( box.upper.x, -box.upper.y, -box.upper.z );

    glm::vec3 backA( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 backB(-box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 backC( -box.upper.x, -box.upper.y, box.upper.z );
    glm::vec3 backD( box.upper.x, -box.upper.y, box.upper.z  );

    glm::vec3 bottomA( -box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 bottomB( box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 bottomC( box.upper.x, -box.upper.y, box.upper.z  );
    glm::vec3 bottomD( -box.upper.x, -box.upper.y, box.upper.z );

    glm::vec3 leftA( -box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 leftB( -box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 leftC( -box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 leftD( -box.upper.x, -box.upper.y, box.upper.z );

    glm::vec3 topA( -box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 topB( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 topC( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 topD( -box.upper.x, box.upper.y, -box.upper.z );

    std::vector<ShapeVertex> vertices;
    vertices.push_back( ShapeVertex( frontA, glm::vec3(1, 0, 0), glm::vec2(0,0) ) );//0
    vertices.push_back( ShapeVertex( frontB, glm::vec3(1, 0, 0), glm::vec2(0.3333,0) ) );
    vertices.push_back( ShapeVertex( frontC, glm::vec3(1, 0, 0), glm::vec2(0.3333,0.5) ) );
    vertices.push_back( ShapeVertex( frontD, glm::vec3(1, 0, 0), glm::vec2(0,0.5) ) );

    vertices.push_back( ShapeVertex( rightA, glm::vec3(1, 0, 0), glm::vec2(0.3333,0) ) );//4
    vertices.push_back( ShapeVertex( rightB, glm::vec3(1, 0, 0), glm::vec2(0.6666,0) ) );
    vertices.push_back( ShapeVertex( rightC, glm::vec3(1, 0, 0), glm::vec2(0.6666,0.5) ) );
    vertices.push_back( ShapeVertex( rightD, glm::vec3(1, 0, 0), glm::vec2(0.3333,0.5) ) );

    vertices.push_back( ShapeVertex( backA, glm::vec3(1, 0, 0), glm::vec2(0.6666,0) ) );//8
    vertices.push_back( ShapeVertex( backB, glm::vec3(1, 0, 0), glm::vec2(1,0) ) );
    vertices.push_back( ShapeVertex( backC, glm::vec3(1, 0, 0), glm::vec2(1,0.5) ) );
    vertices.push_back( ShapeVertex( backD, glm::vec3(1, 0, 0), glm::vec2(0.6666,0.5) ) );

    vertices.push_back( ShapeVertex( bottomA, glm::vec3(1, 0, 0), glm::vec2(0,0.5) ) );//12
    vertices.push_back( ShapeVertex( bottomB, glm::vec3(1, 0, 0), glm::vec2(0.3333,0.5) ) );
    vertices.push_back( ShapeVertex( bottomC, glm::vec3(1, 0, 0), glm::vec2(0.3333,1) ) );
    vertices.push_back( ShapeVertex( bottomD, glm::vec3(1, 0, 0), glm::vec2(0,1) ) );

    vertices.push_back( ShapeVertex( leftA, glm::vec3(1, 0, 0), glm::vec2(0.3333,0.5) ) );//16
    vertices.push_back( ShapeVertex( leftB, glm::vec3(1, 0, 0), glm::vec2(0.6666,0.5) ) );
    vertices.push_back( ShapeVertex( leftC, glm::vec3(1, 0, 0), glm::vec2(0.6666,1) ) );
    vertices.push_back( ShapeVertex( leftD, glm::vec3(1, 0, 0), glm::vec2(0.3333,1) ) );

    vertices.push_back( ShapeVertex( topA, glm::vec3(1, 0, 0), glm::vec2(0.6666,0.5) ) );//20
    vertices.push_back( ShapeVertex( topB, glm::vec3(1, 0, 0), glm::vec2(1,0.5) ) );
    vertices.push_back( ShapeVertex( topC, glm::vec3(1, 0, 0), glm::vec2(1,1) ) );
    vertices.push_back( ShapeVertex( topD, glm::vec3(1, 0, 0), glm::vec2(0.6666,1) ) );

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // Ajout ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    /* // avant rework cube
    uint32_t indices[] = {
            0, 2, 3,//faceSup
            0, 2, 1,
            0, 5, 4,// non ok
            0, 5, 1,
            0, 7, 4,//ok
            0, 7, 3,
            6, 4, 7,//ok
            6, 4, 5,
            6, 1, 5,//ok
            6, 1, 2,
            6, 3, 7,//non ok
            6, 3, 2
    }; */
    uint32_t indices[] = {
            3, 1, 0,//front
            3, 1, 2,
            7, 5, 4,//right
            7, 5, 6,
            11, 9, 8,//back
            11, 9, 10,
            15, 13, 12,//bottom non ok
            15, 13, 14,
            19, 17, 16,//left
            19, 17, 18,
            23, 21, 20,//top
            23, 21, 22
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


    // Chargement Texture
    FilePath applicationPath(".\\opengl.exe");
    //std::unique_ptr<Image> textureImg = loadImage( applicationPath.dirPath() + "\\..\\..\\assets\\textures\\cubeDebugUV.png" );
    std::unique_ptr<Image> textureImg = loadImage( applicationPath.dirPath() + "\\..\\..\\assets\\textures\\" + textureName );

    if ( textureImg == NULL ) {
        std::cerr << "IMAGE NOT FOUND!" << std::endl;
    }

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D( GL_TEXTURE_2D, 0, 4, textureImg->getWidth(), textureImg->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImg->getPixels() );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

void Cube3D::draw() {

     /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/


    // Transformations

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix));

    shaderProgram.program.use();

    glUniformMatrix4fv( shaderProgram.uMVPMatrixLoc ,1,GL_FALSE,glm::value_ptr(projMatrix * modelMatrix));
    glUniformMatrix4fv( shaderProgram.uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(modelMatrix));
    glUniformMatrix4fv( shaderProgram.uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(normalMatrix));


    glBindVertexArray(vao);

    glBindTexture( GL_TEXTURE_2D, texture );
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindTexture( GL_TEXTURE_2D, 0 );

    glBindVertexArray(0);
}

/*
// Code avant de tenter les shaders 3D / normals

 //
// Created by Vincent on 13/12/2016.
//
#define GLEW_STATIC



#include "../include/Cube3D.h"

using namespace glimac;


Cube3D::Cube3D() {
    //charge les shaders que l'on a ajouté dans le dossier shaders
    FilePath applicationPath(".\\opengl.exe");
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\color2D.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\color2D.fs.glsl");
    program.use();

    // Matrice de transformation
    this->uModelMatrixID = glGetUniformLocation( program.getGLId(), "uModelMatrix" );


    //*********************************
    // HERE SHOULD COME THE INITIALIZATION CODE
    //*********************************

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

    //********************************
    // HERE SHOULD COME THE RENDERING CODE
    //*********************************

    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glUniformMatrix4fv( uModelMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix * modelMatrix) );

    //Dessiner avec le VAO
    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}




*/