//
// Created by Vincent on 27/12/2016.
//

#include "../include/Quad3D.h"


using namespace glimac;


Quad3D::Quad3D(std::string textureName) {


    shaderProgram = SimpleTexture();

    //********************************
    //HERE SHOULD COME THE INITIALIZATION CODE
    //*********************************

    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float unit = 0.5f;

    // 4 points partagés.
    glm::vec3 bottomA( -unit, 0, -unit );
    glm::vec3 bottomB( unit, 0, -unit );
    glm::vec3 bottomC( unit, 0, unit  );
    glm::vec3 bottomD( -unit, 0, unit );

    std::vector<ShapeVertex> vertices;
    vertices.push_back( ShapeVertex( bottomA, glm::vec3(1, 0, 0), glm::vec2(0,0) ) );
    vertices.push_back( ShapeVertex( bottomB, glm::vec3(1, 0, 0), glm::vec2(0,1) ) );
    vertices.push_back( ShapeVertex( bottomC, glm::vec3(1, 0, 0), glm::vec2(1,1) ) );
    vertices.push_back( ShapeVertex( bottomD, glm::vec3(1, 0, 0), glm::vec2(1,0) ) );

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(ShapeVertex), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // Ajout ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    uint32_t indices[] = {
            0, 1, 2,
            0, 2, 3
    };

    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
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
    std::unique_ptr<Image> textureImg = loadImage( GameManager::getInstance().getAppPath() + "\\..\\..\\assets\\textures\\" + textureName );

    if ( textureImg == NULL ) {
        std::cerr << "IMAGE NOT FOUND!" << std::endl;
    }

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D( GL_TEXTURE_2D, 0, 4, textureImg->getWidth(), textureImg->getHeight(), 0, GL_RGBA, GL_FLOAT, textureImg->getPixels() );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}

void Quad3D::draw() {

    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    // Transformations

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;


    // modelMatrix = GameManager::getInstance().camera1.getViewMatrix();
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelMatrix ));

    shaderProgram.program.use();

    glUniformMatrix4fv( shaderProgram.uMVPMatrixLoc ,1,GL_FALSE,glm::value_ptr(  projMatrix*   GameManager::getInstance().camera1.getViewMatrix() * modelMatrix ));
    glUniformMatrix4fv( shaderProgram.uMVMatrixLoc,1,GL_FALSE,glm::value_ptr(GameManager::getInstance().camera1.getViewMatrix()*modelMatrix  ));
    glUniformMatrix4fv( shaderProgram.uNormalMatrixLoc,1,GL_FALSE,glm::value_ptr(normalMatrix));


    glBindVertexArray(vao);

    glBindTexture( GL_TEXTURE_2D, texture );
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindTexture( GL_TEXTURE_2D, 0 );

    glBindVertexArray(0);




}
